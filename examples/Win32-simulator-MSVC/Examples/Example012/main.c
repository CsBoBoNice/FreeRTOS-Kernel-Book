/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  本文件包含FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* 演示支持函数 */
#include "supporting_functions.h"

/* 三个发送任务的函数声明 */
void vSenderTask1( void * pvParameters );
void vSenderTask2( void * pvParameters );

/* 接收任务函数声明。接收任务通过队列集阻塞以从两个发送任务接收数据。 */
void vReceiverTask( void * pvParameters );

/*-----------------------------------------------------------*/

/* 声明两个QueueHandle_t类型的变量。这两个队列都被添加到同一个队列集中。 */
static QueueHandle_t xQueue1 = NULL, xQueue2 = NULL;

/* 声明一个QueueSetHandle_t类型的变量。这是添加两个队列的队列集。 */
static QueueSetHandle_t xQueueSet = NULL;

int main( void )
{
    /* 创建两个队列。每个队列发送字符指针。
     * 接收任务的优先级高于发送任务的优先级，因此队列在任何时候都不会有超过一个项目。 */
    xQueue1 = xQueueCreate( 1, sizeof( char * ) );  /* 创建容量为1的队列1，每个项目大小为char*指针大小 */
    xQueue2 = xQueueCreate( 1, sizeof( char * ) );  /* 创建容量为1的队列2，每个项目大小为char*指针大小 */

    /* 创建队列集。有两个队列，每个队列最多包含1个项目，
     * 因此队列集最多需要容纳2个队列句柄（1个项目乘以2个队列）。 */
    xQueueSet = xQueueCreateSet( 1 * 2 );  /* 创建最大容量为2的队列集 */

    /* 将两个队列添加到队列集中 */
    xQueueAddToSet( xQueue1, xQueueSet );  /* 将队列1添加到队列集 */
    xQueueAddToSet( xQueue2, xQueueSet );  /* 将队列2添加到队列集 */

    /* 创建发送到队列的任务 */
    xTaskCreate( vSenderTask1,     /* 任务函数 */
                "Sender1",         /* 任务名称 */
                1000,              /* 任务堆栈大小 */
                NULL,              /* 任务参数 */
                1,                 /* 任务优先级 - 较低优先级 */
                NULL );            /* 不保存任务句柄 */
    
    xTaskCreate( vSenderTask2,     /* 任务函数 */
                "Sender2",         /* 任务名称 */
                1000,              /* 任务堆栈大小 */
                NULL,              /* 任务参数 */
                1,                 /* 任务优先级 - 较低优先级 */
                NULL );            /* 不保存任务句柄 */

    /* 创建接收任务 */
    xTaskCreate( vReceiverTask,    /* 任务函数 */
                "Receiver",        /* 任务名称 */
                1000,              /* 任务堆栈大小 */
                NULL,              /* 任务参数 */
                2,                 /* 任务优先级 - 较高优先级 */
                NULL );            /* 不保存任务句柄 */

    /* 启动调度器，使创建的任务开始执行 */
    vTaskStartScheduler();

    /* 以下代码行永远不应该被执行，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存来创建空闲任务和（如果配置了）定时器任务时才会返回。
     * 堆管理以及捕获堆耗尽的技术在书本文本中有所描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vSenderTask1( void * pvParameters )
{
    const TickType_t xBlockTime = pdMS_TO_TICKS( 100 );  /* 定义100毫秒的阻塞时间 */
    const char * const pcMessage = "来自vSenderTask1的消息\r\n";  /* 定义要发送的消息 */

    /* 与大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 阻塞100毫秒 */
        vTaskDelay( xBlockTime );

        /* 将此任务的字符串发送到xQueue1。不需要使用阻塞时间，即使队列只能容纳一个项目。
         * 这是因为读取队列的任务优先级高于此任务的优先级；
         * 一旦此任务向队列写入数据，它将被从队列读取的任务抢占，
         * 因此在xQueueSend()调用返回时队列已经再次为空。
         * 阻塞时间设置为0。 */
        xQueueSend( xQueue1, &pcMessage, 0 );  /* 发送消息指针到队列1，无阻塞时间 */
    }
}
/*-----------------------------------------------------------*/

static void vSenderTask2( void * pvParameters )
{
    const TickType_t xBlockTime = pdMS_TO_TICKS( 200 );  /* 定义200毫秒的阻塞时间 */
    const char * const pcMessage = "来自vSenderTask2的消息\r\n";  /* 定义要发送的消息 */

    /* 与大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 阻塞200毫秒 */
        vTaskDelay( xBlockTime );

        /* 将此任务的字符串发送到xQueue2。不需要使用阻塞时间，即使队列只能容纳一个项目。
         * 这是因为读取队列的任务优先级高于此任务的优先级；
         * 一旦此任务向队列写入数据，它将被从队列读取的任务抢占，
         * 因此在xQueueSend()调用返回时队列已经再次为空。
         * 阻塞时间设置为0。 */
        xQueueSend( xQueue2, &pcMessage, 0 );  /* 发送消息指针到队列2，无阻塞时间 */
    }
}
/*-----------------------------------------------------------*/

static void vReceiverTask( void * pvParameters )
{
    QueueHandle_t xQueueThatContainsData;  /* 用于存储包含数据的队列句柄 */
    char * pcReceivedString;  /* 用于接收字符串指针的变量 */

    /* 与大多数任务一样，此任务在无限循环内实现 */
    for( ; ; )
    {
        /* 在队列集上阻塞，等待集合中的一个队列包含数据。
         * 将从xQueueSelectFromSet()返回的QueueSetMemberHandle_t值转换为QueueHandle_t，
         * 因为已知集合中的所有项目都是队列（而不是也可以是队列集成员的信号量）。 */
        xQueueThatContainsData = ( QueueHandle_t ) xQueueSelectFromSet( xQueueSet, portMAX_DELAY );  /* 无限等待，直到队列集中有队列包含数据 */

        /* 从队列集中读取时使用了无限阻塞时间，因此xQueueSelectFromSet()只有在集合中
         * 的一个队列包含数据时才会返回，并且xQueueThatContainsData必须有效。
         * 从队列中读取数据。不需要指定阻塞时间，因为已知队列包含数据。
         * 阻塞时间设置为0。 */
        xQueueReceive( xQueueThatContainsData, &pcReceivedString, 0 );  /* 从包含数据的队列中接收消息 */

        /* 打印从队列接收到的字符串 */
        vPrintString( pcReceivedString );  /* 使用支持函数打印接收到的字符串 */
    }
}
