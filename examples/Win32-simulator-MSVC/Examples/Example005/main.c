/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 以确保您使用的是最新版本。
 *
 *  此文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示相关包含文件 */
#include "supporting_functions.h"

/* 任务函数声明 */
void vTaskFunction( void * pvParameters );

/* 定义将作为任务参数传递的字符串。
 * 这些字符串被定义为const并且不在栈上，以确保它们在任务执行时保持有效。 */
const char * pcTextForTask1 = "任务1正在运行\r\n";
const char * pcTextForTask2 = "任务2正在运行\r\n";

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建第一个任务，优先级为1... */
    xTaskCreate( vTaskFunction, "Task 1", 1000, ( void * ) pcTextForTask1, 1, NULL );

    /* ...然后创建第二个任务，优先级为2。
     * 优先级是倒数第二个参数。数值越大，优先级越高。 */
    xTaskCreate( vTaskFunction, "Task 2", 1000, ( void * ) pcTextForTask2, 2, NULL );

    /* 启动调度器，开始执行任务 */
    vTaskStartScheduler();

    /* 如果程序执行到这里，说明出现了问题。
     * vTaskStartScheduler()只有在没有足够的FreeRTOS堆内存来创建
     * 空闲任务和计时器任务(如果配置了)时才会返回。
     * 堆内存管理和捕获堆内存耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void * pvParameters )
{
    char * pcTaskName;
    TickType_t xLastWakeTime;
    const TickType_t xDelay250ms = pdMS_TO_TICKS( 250UL ); /* 将250毫秒转换为系统节拍数 */

    /* 通过参数传入要打印的字符串。将参数转换为字符指针类型。 */
    pcTaskName = ( char * ) pvParameters;

    /* xLastWakeTime变量需要使用当前节拍计数初始化。
     * 注意这是我们唯一一次直接访问这个变量。
     * 从这一点开始，xLastWakeTime将由vTaskDelayUntil() API函数自动管理。 */
    xLastWakeTime = xTaskGetTickCount();

    /* 和大多数任务一样，这个任务在一个无限循环中实现 */
    for( ; ; )
    {
        /* 打印出这个任务的名称 */
        vPrintString( pcTaskName );

        /* 我们希望这个任务精确地每250毫秒执行一次。
         * 与vTaskDelay()函数一样，时间以节拍为单位测量，
         * pdMS_TO_TICKS()宏用于将毫秒转换为节拍数。
         * xLastWakeTime在vTaskDelayUntil()内部自动更新，
         * 因此此任务代码不需要更新它。
         * 这与vTaskDelay()不同，vTaskDelayUntil()提供了更精确的周期时间控制。 */
        vTaskDelayUntil( &xLastWakeTime, xDelay250ms );
    }
}
