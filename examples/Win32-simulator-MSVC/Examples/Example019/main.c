/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX许可证标识符: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了《掌握FreeRTOS实时内核》一书中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 头文件包含 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* 示例支持函数头文件 */
#include "supporting_functions.h"

/* 本示例中使用的模拟中断编号。编号0到2被FreeRTOS Windows端口本身使用，
 * 因此3是应用程序可用的第一个编号。 */
#define mainINTERRUPT_NUMBER    3

/* 要创建的任务函数声明 */
static void vIntegerGenerator( void * pvParameters );
static void vStringPrinter( void * pvParameters );

/* 中断服务程序（模拟）。这是任务将与之同步的中断。 */
static uint32_t ulExampleInterruptHandler( void );

/*-----------------------------------------------------------*/

/* 声明两个QueueHandle_t类型的变量。一个队列将在ISR中读取，
 * 另一个队列将在ISR中写入。 */
QueueHandle_t xIntegerQueue, xStringQueue;

int main( void )
{
    /* 在使用队列之前必须先创建它。创建本示例使用的两个队列。
     * 一个队列可以保存uint32_t类型的变量，另一个队列可以保存char*类型的变量。
     * 两个队列都最多可以容纳10个项目。实际应用应检查返回值以确保队列已成功创建。 */
    xIntegerQueue = xQueueCreate( 10, sizeof( uint32_t ) );
    xStringQueue = xQueueCreate( 10, sizeof( char * ) );

    /* 创建使用队列向中断服务程序传递整数的任务。
     * 该任务创建时优先级为1。 */
    xTaskCreate( vIntegerGenerator, "IntGen", 1000, NULL, 1, NULL );

    /* 创建打印从中断服务程序发送给它的字符串的任务。
     * 该任务以更高的优先级2创建。 */
    xTaskCreate( vStringPrinter, "String", 1000, NULL, 2, NULL );

    /* 安装软件中断的处理程序。执行此操作所需的语法取决于所使用的FreeRTOS端口。
     * 此处显示的语法只能与FreeRTOS Windows端口一起使用，其中此类中断仅为模拟。 */
    vPortSetInterruptHandler( mainINTERRUPT_NUMBER, ulExampleInterruptHandler );

    /* 启动调度器，使创建的任务开始执行。 */
    vTaskStartScheduler();

    /* 由于vTaskStartScheduler()仅在没有足够的FreeRTOS堆内存来创建空闲任务和
     * （如配置的）定时器任务时才会返回，因此不应该到达以下行。
     * 堆管理和捕获堆耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vIntegerGenerator( void * pvParameters )
{
    TickType_t xLastExecutionTime;
    const TickType_t xDelay200ms = pdMS_TO_TICKS( 200UL ), xDontBlock = 0;
    uint32_t ulValueToSend = 0;
    BaseType_t i;

    /* 初始化vTaskDelayUntil()调用使用的变量。 */
    xLastExecutionTime = xTaskGetTickCount();

    for( ; ; )
    {
        /* 这是一个周期性任务。阻塞，直到再次运行时间到。
         * 任务将每200毫秒执行一次。 */
        vTaskDelayUntil( &xLastExecutionTime, xDelay200ms );

        /* 向队列发送五个数字，每个值比前一个值高一个。
         * 这些数字由中断服务程序从队列中读取。中断服务程序
         * 总是清空队列，所以这个任务保证能够写入所有五个值而
         * 不需要指定阻塞时间。 */
        for( i = 0; i < 5; i++ )
        {
            xQueueSendToBack( xIntegerQueue, &ulValueToSend, xDontBlock );
            ulValueToSend++;
        }

        /* 生成中断，使中断服务程序可以从队列读取值。
         * 用于生成软件中断的语法取决于所使用的FreeRTOS端口。
         * 下面使用的语法只能用于FreeRTOS Windows端口，
         * 在该端口中，此类中断仅为模拟。 */
        vPrintString( "生成器任务 - 即将生成中断。\r\n" );
        vPortGenerateSimulatedInterrupt( mainINTERRUPT_NUMBER );
        vPrintString( "生成器任务 - 中断已生成。\r\n\r\n\r\n" );
    }
}
/*-----------------------------------------------------------*/

static void vStringPrinter( void * pvParameters )
{
    char * pcString;

    for( ; ; )
    {
        /* 在队列上阻塞，等待数据到达。 */
        xQueueReceive( xStringQueue, &pcString, portMAX_DELAY );

        /* 打印接收到的字符串。 */
        vPrintString( pcString );
    }
}
/*-----------------------------------------------------------*/

static uint32_t ulExampleInterruptHandler( void )
{
    BaseType_t xHigherPriorityTaskWoken;
    uint32_t ulReceivedNumber;

/* 字符串声明为static const，以确保它们不会分配在中断服务程序的栈上，
 * 并且即使中断服务程序不执行时也存在。 */
    static const char * pcStrings[] =
    {
        "字符串 0\r\n",
        "字符串 1\r\n",
        "字符串 2\r\n",
        "字符串 3\r\n"
    };

    /* 与往常一样，xHigherPriorityTaskWoken初始化为pdFALSE，以便能够
     * 检测它在中断安全API函数内部被设置为pdTRUE。 */
    xHigherPriorityTaskWoken = pdFALSE;

    /* 从队列读取，直到队列为空。 */
    while( xQueueReceiveFromISR( xIntegerQueue, &ulReceivedNumber, &xHigherPriorityTaskWoken ) != errQUEUE_EMPTY )
    {
        /* 将接收到的值截断为最后两位（值0到3），然后使用截断后的值
         * 作为pcStrings[]数组的索引，以选择要在另一个队列上发送的字符串(char *)。 */
        ulReceivedNumber &= 0x03;
        xQueueSendToBackFromISR( xStringQueue, &pcStrings[ ulReceivedNumber ], &xHigherPriorityTaskWoken );
    }

    /* 如果从xIntegerQueue接收导致任务离开阻塞状态，并且如果离开
     * 阻塞状态的任务的优先级高于运行状态任务的优先级，则
     * xHigherPriorityTaskWoken将在xQueueReceiveFromISR()内部被设置为pdTRUE。
     *
     * 如果向xStringQueue发送导致任务离开阻塞状态，并且如果离开
     * 阻塞状态的任务的优先级高于运行状态任务的优先级，则
     * xHigherPriorityTaskWoken将在xQueueSendFromISR()内部被设置为pdTRUE。
     *
     * xHigherPriorityTaskWoken用作portYIELD_FROM_ISR()的参数。
     * 如果xHigherPriorityTaskWoken等于pdTRUE，则调用portYIELD_FROM_ISR()
     * 将请求上下文切换。如果xHigherPriorityTaskWoken仍为pdFALSE，
     * 则调用portYIELD_FROM_ISR()将没有效果。
     *
     * Windows端口使用的portYIELD_FROM_ISR()实现包括return语句，
     * 这就是为什么此函数不显式返回值的原因。 */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
