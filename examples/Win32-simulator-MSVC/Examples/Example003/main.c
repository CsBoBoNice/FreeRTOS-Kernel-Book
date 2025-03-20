/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是 FreeRTOS 发行版的一部分。
 * 
 *  这包含了《掌握 FreeRTOS 实时内核》一书中列出的示例的 Windows 移植实现。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h> /* 添加 uint32_t 的定义 */

/* 演示包含文件 */
#include "supporting_functions.h"

/* 用作循环计数器以创建一个非常粗略的延迟 */
#define mainDELAY_LOOP_COUNT    ( 0xffffff )

/* 任务函数声明 */
void vTaskFunction( void * pvParameters );

/* 定义将作为任务参数传递的字符串。
 * 这些被定义为 const 并且不在栈上，以确保当任务执行时它们保持有效。 */
const char * pcTextForTask1 = "任务 1 正在运行\r\n";
const char * pcTextForTask2 = "任务 2 正在运行\r\n";

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建第一个任务，优先级为 1... */
    xTaskCreate( vTaskFunction, "Task 1", 1000, ( void * ) pcTextForTask1, 1, NULL );

    /* ...然后创建第二个任务，优先级为 2。优先级是倒数第二个参数。 */
    xTaskCreate( vTaskFunction, "Task 2", 1000, ( void * ) pcTextForTask2, 2, NULL );

    /* 启动调度器，开始执行任务 */
    vTaskStartScheduler();

    /* 下面的代码行永远不应该被执行，因为 vTaskStartScheduler() 
     * 只有在没有足够的 FreeRTOS 堆内存来创建空闲任务和（如果配置了）定时器任务时才会返回。
     * 堆管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void * pvParameters )
{
    char * pcTaskName;
    volatile uint32_t ul;

    /* 通过参数传入要打印的字符串。将其转换为字符指针。 */
    pcTaskName = ( char * ) pvParameters;

    /* 像大多数任务一样，此任务在无限循环中实现 */
    for( ; ; )
    {
        /* 打印此任务的名称 */
        vPrintString( pcTaskName );

        /* 延迟一段时间 */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
            /* 这个循环只是一个非常粗略的延迟实现。
             * 这里没有任何需要执行的内容。
             * 后续练习将使用适当的延迟/睡眠函数替换这个粗略的循环。 */
        }
    }
}
