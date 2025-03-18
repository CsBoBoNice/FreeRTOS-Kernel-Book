/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 头文件包含 */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* 示例程序相关的头文件 */
#include "supporting_functions.h"

/* 分别为单次触发定时器和自动重载定时器分配的周期 */
#define mainONE_SHOT_TIMER_PERIOD       ( pdMS_TO_TICKS( 3333UL ) ) /* 单次触发定时器周期为3333毫秒 */
#define mainAUTO_RELOAD_TIMER_PERIOD    ( pdMS_TO_TICKS( 500UL ) )  /* 自动重载定时器周期为500毫秒 */

/*-----------------------------------------------------------*/

/*
 * 单次触发定时器和自动重载定时器分别使用的回调函数
 */
static void prvOneShotTimerCallback( TimerHandle_t xTimer );
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer );

/*-----------------------------------------------------------*/

int main( void )
{
    TimerHandle_t xAutoReloadTimer, xOneShotTimer;
    BaseType_t xTimer1Started, xTimer2Started;

    /* 创建单次触发软件定时器，将创建的软件定时器句柄存储在xOneShotTimer中 */
    xOneShotTimer = xTimerCreate( 
                      "OneShot",                 /* 软件定时器的文本名称 - FreeRTOS不使用此名称，仅用于调试 */
                      mainONE_SHOT_TIMER_PERIOD, /* 软件定时器的周期（以节拍为单位） */
                      pdFALSE,                   /* 将uxAutoReload设置为pdFALSE创建单次触发软件定时器 */
                      0,                         /* 本示例不使用定时器ID */
                      prvOneShotTimerCallback ); /* 由正在创建的软件定时器使用的回调函数 */

    /* 创建自动重载软件定时器，将创建的软件定时器句柄存储在xAutoReloadTimer中 */
    xAutoReloadTimer = xTimerCreate( 
                         "AutoReload",                 /* 软件定时器的文本名称 - FreeRTOS不使用此名称，仅用于调试 */
                         mainAUTO_RELOAD_TIMER_PERIOD, /* 软件定时器的周期（以节拍为单位） */
                         pdTRUE,                       /* 将uxAutoReload设置为pdTRUE创建自动重载软件定时器 */
                         0,                            /* 本示例不使用定时器ID */
                         prvAutoReloadTimerCallback ); /* 由正在创建的软件定时器使用的回调函数 */

    /* 检查定时器是否创建成功 */
    if( ( xOneShotTimer != NULL ) && ( xAutoReloadTimer != NULL ) )
    {
        /* 启动软件定时器，使用阻塞时间为0（无阻塞）。
         * 调度器尚未启动，因此此处指定的任何阻塞时间都将被忽略。 */
        xTimer1Started = xTimerStart( xOneShotTimer, 0 );
        xTimer2Started = xTimerStart( xAutoReloadTimer, 0 );

        /* xTimerStart()的实现使用定时器命令队列，如果定时器命令队列已满，
         * 则xTimerStart()将失败。定时器服务任务直到调度器启动后才被创建，
         * 所以所有发送到命令队列的命令都将保留在队列中，直到调度器启动后。
         * 检查两次调用xTimerStart()是否都成功。 */
        if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
        {
            /* 启动调度器 */
            vTaskStartScheduler();
        }
    }

    /* 如果调度器启动，则永远不应到达下面的代码，因为vTaskStartScheduler()只有在
     * 没有足够的FreeRTOS堆内存可用于创建空闲任务和（如果配置了）定时器任务时才会返回。
     * 堆内存管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void prvOneShotTimerCallback( TimerHandle_t xTimer )
{
    static TickType_t xTimeNow;

    /* 获取当前的节拍计数 */
    xTimeNow = xTaskGetTickCount();

    /* 输出一个字符串，显示回调执行的时间 */
    vPrintStringAndNumber( "单次触发定时器回调执行", xTimeNow );
}
/*-----------------------------------------------------------*/

static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
    static TickType_t xTimeNow;

    /* 获取当前的节拍计数 */
    xTimeNow = xTaskGetTickCount();

    /* 输出一个字符串，显示回调执行的时间 */
    vPrintStringAndNumber( "自动重载定时器回调执行", xTimeNow );
}
/*-----------------------------------------------------------*/
