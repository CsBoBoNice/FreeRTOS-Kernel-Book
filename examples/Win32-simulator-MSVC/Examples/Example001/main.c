/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
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

/* FreeRTOS.org 包含文件。 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示包含文件。 */
#include "supporting_functions.h"

/* 用作循环计数器来创建一个非常粗略的延迟。 */
#define mainDELAY_LOOP_COUNT    ( 0xffffff )

/* 任务函数。 */
void vTask1( void * pvParameters );
void vTask2( void * pvParameters );

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建两个任务中的第一个。 */
    xTaskCreate( vTask1,   /* 指向实现任务的函数的指针。 */
                 "Task 1", /* 任务的文本名称。这是为了便于调试。 */
                 1000,     /* 堆栈深度 - 大多数小型微控制器使用的堆栈比这少得多。 */
                 NULL,     /* 我们没有使用任务参数。 */
                 1,        /* 此任务将以优先级1运行。 */
                 NULL );   /* 我们没有使用任务句柄。 */

    /* 以完全相同的方式创建另一个任务。 */
    xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, NULL );

    /* 启动调度程序以开始执行任务。 */
    vTaskStartScheduler();

    /* 以下行永远不应该被执行，因为vTaskStartScheduler()
    *  只有在没有足够的FreeRTOS堆内存可用于创建空闲和（如果配置了）
    *  定时器任务时才会返回。堆管理和捕获堆耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vTask1( void * pvParameters )
{
    const char * pcTaskName = "Task 1 is running\r\n";
    volatile uint32_t ul;

    /* 与大多数任务一样，此任务在无限循环中实现。 */
    for( ; ; )
    {
        /* 打印此任务的名称。 */
        vPrintString( pcTaskName );

        /* 延迟一段时间。 */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
            /* 这个循环只是一个非常粗略的延迟实现。
             * 这里没有什么可做的。后续练习将用适当的
             * 延迟/睡眠函数替换这个粗略的循环。 */
        }
    }
}
/*-----------------------------------------------------------*/

void vTask2( void * pvParameters )
{
    const char * pcTaskName = "Task 2 is running\r\n";
    volatile uint32_t ul;

    /* 与大多数任务一样，此任务在无限循环中实现。 */
    for( ; ; )
    {
        /* 打印此任务的名称。 */
        vPrintString( pcTaskName );

        /* 延迟一段时间。 */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
            /* 这个循环只是一个非常粗略的延迟实现。
             * 这里没有什么可做的。后续练习将用适当的
             * 延迟/睡眠函数替换这个粗略的循环。 */
        }
    }
}
