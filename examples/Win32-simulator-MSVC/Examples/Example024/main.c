/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是 FreeRTOS 发行版的一部分。
 * 
 *  这里包含了 FreeRTOS 书籍《掌握 FreeRTOS 实时内核》中列出的示例的 Windows 端口实现。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* 演示相关包含文件 */
#include "supporting_functions.h"

/* 本例中使用的模拟中断号。数字 0 到 2 由 FreeRTOS Windows 端口本身使用，
 * 因此 3 是应用程序可用的第一个数字。 */
#define mainINTERRUPT_NUMBER    3

/* 将要创建的任务 */
static void vHandlerTask( void * pvParameters );
static void vPeriodicTask( void * pvParameters );

/* (模拟)中断的服务例程。这是任务将与之同步的中断。 */
static uint32_t ulExampleInterruptHandler( void );

/* 周期性任务产生软件中断的频率 */
static const TickType_t xInterruptFrequency = pdMS_TO_TICKS( 500UL ); /* 每500毫秒触发一次 */

/* 存储中断处理将被延迟到的任务的句柄 */
static TaskHandle_t xHandlerTask = NULL;

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建"处理器"任务，该任务是中断处理被延迟到的任务，
     * 也就是将与中断同步的任务。处理器任务以高优先级创建，
     * 以确保它在中断退出后立即运行。在这种情况下，选择优先级 3。
     * 保存任务的句柄供 ISR 使用。 */
    xTaskCreate( vHandlerTask, "Handler", 1000, NULL, 3, &xHandlerTask );

    /* 创建将定期产生软件中断的任务。
     * 该任务创建时的优先级低于处理器任务，以确保每次处理器任务
     * 退出阻塞状态时，它都会被抢占。 */
    xTaskCreate( vPeriodicTask, "Periodic", 1000, NULL, 1, NULL );

    /* 为软件中断安装处理程序。执行此操作所需的语法取决于
     * 正在使用的 FreeRTOS 端口。此处显示的语法只能与 FreeRTOS
     * Windows 端口一起使用，其中此类中断仅为模拟。 */
    vPortSetInterruptHandler( mainINTERRUPT_NUMBER, ulExampleInterruptHandler );

    /* 启动调度器，使创建的任务开始执行 */
    vTaskStartScheduler();

    /* 以下行永远不应该到达，因为只有在没有足够的 FreeRTOS 堆内存可用于
     * 创建空闲任务和(如果配置了)计时器任务时，vTaskStartScheduler()
     * 才会返回。堆内存管理和捕获堆耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vHandlerTask( void * pvParameters )
{
/* xMaxExpectedBlockTime 设置为比事件之间的最大预期时间稍长一些 */
    const TickType_t xMaxExpectedBlockTime = xInterruptFrequency + pdMS_TO_TICKS( 10 );
    uint32_t ulEventsToProcess;

    /* 和大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 等待接收从中断处理程序直接发送到此任务的通知 */
        ulEventsToProcess = ulTaskNotifyTake( pdTRUE, xMaxExpectedBlockTime );

        if( ulEventsToProcess != 0 )
        {
            /* 要到达这里，至少必须发生一个事件。在这里循环，
             * 直到所有待处理事件都已处理完毕(在这种情况下，只需为每个
             * 事件打印一条消息)。 */
            while( ulEventsToProcess > 0 )
            {
                vPrintString( "处理器任务 - 正在处理事件。\r\n" );
                ulEventsToProcess--;
            }
        }
        else
        {
            /* 如果到达了函数的这一部分，则表示中断未在预期时间内
             * 到达，并且(在实际应用中)可能需要执行一些错误恢复操作。 */
        }
    }
}
/*-----------------------------------------------------------*/

static uint32_t ulExampleInterruptHandler( void )
{
    BaseType_t xHigherPriorityTaskWoken;

    /* xHigherPriorityTaskWoken 参数必须初始化为 pdFALSE，因为如果需要
     * 上下文切换，它将在中断安全 API 函数内部设置为 pdTRUE。 */
    xHigherPriorityTaskWoken = pdFALSE;

    /* 直接向处理器任务发送通知 */
    vTaskNotifyGiveFromISR( /* 正在向其发送通知的任务的句柄。
                             * 创建任务时保存了句柄。 */
        xHandlerTask,

        /* xHigherPriorityTaskWoken 按常规方式使用 */
        &xHigherPriorityTaskWoken );

    /* 将 xHigherPriorityTaskWoken 值传递给 portYIELD_FROM_ISR()。
     * 如果在 vTaskNotifyGiveFromISR() 内部将 xHigherPriorityTaskWoken 
     * 设置为 pdTRUE，则调用 portYIELD_FROM_ISR() 将请求上下文切换。
     * 如果 xHigherPriorityTaskWoken 仍为 pdFALSE，则调用 portYIELD_FROM_ISR() 
     * 将没有任何效果。Windows 端口使用的 portYIELD_FROM_ISR() 实现包含
     * 一个 return 语句，这就是为什么该函数没有显式返回值的原因。 */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/*-----------------------------------------------------------*/

static void vPeriodicTask( void * pvParameters )
{
    /* 与大多数任务一样，此任务在无限循环中实现 */
    for( ; ; )
    {
        /* 此任务仅用于"模拟"中断。这是通过定期生成模拟软件中断来完成的。
         * 阻塞直到再次生成软件中断的时间到来。 */
        vTaskDelay( xInterruptFrequency );

        /* 产生中断，在生成中断前后都打印消息，
         * 以便从输出中清楚地看到执行顺序。
         *
         * 用于生成软件中断的语法取决于正在使用的 FreeRTOS 端口。
         * 下面使用的语法只能与 FreeRTOS Windows 端口一起使用，
         * 在该端口中，这种中断只是模拟的。 */
        vPrintString( "周期性任务 - 即将产生中断。\r\n" );
        vPortGenerateSimulatedInterrupt( mainINTERRUPT_NUMBER );
        vPrintString( "周期性任务 - 中断已产生。\r\n\r\n\r\n" );
    }
}
