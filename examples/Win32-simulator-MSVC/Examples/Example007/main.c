/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  请访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是 FreeRTOS 发行版的一部分。
 * 
 *  这包含了《掌握 FreeRTOS 实时内核》这本书中所列举的示例在 Windows 端口上的实现。
 *
 */

/* FreeRTOS.org 头文件包含 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示相关头文件包含 */
#include "supporting_functions.h"

/* 任务函数声明 */
void vTaskFunction( void * pvParameters );

/* 这个变量会被空闲任务钩子函数递增 */
static uint32_t ulIdleCycleCount = 0UL;

/* 定义将作为任务参数传递的字符串。
 * 这些被定义为常量且不在栈上，以确保它们在任务执行期间保持有效。 */
const char * pcTextForTask1 = "任务 1 正在运行\r\n";
const char * pcTextForTask2 = "任务 2 正在运行\r\n";

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建第一个任务，优先级为 1... */
    xTaskCreate( vTaskFunction, "Task 1", 1000, ( void * ) pcTextForTask1, 1, NULL );

    /* ...然后创建第二个任务，优先级为 2。
     * 优先级是倒数第二个参数。 */
    xTaskCreate( vTaskFunction, "Task 2", 1000, ( void * ) pcTextForTask2, 2, NULL );

    /* 启动调度器，开始执行任务。 */
    vTaskStartScheduler();

    /* 以下代码永远不应该被执行，因为 vTaskStartScheduler() 
     * 只有在 FreeRTOS 堆内存不足以创建空闲任务和定时器任务(如果配置了)时才会返回。
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
    const TickType_t xDelay250ms = pdMS_TO_TICKS( 250UL );

    /* 通过参数传入要打印的字符串。将其转换为字符指针。 */
    pcTaskName = ( char * ) pvParameters;

    /* 和大多数任务一样，这个任务在一个无限循环中实现。 */
    for( ; ; )
    {
        /* 打印任务名称和 ulIdleCycleCount 被递增的次数。 */
        vPrintStringAndNumber( pcTaskName, ulIdleCycleCount );

        /* 延时一段时间。这里我们使用 vTaskDelay() 函数，
         * 它会将任务置于阻塞状态，直到延时期限到期。
         * 延时期限以"节拍"为单位指定。 */
        vTaskDelay( xDelay250ms );
    }
}
/*-----------------------------------------------------------*/

/* 空闲钩子函数必须命名为 vApplicationIdleHook()，
 * 不接受参数，且返回类型为 void。 */
void vApplicationIdleHook( void )
{
    /* 这个钩子函数只是递增一个计数器。 */
    ulIdleCycleCount++;
}
