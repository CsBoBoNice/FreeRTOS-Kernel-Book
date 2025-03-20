/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  本文件包含FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows移植实现。
 *
 */

/* FreeRTOS.org包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* 演示程序包含文件 */
#include "supporting_functions.h"

/* 本示例中使用的模拟中断的编号。编号0到2由FreeRTOS Windows端口本身使用，
 * 因此3是应用程序可用的第一个编号。 */
#define mainINTERRUPT_NUMBER    3

/* 要创建的任务 */
static void vHandlerTask( void * pvParameters );
static void vPeriodicTask( void * pvParameters );

/* 模拟中断的服务例程。这是任务将要与之同步的中断。 */
static uint32_t ulExampleInterruptHandler( void );

/* 周期性任务生成软件中断的频率 */
static const TickType_t xInterruptFrequency = pdMS_TO_TICKS( 500UL );  /* 500毫秒转换为系统节拍数 */

/* 存储中断处理被延迟到的任务的句柄 */
static TaskHandle_t xHandlerTask = NULL;

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建'处理程序'任务，这是中断处理延迟到的任务，因此也是与中断同步的任务。
     * 处理程序任务以高优先级创建，以确保它在中断退出后立即运行。
     * 在这种情况下，选择优先级3。任务的句柄保存供ISR使用。 */
    xTaskCreate( vHandlerTask, "Handler", 1000, NULL, 3, &xHandlerTask );

    /* 创建将定期生成软件中断的任务。
     * 该任务的优先级低于处理程序任务，以确保每次处理程序任务退出阻塞状态时都会抢占该任务。 */
    xTaskCreate( vPeriodicTask, "Periodic", 1000, NULL, 1, NULL );

    /* 为软件中断安装处理程序。
     * 执行此操作所需的语法取决于所使用的FreeRTOS端口。
     * 此处显示的语法只能与FreeRTOS Windows端口一起使用，其中此类中断仅是模拟的。 */
    vPortSetInterruptHandler( mainINTERRUPT_NUMBER, ulExampleInterruptHandler );

    /* 启动调度器，使创建的任务开始执行 */
    vTaskStartScheduler();

    /* 下面的行永远不应该被执行，因为vTaskStartScheduler()只有在没有足够的FreeRTOS堆内存来
     * 创建空闲任务和（如果配置了）定时器任务时才会返回。堆管理和捕获堆耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vHandlerTask( void * pvParameters )
{
/* xMaxExpectedBlockTime被设置为比事件之间的最大预期时间稍长一些 */
    const TickType_t xMaxExpectedBlockTime = xInterruptFrequency + pdMS_TO_TICKS( 10 );  /* 中断频率加上10毫秒的额外时间 */

    /* 与大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 等待接收从中断处理程序直接发送到此任务的通知。
         * xClearCountOnExit参数现在是pdFALSE，所以当ulTaskNotifyTake()
         * 收到通知并返回时，任务的通知值将减少。 */
        if( ulTaskNotifyTake( pdFALSE, xMaxExpectedBlockTime ) != 0 )
        {
            /* 能执行到这里说明事件已经发生。处理事件（在本例中只是打印一条消息）。 */
            vPrintString( "处理程序任务 - 正在处理事件.\r\n" );
        }
        else
        {
            /* 如果达到函数的这部分，则表示中断没有在预期时间内到达，
             * 在实际应用中，可能需要执行一些错误恢复操作。 */
        }
    }
}
/*-----------------------------------------------------------*/

static uint32_t ulExampleInterruptHandler( void )
{
    BaseType_t xHigherPriorityTaskWoken;

    /* xHigherPriorityTaskWoken参数必须初始化为pdFALSE，因为如果需要上下文切换，
     * 它将在中断安全API函数内部设置为pdTRUE。 */
    xHigherPriorityTaskWoken = pdFALSE;

    /* 多次向处理程序任务发送通知。第一次将解除任务阻塞，后续的'give'是为了
     * 演示接收任务的通知值被用来锁定事件 - 允许任务依次处理事件。 */
    vTaskNotifyGiveFromISR( xHandlerTask, &xHigherPriorityTaskWoken );
    vTaskNotifyGiveFromISR( xHandlerTask, &xHigherPriorityTaskWoken );
    vTaskNotifyGiveFromISR( xHandlerTask, &xHigherPriorityTaskWoken );

    /* 将xHigherPriorityTaskWoken值传递给portYIELD_FROM_ISR()。
     * 如果xHigherPriorityTaskWoken在vTaskNotifyGiveFromISR()内部设置为pdTRUE，
     * 则调用portYIELD_FROM_ISR()将请求上下文切换。
     * 如果xHigherPriorityTaskWoken仍然是pdFALSE，则调用portYIELD_FROM_ISR()不会有任何效果。
     * Windows端口使用的portYIELD_FROM_ISR()实现包含一个return语句，
     * 这就是为什么该函数没有显式返回值的原因。 */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/*-----------------------------------------------------------*/

static void vPeriodicTask( void * pvParameters )
{
    /* 与大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 此任务仅用于"模拟"中断。这是通过定期生成模拟软件中断来完成的。
         * 阻塞直到到了再次生成软件中断的时间。 */
        vTaskDelay( xInterruptFrequency );

        /* 生成中断，在生成中断之前和之后都打印消息，以便从输出中可以看到执行顺序。
         *
         * 用于生成软件中断的语法取决于所使用的FreeRTOS端口。
         * 下面使用的语法只能与FreeRTOS Windows端口一起使用，在这个端口中这些中断只是模拟的。 */
        vPrintString( "周期性任务 - 即将生成中断.\r\n" );
        vPortGenerateSimulatedInterrupt( mainINTERRUPT_NUMBER );
        vPrintString( "周期性任务 - 中断已生成.\r\n\r\n\r\n" );
    }
}
