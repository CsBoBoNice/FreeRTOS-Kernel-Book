/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  这里包含了《掌握FreeRTOS实时内核》一书中列出的示例的Windows端口实现。
 *
 */

/* 标准包含文件 */
#include <stdio.h>
#include <conio.h>

/* FreeRTOS包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* 示例支持函数包含文件 */
#include "supporting_functions.h"

/* 发送消息到标准输出守门人的任务。此任务创建两个实例。 */
static void prvPrintTask( void * pvParameters );

/* 守门人任务本身 */
static void prvStdioGatekeeperTask( void * pvParameters );

/* 定义任务和中断将通过守门人打印的字符串 */
static const char * pcStringsToPrint[] =
{
    "任务1 ****************************************************\r\n",
    "任务2 ----------------------------------------------------\r\n",
    "来自时钟钩子中断的消息 ##############\r\n"
};

/*-----------------------------------------------------------*/

/* 声明一个QueueHandle_t类型的变量。这用于从打印任务向守门人任务发送消息。 */
static QueueHandle_t xPrintQueue;

/* 任务会阻塞一个伪随机时间，范围在0到xMaxBlockTime之间的节拍数。 */
const TickType_t xMaxBlockTimeTicks = 0x20;

int main( void )
{
    /* 在使用队列前必须显式创建它。该队列创建为最多容纳5个字符指针。 */
    xPrintQueue = xQueueCreate( 5, sizeof( char * ) );

    /* 检查队列是否成功创建 */
    if( xPrintQueue != NULL )
    {
        /* 创建两个向守门人发送消息的任务实例。它们尝试写入的字符串索引作为任务参数传入
         * （xTaskCreate的第4个参数）。这些任务以不同的优先级创建，因此会发生一些抢占。 */
        xTaskCreate( prvPrintTask, "Print1", 1000, ( void * ) 0, 1, NULL );
        xTaskCreate( prvPrintTask, "Print2", 1000, ( void * ) 1, 2, NULL );

        /* 创建守门人任务。这是唯一被允许访问标准输出的任务。 */
        xTaskCreate( prvStdioGatekeeperTask, "Gatekeeper", 1000, NULL, 0, NULL );

        /* 启动调度器，使创建的任务开始执行 */
        vTaskStartScheduler();
    }

    /* 下面这行代码永远不应该被执行到，因为vTaskStartScheduler()只有在没有足够的
     * FreeRTOS堆内存来创建空闲任务和（如果配置了）定时器任务时才会返回。堆管理和
     * 捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void prvStdioGatekeeperTask( void * pvParameters )
{
    char * pcMessageToPrint;

    /* 这是唯一允许写入终端输出的任务。任何其他想要写入输出的任务不直接访问终端，
     * 而是将输出发送给这个任务。由于只有一个任务写入标准输出，所以在这个任务本身
     * 内部不需要考虑互斥或序列化问题。 */
    for( ; ; )
    {
        /* 等待消息到达 */
        xQueueReceive( xPrintQueue, &pcMessageToPrint, portMAX_DELAY );

        /* 不需要检查返回值，因为任务将无限期阻塞，只有在消息到达时才会再次运行。
         * 当执行下一行代码时，一定会有消息需要输出。 */
        printf( "%s", pcMessageToPrint );
        fflush( stdout );

        /* 现在简单地返回等待下一条消息 */
    }
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
    static int iCount = 0;

    /* 每200个时钟节拍打印一条消息。消息不是直接写出，而是发送给守门人任务。 */
    iCount++;

    if( iCount >= 200 )
    {
        /* 在这种情况下，最后一个参数（xHigherPriorityTaskWoken）实际上没有使用，设置为NULL。 */
        xQueueSendToFrontFromISR( xPrintQueue, &( pcStringsToPrint[ 2 ] ), NULL );

        /* 重置计数器，准备在200个时钟节拍后再次打印字符串 */
        iCount = 0;
    }
}
/*-----------------------------------------------------------*/

static void prvPrintTask( void * pvParameters )
{
    int iIndexToString;

    /* 创建此任务的两个实例，所以任务要发送给守门人任务的字符串索引通过任务参数传入。
     * 将其转换为所需类型。 */
    iIndexToString = ( int ) pvParameters;

    for( ; ; )
    {
        /* 打印字符串，不是直接打印，而是通过队列将字符串传递给守门人任务。
         * 队列在调度器启动前创建，所以在此任务执行时队列已经存在。
         * 未指定阻塞时间，因为队列中应该始终有空间。 */
        xQueueSendToBack( xPrintQueue, &( pcStringsToPrint[ iIndexToString ] ), 0 );

        /* 等待一个伪随机时间。注意，rand()不一定是可重入的，但在这种情况下并不重要，
         * 因为代码不关心返回什么值。在更安全的应用程序中，应该使用已知可重入的rand()版本，
         * 或者使用关键段保护对rand()的调用。 */
        vTaskDelay( ( rand() % xMaxBlockTimeTicks ) );
    }
}
/*-----------------------------------------------------------*/



/* 在其他示例中，此函数在supporting_functions.c源文件中实现，但本示例不包含该源文件，
 * 因为包含它会导致时钟钩子函数的多重定义。 */
void vAssertCalled( uint32_t ulLine,
                    const char * const pcFile )
{
/* 以下两个变量仅确保参数不会被优化掉，因此在调试器中查看时可用。 */
    volatile uint32_t ulLineNumber = ulLine, ulSetNonZeroInDebuggerToReturn = 0;
    volatile const char * const pcFileName = pcFile;

    taskENTER_CRITICAL();
    {
        while( ulSetNonZeroInDebuggerToReturn == 0 )
        {
            /* 如果你想在调试器中退出这个函数以查看assert()位置，
             * 请将ulSetNonZeroInDebuggerToReturn设置为非零值。 */
        }
    }
    taskEXIT_CRITICAL();

    /* 消除潜在的编译器警告，这些警告是因为变量已设置但随后未引用。 */
    ( void ) pcFileName;
    ( void ) ulLineNumber;
}
/*-----------------------------------------------------------*/

/* 在其他示例中，此函数在supporting_functions.c源文件中实现，但本示例不包含该源文件，
 * 因为包含它会导致时钟钩子函数的多重定义。 */
void vApplicationMallocFailedHook( void )
{
    /* 只有当FreeRTOSConfig.h中configUSE_MALLOC_FAILED_HOOK设置为1时，
     * vApplicationMallocFailedHook()才会被调用。它是一个在pvPortMalloc()调用失败时
     * 会被调用的钩子函数。每当内核创建任务、队列、定时器、事件组或信号量时，
     * pvPortMalloc()都会被内部调用。演示应用程序的各个部分也会调用它。
     * 如果使用heap_1.c、heap_2.c或heap_4.c，则pvPortMalloc()可用的堆大小由
     * FreeRTOSConfig.h中的configTOTAL_HEAP_SIZE定义，并且可以使用xPortGetFreeHeapSize()
     * API函数查询剩余的可用堆空间大小。书中提供了更多信息。 */
    vAssertCalled( __LINE__, __FILE__ );
}
/*-----------------------------------------------------------*/
