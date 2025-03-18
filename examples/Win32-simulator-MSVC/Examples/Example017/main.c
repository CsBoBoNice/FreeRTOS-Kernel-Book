/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是 FreeRTOS 发行版的一部分。
 * 
 *  这包含了 FreeRTOS 书籍《掌握 FreeRTOS 实时内核》中列出的示例的 Windows 端口实现。
 *  本例演示了如何使用计数信号量从中断处理程序向任务发送数据。
 *
 */

/* FreeRTOS 头文件引入 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* 演示所需的辅助函数 */
#include "supporting_functions.h"


/* 本例中使用的模拟中断号。数字 0 到 2 由 FreeRTOS Windows 端口本身使用，
 * 因此 3 是应用程序可用的第一个数字。 */
#define mainINTERRUPT_NUMBER    3

/* 需要创建的任务 */
static void vHandlerTask( void * pvParameters );
static void vPeriodicTask( void * pvParameters );

/* (模拟)中断的服务例程。这是任务将与之同步的中断。
 * 当中断发生时，此函数将被调用。 */
static uint32_t ulExampleInterruptHandler( void );

/*-----------------------------------------------------------*/

/* 声明一个 SemaphoreHandle_t 类型的变量。这用于引用将任务与中断同步的信号量。
 * 计数信号量允许多个"给予"操作累积，然后可以被多个"获取"操作使用。 */
SemaphoreHandle_t xCountingSemaphore;


int main( void )
{
    /* 在使用信号量之前，必须先创建它。在此示例中，创建了一个计数信号量。
     * 该信号量被创建为最大计数值为 10，初始计数值为 0。
     * 初始计数为0意味着信号量初始状态为不可用。 */
    xCountingSemaphore = xSemaphoreCreateCounting( 10, 0 );

    /* 检查信号量是否成功创建 */
    if( xCountingSemaphore != NULL )
    {
        /* 创建"处理程序"任务，这是中断处理被推迟到的任务，因此是与中断同步的任务。
         * 处理程序任务以高优先级创建，以确保它在中断退出后立即运行。
         * 在本例中，选择了优先级 3。 */
        xTaskCreate( vHandlerTask, "Handler", 1000, NULL, 3, NULL );

        /* 创建将定期生成软件中断的任务。
         * 这个任务的优先级低于处理程序任务，以确保每次处理程序任务退出阻塞状态时，
         * 该任务都会被抢占。 */
        xTaskCreate( vPeriodicTask, "Periodic", 1000, NULL, 1, NULL );

        /* 为软件中断安装处理程序。执行此操作所需的语法取决于所使用的 FreeRTOS 端口。
         * 此处显示的语法只能与 FreeRTOS Windows 端口一起使用，其中此类中断仅被模拟。 */
        vPortSetInterruptHandler( mainINTERRUPT_NUMBER, ulExampleInterruptHandler );

        /* 启动调度程序，使创建的任务开始执行。
         * 调度器接管控制后，任务将开始执行。 */
        vTaskStartScheduler();
    }

    /* 下面的行应该永远不会到达，因为 vTaskStartScheduler() 只有在没有足够的
     * FreeRTOS 堆内存可用于创建空闲和（如果配置）定时器任务的情况下才会返回。
     * 堆管理和捕获堆耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vHandlerTask( void * pvParameters )
{
    /* 与大多数任务一样，此任务在无限循环中实现。 */
    for( ; ; )
    {
        /* 使用信号量等待事件。信号量是在调度程序启动之前创建的，因此是在此任务首次运行之前创建的。
         * 任务无限期阻塞，这意味着此函数调用仅在成功获得信号量后才会返回，因此无需检查返回值。
         * portMAX_DELAY参数表示任务将永远等待，直到信号量可用。 */
        xSemaphoreTake( xCountingSemaphore, portMAX_DELAY );

        /* 能到达这里说明事件必须已经发生。处理事件（在本例中只是打印一条消息）。
         * 这个消息表明处理程序任务已从信号量接收到通知并正在处理事件。 */
        vPrintString( "处理程序任务 - 正在处理事件。\r\n" );
    }
}
/*-----------------------------------------------------------*/

static void vPeriodicTask( void * pvParameters )
{
    /* 定义一个延迟常量，等于500毫秒的滴答数
     * pdMS_TO_TICKS宏将毫秒转换为系统滴答数 */
    const TickType_t xDelay500ms = pdMS_TO_TICKS( 500UL );

    /* 与大多数任务一样，此任务在无限循环中实现。 */
    for( ; ; )
    {
        /* 此任务仅用于"模拟"中断。这是通过定期生成模拟软件中断来完成的。
         * 阻塞直到再次生成软件中断的时间。
         * vTaskDelay使任务进入阻塞状态指定的时间。 */
        vTaskDelay( xDelay500ms );

        /* 生成中断，在生成中断前后打印消息，以便从输出中清楚地看出执行顺序。
         *
         * 用于生成软件中断的语法取决于所使用的 FreeRTOS 端口。
         * 下面使用的语法只能与 FreeRTOS Windows 端口一起使用，在该端口中，
         * 此类中断只是被模拟。 */
        vPrintString( "周期性任务 - 即将生成中断。\r\n" );
        vPortGenerateSimulatedInterrupt( mainINTERRUPT_NUMBER );
        vPrintString( "周期性任务 - 中断已生成。\r\n\r\n\r\n" );
    }
}
/*-----------------------------------------------------------*/

static uint32_t ulExampleInterruptHandler( void )
{
    BaseType_t xHigherPriorityTaskWoken;

    /* xHigherPriorityTaskWoken 参数必须初始化为 pdFALSE，因为如果在中断安全 API 函数内
     * 需要进行上下文切换，它将被设置为 pdTRUE。
     * 该参数用于指示是否有更高优先级的任务被唤醒。 */
    xHigherPriorityTaskWoken = pdFALSE;

    /* 多次"给予"信号量。第一次将解除阻塞延迟中断处理任务，
     * 后续的"给予"用于演示信号量如何锁定事件，以允许处理程序任务按顺序处理它们，
     * 而不会丢失事件。这模拟了处理器处理多个中断，尽管在这种情况下，
     * 事件是在单个中断发生内模拟的。
     * 
     * 计数信号量的这种特性非常适合实现事件计数和管理有限资源池。 */
    xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
    xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );
    xSemaphoreGiveFromISR( xCountingSemaphore, &xHigherPriorityTaskWoken );

    /* 将 xHigherPriorityTaskWoken 值传递给 portYIELD_FROM_ISR()。
     * 如果在 xSemaphoreGiveFromISR() 内部将 xHigherPriorityTaskWoken 设置为 pdTRUE，
     * 则调用 portYIELD_FROM_ISR() 将请求上下文切换。
     * 如果 xHigherPriorityTaskWoken 仍为 pdFALSE，则调用 portYIELD_FROM_ISR() 将没有效果。
     * Windows 端口使用的 portYIELD_FROM_ISR() 实现包含一个返回语句，
     * 这就是为什么此函数不显式返回值的原因。
     * 
     * 通过这种机制，中断可以立即切换到更高优先级的任务，提高系统响应性。 */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
