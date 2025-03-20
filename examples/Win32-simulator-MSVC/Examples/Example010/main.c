/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了书籍《掌握FreeRTOS实时内核》中列出示例的Windows端口实现。
 *
 */

/* FreeRTOS.org头文件包含 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* 演示相关头文件包含 */
#include "supporting_functions.h"


/* 要创建的任务。发送者任务创建两个实例，而接收者任务只创建一个实例 */
static void vSenderTask( void * pvParameters );
static void vReceiverTask( void * pvParameters );

/*-----------------------------------------------------------*/

/* 声明一个QueueHandle_t类型的变量。用于存储三个任务都访问的队列句柄 */
QueueHandle_t xQueue;


int main( void )
{
    /* 创建一个最多能容纳5个长整型值的队列 */
    xQueue = xQueueCreate( 5, sizeof( int32_t ) );

    if( xQueue != NULL )
    {
        /* 创建两个将写入队列的任务实例。
         * 参数用于传递任务应写入队列的值，
         * 因此一个任务将持续地向队列写入100，
         * 而另一个任务将持续地向队列写入200。
         * 两个任务都以优先级1创建。 */
        xTaskCreate( vSenderTask, "Sender1", 1000, ( void * ) 100, 1, NULL );
        xTaskCreate( vSenderTask, "Sender2", 1000, ( void * ) 200, 1, NULL );

        /* 创建从队列读取的任务。该任务以优先级2创建，
         * 高于发送者任务的优先级。 */
        xTaskCreate( vReceiverTask, "Receiver", 1000, NULL, 2, NULL );

        /* 启动调度器，使创建的任务开始执行 */
        vTaskStartScheduler();
    }
    else
    {
        /* 队列无法创建 */
    }

    /* 下面的行应该永远不会执行，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存用于创建空闲任务和
     * （如果配置了）定时器任务时才会返回。
     * 堆管理以及捕获堆耗尽的技术都在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vSenderTask( void * pvParameters )
{
    int32_t lValueToSend;
    BaseType_t xStatus;

    /* 由于创建了此任务的两个实例，所以发送到队列的值通过任务参数传入，
     * 而不是硬编码的。这样每个实例都可以使用不同的值。
     * 将参数转换为所需的类型。 */
    lValueToSend = ( int32_t ) pvParameters;

    /* 与大多数任务一样，该任务在无限循环中实现 */
    for( ; ; )
    {
        /* 第一个参数是要发送数据的队列。
         * 队列是在调度器启动之前创建的，因此在此任务开始执行之前就已创建。
         *
         * 第二个参数是要发送数据的地址。
         *
         * 第三个参数是阻塞时间 - 如果队列已满，任务应保持在阻塞状态等待
         * 队列中的空间变得可用的时间。在这种情况下，我们不指定阻塞时间，
         * 因为队列中应该始终有空间。 */
        xStatus = xQueueSendToBack( xQueue, &lValueToSend, 0 );

        if( xStatus != pdPASS )
        {
            /* 我们无法写入队列，因为它已满 - 这必须是一个错误，
             * 因为队列永远不应该包含超过一个项目！ */
            vPrintString( "无法发送到队列。\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void vReceiverTask( void * pvParameters )
{
/* 声明将保存从队列接收的值的变量 */
    int32_t lReceivedValue;
    BaseType_t xStatus;
    const TickType_t xTicksToWait = pdMS_TO_TICKS( 100UL );

    /* 该任务也在无限循环中定义 */
    for( ; ; )
    {
        /* 由于该任务在数据写入队列后立即解除阻塞，
         * 因此这个调用应该总是发现队列为空。 */
        if( uxQueueMessagesWaiting( xQueue ) != 0 )
        {
            vPrintString( "队列应该是空的！\r\n" );
        }

        /* 第一个参数是要从中接收数据的队列。
         * 队列是在调度器启动之前创建的，因此在此任务首次运行之前就已创建。
         *
         * 第二个参数是接收数据将放入的缓冲区。
         * 在这种情况下，缓冲区只是一个变量的地址，该变量具有存储接收数据所需的大小。
         *
         * 最后一个参数是阻塞时间 - 如果队列已经为空，任务应该保持在阻塞状态等待
         * 数据可用的最大时间。 */
        xStatus = xQueueReceive( xQueue, &lReceivedValue, xTicksToWait );

        if( xStatus == pdPASS )
        {
            /* 已成功从队列接收数据，打印出接收到的值。 */
            vPrintStringAndNumber( "接收到的值 = ", lReceivedValue );
        }
        else
        {
            /* 即使等待了100ms，我们也没有从队列接收到任何内容。
             * 这必须是一个错误，因为发送任务是自由运行的，并且会不断地写入队列。 */
            vPrintString( "无法从队列接收。\r\n" );
        }
    }
}
