/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  这里包含了《掌握FreeRTOS实时内核》一书中列出的示例在Windows端口上的实现。
 *
 */

/* FreeRTOS.org 头文件包含 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* 示例程序支持函数 */
#include "supporting_functions.h"

/* 本示例中使用的模拟中断号。0到2号中断被FreeRTOS Windows端口自身使用，
 * 所以3号是应用程序可用的第一个中断号。 */
#define mainINTERRUPT_NUMBER    3

/* 要创建的任务 */
static void vHandlerTask( void * pvParameters );    /* 处理器任务 - 用于处理中断事件 */
static void vPeriodicTask( void * pvParameters );   /* 周期性任务 - 用于定期生成软件中断 */

/* 模拟中断的服务例程。这是任务将要与之同步的中断处理程序。 */
static uint32_t ulExampleInterruptHandler( void );

/*-----------------------------------------------------------*/

/* 声明一个SemaphoreHandle_t类型的变量。这用于引用将任务与中断同步的二值信号量。 */
SemaphoreHandle_t xBinarySemaphore;

int main( void )
{
    /* 在使用信号量之前必须先显式创建它。本示例中创建了一个二值信号量。 */
    xBinarySemaphore = xSemaphoreCreateBinary();

    /* 检查信号量是否创建成功 */
    if( xBinarySemaphore != NULL )
    {
        /* 创建"处理器"任务，这是中断处理被推迟到的任务，因此它是与中断同步的任务。
         * 处理器任务创建时具有较高优先级，以确保它在中断退出后立即运行。
         * 这里选择了优先级3。 */
        xTaskCreate( vHandlerTask, "Handler", 1000, NULL, 3, NULL );

        /* 创建将周期性生成软件中断的任务。
         * 这个任务创建时优先级低于处理器任务，以确保每次处理器任务
         * 退出阻塞状态时，它都会被抢占。 */
        xTaskCreate( vPeriodicTask, "Periodic", 1000, NULL, 1, NULL );

        /* 为软件中断安装处理程序。执行此操作所需的语法取决于所使用的FreeRTOS端口。
         * 此处显示的语法只能与FreeRTOS Windows端口一起使用，其中这些中断仅被模拟。 */
        vPortSetInterruptHandler( mainINTERRUPT_NUMBER, ulExampleInterruptHandler );

        /* 启动调度器，使创建的任务开始执行 */
        vTaskStartScheduler();
    }

    /* 下面的行永远不应该被执行到，因为vTaskStartScheduler()只有在没有足够的
     * FreeRTOS堆内存可用于创建空闲和（如果配置了）定时器任务时才会返回。
     * 堆内存管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vHandlerTask( void * pvParameters )
{
    /* 像大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 使用信号量等待事件。信号量是在调度器启动之前创建的，因此在此任务首次运行之前。
         * 任务无限期阻塞，这意味着此函数调用仅在成功获取信号量后才会返回 - 
         * 因此无需检查返回值。 */
        xSemaphoreTake( xBinarySemaphore, portMAX_DELAY );

        /* 能够执行到这里说明事件必定已经发生。处理事件（在本例中仅打印一条消息）。 */
        vPrintString( "处理器任务 - 正在处理事件。\r\n" );
    }
}
/*-----------------------------------------------------------*/

static void vPeriodicTask( void * pvParameters )
{
    /* 定义一个500毫秒的延迟常量，使用pdMS_TO_TICKS将毫秒转换为系统节拍数 */
    const TickType_t xDelay500ms = pdMS_TO_TICKS( 500UL );

    /* 像大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 此任务仅用于"模拟"中断。通过周期性地生成模拟软件中断来实现。
         * 阻塞直到再次生成软件中断的时间到来。 */
        vTaskDelay( xDelay500ms );

        /* 生成中断，在生成中断前后都打印消息，以便从输出中清楚地看到执行顺序。
         *
         * 用于生成软件中断的语法取决于所使用的FreeRTOS端口。
         * 下面使用的语法只能用于FreeRTOS Windows端口，其中这种中断仅被模拟。 */
        vPrintString( "周期性任务 - 即将生成中断。\r\n" );
        vPortGenerateSimulatedInterrupt( mainINTERRUPT_NUMBER );
        vPrintString( "周期性任务 - 中断已生成。\r\n\r\n\r\n" );
    }
}
/*-----------------------------------------------------------*/

static uint32_t ulExampleInterruptHandler( void )
{
    BaseType_t xHigherPriorityTaskWoken;

    /* xHigherPriorityTaskWoken参数必须初始化为pdFALSE，因为如果在中断安全的
     * API函数内需要进行上下文切换，它将被设置为pdTRUE。 */
    xHigherPriorityTaskWoken = pdFALSE;

    /* "释放"信号量以解除任务的阻塞。 */
    xSemaphoreGiveFromISR( xBinarySemaphore, &xHigherPriorityTaskWoken );

    /* 将xHigherPriorityTaskWoken值传递给portYIELD_FROM_ISR()。
     * 如果在xSemaphoreGiveFromISR()内部将xHigherPriorityTaskWoken设置为pdTRUE，
     * 那么调用portYIELD_FROM_ISR()将请求上下文切换。
     * 如果xHigherPriorityTaskWoken仍为pdFALSE，则调用portYIELD_FROM_ISR()不会有任何效果。
     * Windows端口使用的portYIELD_FROM_ISR()实现包含一个返回语句，
     * 这就是为什么此函数不显式返回值的原因。 */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
