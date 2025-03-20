/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  请访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是FreeRTOS发行版的一部分。
 * 
 *  本文件包含FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows移植实现。
 *
 */

/* 标准包含文件 */
#include <stdio.h>
#include <conio.h>

/* FreeRTOS包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* 演示包含文件 */
#include "supporting_functions.h"

/* 要创建的任务。创建了此任务的两个实例。 */
static void prvPrintTask( void * pvParameters );

/* 使用互斥量控制对标准输出的访问的函数。 */
static void prvNewPrintString( const char * pcString );

/*-----------------------------------------------------------*/

/* 声明一个SemaphoreHandle_t类型的变量。这用于引用确保对stdout互斥访问的互斥量类型信号量。 */
SemaphoreHandle_t xMutex;

/* 任务会在0到xMaxBlockTime之间的伪随机时间内阻塞。 */
const TickType_t xMaxBlockTimeTicks = 0x20;

int main( void )
{
    /* 在使用信号量之前，必须显式创建它。在此示例中，创建了一个互斥量类型的信号量。 */
    xMutex = xSemaphoreCreateMutex();

    /* 检查信号量是否成功创建。 */
    if( xMutex != NULL )
    {
        /* 创建两个尝试写入stdout的任务实例。
         * 它们尝试写入的字符串作为任务参数传入。
         * 创建任务时使用不同的优先级，因此会发生一些抢占。 */
        xTaskCreate( prvPrintTask, "Print1", 1000, "任务1 ******************************************\r\n", 1, NULL );
        xTaskCreate( prvPrintTask, "Print2", 1000, "任务2 ------------------------------------------\r\n", 2, NULL );

        /* 启动调度器，使创建的任务开始执行。 */
        vTaskStartScheduler();
    }

    /* 以下代码行永远不应该被执行，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存来创建空闲任务和（如果配置了）定时器任务时才会返回。
     * 堆管理和捕获堆耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void prvNewPrintString( const char * pcString )
{
    /* 信号量在调度器启动前创建，因此在此任务执行时已经存在。
     *
     * 尝试获取信号量，如果互斥量不能立即可用，则无限期阻塞。
     * 对xSemaphoreTake()的调用只有在成功获取信号量后才会返回，
     * 因此无需检查返回值。如果使用任何其他延迟期，则代码必须检查
     * xSemaphoreTake()是否返回pdTRUE，然后才能访问资源（在本例中是标准输出）。 */
    xSemaphoreTake( xMutex, portMAX_DELAY );
    {
        /* 只有在成功获取信号量后，才会执行以下行 - 因此可以自由访问标准输出。 */
        printf( "%s", pcString );
        fflush( stdout );
    }
    xSemaphoreGive( xMutex );

    /* 允许按任意键停止应用程序运行。实际应用程序如果真正使用键值，
     * 也应该保护对键盘的访问。不过，实际应用程序不太可能有多个任务处理按键！ */
    if( _kbhit() != 0 )
    {
        vTaskEndScheduler();
    }
}
/*-----------------------------------------------------------*/

static void prvPrintTask( void * pvParameters )
{
    char * pcStringToPrint;
    const TickType_t xSlowDownDelay = pdMS_TO_TICKS( 5UL );

    /* 创建此任务的两个实例。任务打印的字符串通过任务参数传递给任务。
     * 参数被转换为所需的类型。 */
    pcStringToPrint = ( char * ) pvParameters;

    for( ; ; )
    {
        /* 使用新定义的函数打印字符串。 */
        prvNewPrintString( pcStringToPrint );

        /* 等待伪随机时间。注意，rand()不一定是可重入的，
         * 但在这种情况下，代码不关心返回什么值，所以并不重要。
         * 在更安全的应用程序中，应该使用已知可重入的rand()版本，
         * 或者使用临界区保护对rand()的调用。 */
        vTaskDelay( rand() % xMaxBlockTimeTicks );

        /* 仅确保滚动不会太快！ */
        vTaskDelay( xSlowDownDelay );
    }
}
