/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了《掌握FreeRTOS实时内核》一书中所列举示例的Windows端口实现。
 *
 */

/* 标准包含 - 用于初始化随机数生成器 */
#include <time.h>

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"

/* 演示包含文件 */
#include "supporting_functions.h"

/* 事件组中事件位的定义 */
#define mainFIRST_TASK_BIT     ( 1UL << 0UL ) /* 事件位0，由第一个任务设置 */
#define mainSECOND_TASK_BIT    ( 1UL << 1UL ) /* 事件位1，由第二个任务设置 */
#define mainTHIRD_TASK_BIT     ( 1UL << 2UL ) /* 事件位2，由第三个任务设置 */

/* 伪随机数生成函数 - 在本文件中实现，因为MSVC的rand()函数可能产生意外结果 */
static uint32_t prvRand( void );
static void prvSRand( uint32_t ulSeed );

/* 将创建三个该任务的实例 */
static void vSyncingTask( void * pvParameters );

/*-----------------------------------------------------------*/

/* 伪随机数生成器使用的变量 */
static uint32_t ulNextRand;

/* 声明用于同步三个任务的事件组 */
EventGroupHandle_t xEventGroup;

int main( void )
{
    /* 本例中创建的任务会随机阻塞一段时间。
     * 阻塞时间使用rand()生成 - 初始化随机数生成器 */
    prvSRand( ( uint32_t ) time( NULL ) );

    /* 在使用事件组之前，必须先创建它 */
    xEventGroup = xEventGroupCreate();

    /* 创建三个任务实例。每个任务被赋予不同的名称，
     * 稍后打印出来以直观地指示哪个任务正在执行。
     * 当任务达到其同步点时使用的事件位通过任务参数传递给任务。 */
    xTaskCreate( vSyncingTask, "Task 1", 1000, ( void * ) mainFIRST_TASK_BIT, 1, NULL );
    xTaskCreate( vSyncingTask, "Task 2", 1000, ( void * ) mainSECOND_TASK_BIT, 1, NULL );
    xTaskCreate( vSyncingTask, "Task 3", 1000, ( void * ) mainTHIRD_TASK_BIT, 1, NULL );

    /* 启动调度器，使创建的任务开始执行 */
    vTaskStartScheduler();

    /* 下面的代码行不应该被执行到，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存可用于创建空闲任务和
     * （如果配置了）定时器任务时才会返回。堆管理和陷阱堆
     * 耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vSyncingTask( void * pvParameters )
{
    /* 所有任务同步位的组合 */
    const EventBits_t uxAllSyncBits = ( mainFIRST_TASK_BIT | mainSECOND_TASK_BIT | mainTHIRD_TASK_BIT );
    const TickType_t xMaxDelay = pdMS_TO_TICKS( 4000UL ); /* 最大延迟时间（毫秒转为时钟节拍） */
    const TickType_t xMinDelay = pdMS_TO_TICKS( 200UL );  /* 最小延迟时间（毫秒转为时钟节拍） */
    TickType_t xDelayTime;                                /* 实际延迟时间变量 */
    EventBits_t uxThisTasksSyncBit;                       /* 当前任务使用的同步位 */

    /* 创建了三个此任务的实例 - 每个任务在同步中使用不同的事件位。
     * 此任务实例使用的事件位通过任务的参数传入。
     * 将其存储在uxThisTasksSyncBit变量中。 */
    uxThisTasksSyncBit = ( EventBits_t ) pvParameters;

    for( ; ; )
    {
        /* 通过延迟一个伪随机时间来模拟此任务执行某些操作所需的时间。
         * 这可以防止所有三个任务实例同时到达同步点，
         * 并使示例的行为更容易观察。 */
        xDelayTime = ( prvRand() % xMaxDelay ) + xMinDelay;
        vTaskDelay( xDelayTime );

        /* 打印一条消息，表明此任务已达到其同步点。
         * pcTaskGetTaskName()是一个API函数，返回创建任务时分配给任务的名称。 */
        vPrintTwoStrings( pcTaskGetTaskName( NULL ), "已到达同步点" );

        /* 等待所有任务都达到各自的同步点 */
        xEventGroupSync( 
            /* 用于同步的事件组 */
            xEventGroup,

            /* 由此任务设置的位，表示它已达到同步点 */
            uxThisTasksSyncBit,

            /* 要等待的位，参与同步的每个任务对应一个位 */
            uxAllSyncBits,

            /* 无限期等待所有三个任务达到同步点 */
            portMAX_DELAY );

        /* 打印一条消息，表明此任务已通过其同步点。
         * 由于使用了无限期延迟，因此只有在所有任务都达到
         * 各自的同步点后，才会执行下面的代码行。 */
        vPrintTwoStrings( pcTaskGetTaskName( NULL ), "已退出同步点" );
    }
}
/*-----------------------------------------------------------*/

static uint32_t prvRand( void )
{
    const uint32_t ulMultiplier = 0x015a4e35UL, ulIncrement = 1UL;
    uint32_t ulReturn;

    /* 生成伪随机数的工具函数，因为MSVC的rand()函数
     * 可能产生意外结果。这里使用线性同余法生成随机数。 */
    taskENTER_CRITICAL();
    ulNextRand = ( ulMultiplier * ulNextRand ) + ulIncrement;
    ulReturn = ( ulNextRand >> 16UL ) & 0x7fffUL;
    taskEXIT_CRITICAL();
    return ulReturn;
}
/*-----------------------------------------------------------*/

static void prvSRand( uint32_t ulSeed )
{
    /* 用于初始化伪随机数生成器的工具函数 */
    ulNextRand = ulSeed;
}
/*-----------------------------------------------------------*/
