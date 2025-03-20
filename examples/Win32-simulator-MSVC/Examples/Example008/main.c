/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 以确保您使用的是最新版本。
 *
 *  此文件是FreeRTOS发行版的一部分。
 * 
 *  此文件包含Windows端口实现，用于《掌握FreeRTOS实时内核》书中列出的示例。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示程序包含文件 */
#include "supporting_functions.h"

/* 两个任务函数的声明 */
void vTask1( void * pvParameters );
void vTask2( void * pvParameters );

/* 用于保存Task2的句柄 */
TaskHandle_t xTask2Handle;

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建第一个任务，优先级为2。
     * 这次任务参数未使用，设置为NULL。
     * 任务句柄也未使用，同样设置为NULL。 */
    xTaskCreate( vTask1, "Task 1", 1000, NULL, 2, NULL );
    /* 任务创建时优先级设为2 ^ */

    /* 创建第二个任务，优先级为1 - 比Task1的优先级低。
     * 同样，任务参数未使用，设置为NULL。
     * 但这次我们需要获取任务句柄，所以传入xTask2Handle变量的地址。 */
    xTaskCreate( vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle );
    /* 任务句柄是最后一个参数 ^^^^^^^^^^^^^ */

    /* 启动调度器，开始任务执行 */
    vTaskStartScheduler();

    /* 下面的代码行应该永远不会执行到，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存用于创建空闲任务和定时器任务(如果配置了)
     * 时才会返回。堆管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

void vTask1( void * pvParameters )
{
    UBaseType_t uxPriority;

    /* 由于Task1的优先级更高，它将始终在Task2之前运行。
     * 由于Task1和Task2都不会阻塞，所以它们总是处于
     * 运行状态(Running)或就绪状态(Ready)。
     *
     * 查询此任务运行的优先级 - 传入NULL表示"返回我们自己的优先级"。 */
    uxPriority = uxTaskPriorityGet( NULL );

    for( ; ; )
    {
        /* 打印此任务的名称 */
        vPrintString( "Task1 正在运行\r\n" );

        /* 将Task2的优先级设置为高于Task1的优先级，这将导致
         * Task2立即开始运行(因为此时Task2将具有两个已创建任务中
         * 更高的优先级)。 */
        vPrintString( "即将提高Task2的优先级\r\n" );
        vTaskPrioritySet( xTask2Handle, ( uxPriority + 1 ) );

        /* Task1只有在优先级高于Task2时才会运行。
         * 因此，要使此任务到达此点，Task2必须已经执行并将
         * 其优先级重新设回较低值。 */
    }
}

/*-----------------------------------------------------------*/

void vTask2( void * pvParameters )
{
    UBaseType_t uxPriority;

    /* 由于Task1具有更高的优先级，它将始终在此任务之前运行。
     * Task1和Task2都不会阻塞，所以它们总是处于
     * 运行状态(Running)或就绪状态(Ready)。
     *
     * 查询此任务运行的优先级 - 传入NULL表示"返回我们自己的优先级"。 */
    uxPriority = uxTaskPriorityGet( NULL );

    for( ; ; )
    {
        /* 要使此任务到达此点，Task1必须已经运行并将
         * 此任务的优先级设置为高于自身的优先级。
         *
         * 打印此任务的名称。 */
        vPrintString( "Task2 正在运行\r\n" );

        /* 将我们的优先级恢复为原始值。
         * 将NULL作为任务句柄传入表示"更改我们自己的优先级"。
         * 将优先级设置为低于Task1的优先级将导致Task1立即
         * 再次开始运行。 */
        vPrintString( "即将降低Task2的优先级\r\n" );
        vTaskPrioritySet( NULL, ( uxPriority - 2 ) );
    }
}
/*-----------------------------------------------------------*/
