/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了《掌握FreeRTOS实时内核》一书中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示包含文件 */
#include "supporting_functions.h"

/* 任务函数声明 */
void vContinuousProcessingTask( void * pvParameters );
void vPeriodicTask( void * pvParameters );

/* 定义将作为任务参数传递的字符串。
 * 这些被定义为常量并且不在栈上，以确保在任务执行时它们保持有效。 */
const char * pcTextForTask1 = "连续任务1正在运行\r\n";
const char * pcTextForTask2 = "连续任务2正在运行\r\n";
const char * pcTextForPeriodicTask = "周期性任务正在运行\r\n";

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建两个连续处理任务的实例，两者都是优先级1。 */
    xTaskCreate( vContinuousProcessingTask, "任务1", 1000, ( void * ) pcTextForTask1, 1, NULL );
    xTaskCreate( vContinuousProcessingTask, "任务2", 1000, ( void * ) pcTextForTask2, 1, NULL );

    /* 创建一个优先级为2的周期性任务实例。 */
    xTaskCreate( vPeriodicTask, "任务3", 1000, ( void * ) pcTextForPeriodicTask, 2, NULL );

    /* 启动调度器以开始执行任务。 */
    vTaskStartScheduler();

    /* 以下代码行永远不应该被执行，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存可用于创建空闲任务和（如果配置了）
     * 定时器任务时才会返回。堆管理和处理堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vContinuousProcessingTask( void * pvParameters )
{
    char * pcTaskName;

    /* 要打印的字符串通过参数传递。将其转换为字符指针。 */
    pcTaskName = ( char * ) pvParameters;

    /* 与大多数任务一样，此任务在无限循环中实现。 */
    for( ; ; )
    {
        /* 打印此任务的名称。这个任务只是重复执行此操作，
         * 永不阻塞或延迟。 */
        vPrintString( pcTaskName );
    }
}
/*-----------------------------------------------------------*/

void vPeriodicTask( void * pvParameters )
{
    TickType_t xLastWakeTime;
    const TickType_t xDelay5ms = pdMS_TO_TICKS( 3UL ); /* 将3毫秒转换为系统节拍数 */

    /* xLastWakeTime变量需要用当前的节拍计数初始化。
     * 注意，这是我们唯一一次访问这个变量。从此以后，
     * xLastWakeTime由vTaskDelayUntil() API函数自动管理。 */
    xLastWakeTime = xTaskGetTickCount();

    /* 与大多数任务一样，此任务在无限循环中实现。 */
    for( ; ; )
    {
        /* 打印此任务的名称。 */
        vPrintString( "周期性任务正在运行\r\n" );

        /* 我们希望此任务每隔3毫秒精确执行一次。
         * vTaskDelayUntil函数会自动计算下一次唤醒的时间点，
         * 确保任务以固定的时间间隔运行，不受任务处理时间的影响。 */
        vTaskDelayUntil( &xLastWakeTime, xDelay5ms );
    }
}
