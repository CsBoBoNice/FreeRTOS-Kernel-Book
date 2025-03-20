/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了Windows端口实现的示例，这些示例在FreeRTOS书籍
 *  《掌握FreeRTOS实时内核》中列出。
 *
 */

/* FreeRTOS.org头文件包含 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示相关的头文件包含 */
#include "supporting_functions.h"

/* 两个任务函数的声明 */
void vTask1( void * pvParameters );
void vTask2( void * pvParameters );

/* 用于保存Task2的句柄 */
TaskHandle_t xTask2Handle;

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建第一个任务，优先级为1。
     * 这次任务参数未使用，设置为NULL。
     * 任务句柄也未使用，同样设置为NULL。 */
    xTaskCreate( vTask1, "Task 1", 1000, NULL, 1, NULL );
    /* 任务创建时的优先级为1 ^ */

    /* 启动调度器，开始执行任务 */
    vTaskStartScheduler();

    /* 以下代码行永远不应该被执行，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存来创建空闲任务和(如果配置了)
     * 定时器任务时才会返回。堆管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vTask1( void * pvParameters )
{
    /* 定义一个100毫秒的延时时间常量 */
    const TickType_t xDelay100ms = pdMS_TO_TICKS( 100UL );

    for( ; ; )
    {
        /* 打印此任务的名称 */
        vPrintString( "Task1 正在运行\r\n" );

        /* 以更高优先级创建任务2。
         * 同样，任务参数未使用，设置为NULL。
         * 但这次我们需要获取任务的句柄，所以传入xTask2Handle变量的地址。 */
        xTaskCreate( vTask2, "Task 2", 1000, NULL, 2, &xTask2Handle );
        /* 任务句柄是最后一个参数 ^^^^^^^^^^^^^ */

        /* 由于任务2具有更高的优先级，所以任务1能够执行到这里，
         * 说明任务2必须已经执行并删除了自己。
         * 延时100毫秒后继续执行。 */
        vTaskDelay( xDelay100ms );
    }
}

/*-----------------------------------------------------------*/

void vTask2( void * pvParameters )
{
    /* 任务2除了删除自己外不做任何事情。
     * 为了实现这一点，它可以调用vTaskDelete()并使用NULL参数，
     * 但为了演示目的，它使用自己的任务句柄调用vTaskDelete()。 */
    vPrintString( "Task2 正在运行并即将删除自己\r\n" );
    vTaskDelete( xTask2Handle );
}
/*-----------------------------------------------------------*/
