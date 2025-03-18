/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 以确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  此文件包含《掌握FreeRTOS实时内核》一书中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 头文件引入 */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* 演示程序所需的辅助函数 */
#include "supporting_functions.h"

/* 要创建的任务。发送者任务创建两个实例，而接收者任务只创建一个实例。 */
static void vSenderTask( void * pvParameters );
static void vReceiverTask( void * pvParameters );

/*-----------------------------------------------------------*/

/* 声明一个QueueHandle_t类型的变量。该变量用于存储队列的句柄，
 * 这个队列将被所有三个任务访问。 */
QueueHandle_t xQueue;

/* 定义数据源枚举类型，用于区分数据来自哪个发送者 */
typedef enum
{
    eSender1,  /* 发送者1 */
    eSender2   /* 发送者2 */
} DataSource_t;

/* 定义将在队列上传递的结构体类型 */
typedef struct
{
    uint8_t ucValue;        /* 存储要发送的数值 */
    DataSource_t eDataSource; /* 标识数据来源（哪个发送者） */
} Data_t;

/* 声明两个Data_t类型的变量，将被传递到队列中 */
static const Data_t xStructsToSend[ 2 ] =
{
    { 100, eSender1 }, /* 由发送者1使用的数据 */
    { 200, eSender2 }  /* 由发送者2使用的数据 */
};

int main( void )
{
    /* 创建一个队列，该队列最多可容纳3个Data_t类型的结构体 */
    xQueue = xQueueCreate( 3, sizeof( Data_t ) );

    if( xQueue != NULL )
    {
        /* 创建两个发送任务的实例。参数用于传递任务应该写入队列的结构体，
         * 因此一个任务将持续发送xStructsToSend[0]到队列，
         * 而另一个任务将持续发送xStructsToSend[1]到队列。
         * 两个任务的优先级都设为2，高于接收者任务的优先级。 */
        xTaskCreate( vSenderTask, "Sender1", 1000, ( void * ) &( xStructsToSend[ 0 ] ), 2, NULL );
        xTaskCreate( vSenderTask, "Sender2", 1000, ( void * ) &( xStructsToSend[ 1 ] ), 2, NULL );

        /* 创建从队列读取的任务。该任务的优先级为1，低于发送者任务的优先级。 */
        xTaskCreate( vReceiverTask, "Receiver", 1000, NULL, 1, NULL );

        /* 启动调度器，使创建的任务开始执行 */
        vTaskStartScheduler();
    }
    else
    {
        /* 队列创建失败的处理 */
    }

    /* 以下代码不应该被执行到，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存来创建空闲任务和
     * （如果配置了）定时器任务时才会返回。
     * 堆管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vSenderTask( void * pvParameters )
{
    BaseType_t xStatus;
    /* 设置等待时间为100毫秒，转换为系统节拍 */
    const TickType_t xTicksToWait = pdMS_TO_TICKS( 100UL );

    /* 与大多数任务一样，此任务在无限循环中实现 */
    for( ; ; )
    {
        /* 第一个参数是要发送数据的目标队列。
         * 该队列是在调度器启动前创建的，因此在此任务开始执行前就已存在。
         *
         * 第二个参数是要发送的结构体的地址。
         * 该地址作为任务参数传入。
         *
         * 第三个参数是阻塞时间 - 如果队列已满，任务应保持在阻塞状态等待队列空间的时间。
         * 指定阻塞时间是因为队列会变满。只有当两个发送任务都处于阻塞状态时，
         * 接收任务才会从队列中移除项目。 */
        xStatus = xQueueSendToBack( xQueue, pvParameters, xTicksToWait );

        if( xStatus != pdPASS )
        {
            /* 无法向队列写入数据，因为队列已满 - 这必须是一个错误，
             * 因为接收任务应该在两个发送任务都处于阻塞状态时在队列中腾出空间。 */
            vPrintString( "无法发送到队列。\r\n" );
        }
    }
}
/*-----------------------------------------------------------*/

static void vReceiverTask( void * pvParameters )
{
/* 声明一个结构体，用于保存从队列接收的值 */
    Data_t xReceivedStructure;
    BaseType_t xStatus;

    /* 此任务也在无限循环中定义 */
    for( ; ; )
    {
        /* 由于此任务只在发送任务处于阻塞状态时运行，
         * 而发送任务只有在队列满时才会阻塞，
         * 因此此任务应该总是发现队列是满的。3是队列长度。 */
        if( uxQueueMessagesWaiting( xQueue ) != 3 )
        {
            vPrintString( "队列应该已满！\r\n" );
        }

        /* 第一个参数是要从中接收数据的队列。
         * 该队列在调度器启动前创建，因此在该任务第一次运行前就已存在。
         *
         * 第二个参数是接收数据将被放置的缓冲区。
         * 在这种情况下，缓冲区只是一个变量的地址，
         * 该变量具有保存接收结构所需的大小。
         *
         * 最后一个参数是阻塞时间 - 如果队列已空，
         * 任务应保持在阻塞状态等待数据可用的最大时间。
         * 这里不需要阻塞时间，因为此任务只在队列满时运行，
         * 所以数据总是可用的。 */
        xStatus = xQueueReceive( xQueue, &xReceivedStructure, 0 );

        if( xStatus == pdPASS )
        {
            /* 数据成功从队列接收，打印接收到的值和数据源 */
            if( xReceivedStructure.eDataSource == eSender1 )
            {
                vPrintStringAndNumber( "来自发送者1 = ", xReceivedStructure.ucValue );
            }
            else
            {
                vPrintStringAndNumber( "来自发送者2 = ", xReceivedStructure.ucValue );
            }
        }
        else
        {
            /* 我们没有从队列接收到任何数据。这必须是一个错误，
             * 因为此任务只应在队列满时运行。 */
            vPrintString( "无法从队列接收数据。\r\n" );
        }
    }
}
