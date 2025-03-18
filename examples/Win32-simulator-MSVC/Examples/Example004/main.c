/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了《掌握FreeRTOS实时内核》一书中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 头文件包含 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示所需的头文件 */
#include "supporting_functions.h"

/* 任务函数声明 */
void vTaskFunction( void * pvParameters );

/* 定义将作为任务参数传递的字符串。
 * 这些被定义为常量并且不在栈上，以确保当任务执行时它们保持有效。 */
const char * pcTextForTask1 = "任务1正在运行\r\n";
const char * pcTextForTask2 = "任务2正在运行\r\n";

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建第一个任务，优先级为1... */
    xTaskCreate( vTaskFunction, "Task 1", 1000, ( void * ) pcTextForTask1, 1, NULL );

    /* ...创建第二个任务，优先级为2。优先级是倒数第二个参数。 
     * 优先级值越大，任务优先级越高 */
    xTaskCreate( vTaskFunction, "Task 2", 1000, ( void * ) pcTextForTask2, 2, NULL );

    /* 启动调度器开始执行任务。
     * 此时，控制权将转移给FreeRTOS调度器 */
    vTaskStartScheduler();

    /* 以下代码行永远不应该被执行，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存来创建空闲任务和定时器任务(如果配置了)时才会返回。
     * 堆管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
        /* 如果调度器因为内存不足而退出，程序会卡在这个无限循环中 */
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void * pvParameters )
{
    char * pcTaskName;
    const TickType_t xDelay250ms = pdMS_TO_TICKS( 250UL );  /* 将250毫秒转换为系统节拍数 */

    /* 要打印的字符串通过参数传入。将其转换为字符指针。 */
    pcTaskName = ( char * ) pvParameters;

    /* 与大多数任务一样，此任务在无限循环中实现。 */
    for( ; ; )
    {
        /* 打印此任务的名称。 */
        vPrintString( pcTaskName );

        /* 延时一段时间。这里使用vTaskDelay()函数，
         * 该函数将任务置于阻塞状态，直到延时期限已过。
         * 参数采用"节拍"指定的时间，pdMS_TO_TICKS()宏用于
         * 将250毫秒转换为等效的节拍时间。
         * 当任务处于阻塞状态时，调度器可以执行其他任务。 */
        vTaskDelay( xDelay250ms );
    }
}
