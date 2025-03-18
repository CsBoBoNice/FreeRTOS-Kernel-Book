/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  请访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是 FreeRTOS 发行版的一部分。
 * 
 *  这包含了《精通 FreeRTOS 实时内核》书中列出的示例的 Windows 移植实现。
 *
 */

/* FreeRTOS.org 头文件包含 */
#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>  /* 添加 stdint.h 以解决 uint32_t 未定义的问题 */
#include <stddef.h>  /* 添加 stddef.h 以解决 NULL 未定义的问题 */

/* 演示程序头文件包含 */
#include "supporting_functions.h"

/* 用作循环计数器来创建一个非常简单的延迟 */
#define mainDELAY_LOOP_COUNT    ( 0xffffff )

/* 任务函数声明 */
void vTaskFunction( void * pvParameters );

/* 定义将作为任务参数传递的字符串。
 * 这些被定义为常量并且不在栈上，以确保任务执行时它们保持有效。 */
const char * pcTextForTask1 = "任务 1 正在运行\r\n";
const char * pcTextForTask2 = "任务 2 正在运行\r\n";

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建两个任务中的第一个 */
    xTaskCreate( vTaskFunction,             /* 指向实现任务的函数的指针 */
                 "Task 1",                  /* 任务的文本名称，仅用于调试目的 */
                 1000,                      /* 堆栈深度 - 大多数小型微控制器使用的堆栈比这少得多 */
                 ( void * ) pcTextForTask1, /* 将要打印的文本作为任务参数传入 */
                 1,                         /* 该任务将以优先级 1 运行 */
                 NULL );                    /* 我们不使用任务句柄 */

    /* 以完全相同的方式创建另一个任务。
     * 注意这次我们创建的是相同的任务，但传入不同的参数。
     * 我们创建了单个任务实现的两个实例。 */
    xTaskCreate( vTaskFunction, "Task 2", 1000, ( void * ) pcTextForTask2, 1, NULL );

    /* 启动调度器以开始执行任务 */
    vTaskStartScheduler();

    /* 下面的行应该永远不会被执行，因为 vTaskStartScheduler()
     * 只有在没有足够的 FreeRTOS 堆内存来创建空闲任务和
     * （如果配置了）定时器任务时才会返回。
     * 堆管理和捕获堆耗尽的技术在书中有描述。 */
    for( ; ; )
    {
        /* 无限循环 */
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void * pvParameters )
{
    char * pcTaskName;
    volatile uint32_t ul;

    /* 要打印的字符串通过参数传入。将其转换为字符指针。 */
    pcTaskName = ( char * ) pvParameters;

    /* 与大多数任务一样，此任务在无限循环中实现 */
    for( ; ; )
    {
        /* 打印此任务的名称 */
        vPrintString( pcTaskName );

        /* 延迟一段时间 */
        for( ul = 0; ul < mainDELAY_LOOP_COUNT; ul++ )
        {
            /* 这个循环只是一个非常简单的延迟实现。
             * 这里没有什么要做的。
             * 后面的练习将用适当的延迟/睡眠函数替换这个简单的循环。 */
        }
    }
}
