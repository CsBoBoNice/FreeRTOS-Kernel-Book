/*
 *  Copyright Amazon.com Inc. or its affiliates. All Rights Reserved.
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  这个文件是FreeRTOS发行版的一部分。
 * 
 *  这包含了Windows端口实现的示例，这些示例在FreeRTOS书籍
 *  《掌握FreeRTOS实时内核》中列出。
 *
 */

/* FreeRTOS.org 头文件包含 */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* 演示所需的头文件包含 */
#include "supporting_functions.h"

/* 分别分配给单次触发定时器和自动重载定时器的周期 */
#define mainONE_SHOT_TIMER_PERIOD       ( pdMS_TO_TICKS( 3333UL ) ) /* 将3333毫秒转换为时钟节拍数 */
#define mainAUTO_RELOAD_TIMER_PERIOD    ( pdMS_TO_TICKS( 500UL ) )  /* 将500毫秒转换为时钟节拍数 */

/*-----------------------------------------------------------*/

/*
 * 定时器回调函数 - 被两种定时器共同使用
 */
static void prvTimerCallback( TimerHandle_t xTimer );

/*-----------------------------------------------------------*/

/* 定时器句柄在回调函数中使用，因此这些定时器被赋予文件作用域 */
static TimerHandle_t xAutoReloadTimer, xOneShotTimer;

int main( void )
{
    BaseType_t xTimer1Started, xTimer2Started;

    /* 创建单次触发定时器，并将创建的定时器句柄存储在xOneShotTimer中 */
    xOneShotTimer = xTimerCreate( 
                                  "OneShot",                 /* 定时器的文本名称 - 不被FreeRTOS使用，仅用于调试 */
                                  mainONE_SHOT_TIMER_PERIOD, /* 定时器周期（以时钟节拍为单位） */
                                  pdFALSE,                   /* 设置uxAutoReload为pdFALSE创建单次触发定时器 */
                                  0,                         /* 定时器ID初始化为0 */
                                  prvTimerCallback );        /* 由创建的定时器使用的回调函数 */

    /* 创建自动重载定时器，并将创建的定时器句柄存储在xAutoReloadTimer中 */
    xAutoReloadTimer = xTimerCreate( 
                                     "AutoReload",                 /* 定时器的文本名称 - 不被FreeRTOS使用，仅用于调试 */
                                     mainAUTO_RELOAD_TIMER_PERIOD, /* 定时器周期（以时钟节拍为单位） */
                                     pdTRUE,                       /* 设置uxAutoReload为pdTRUE创建自动重载定时器 */
                                     0,                            /* 定时器ID初始化为0 */
                                     prvTimerCallback );           /* 由创建的定时器使用的回调函数 */

    /* 检查定时器是否成功创建 */
    if( ( xOneShotTimer != NULL ) && ( xAutoReloadTimer != NULL ) )
    {
        /* 启动定时器，使用阻塞时间为0（无阻塞时间）。
         * 调度器尚未启动，所以这里指定的任何阻塞时间都会被忽略。 */
        xTimer1Started = xTimerStart( xOneShotTimer, 0 );
        xTimer2Started = xTimerStart( xAutoReloadTimer, 0 );

        /* xTimerStart()的实现使用定时器命令队列，如果定时器命令队列已满，
         * xTimerStart()将失败。定时器服务任务直到调度器启动后才会被创建，
         * 所以所有发送到命令队列的命令将保留在队列中，直到调度器启动后才会处理。
         * 检查两次调用xTimerStart()是否都成功。 */
        if( ( xTimer1Started == pdPASS ) && ( xTimer2Started == pdPASS ) )
        {
            /* 启动调度器 */
            vTaskStartScheduler();
        }
    }

    /* 如果调度器启动成功，则不应该到达以下代码，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存来创建空闲任务和（如果配置了）定时器任务时才会返回。
     * 内存管理和陷阱堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void prvTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow;
    uint32_t ulExecutionCount;

    /* 该软件定时器到期次数的计数存储在定时器的ID中。
     * 获取ID，递增它，然后将其保存为新的ID值。
     * ID是一个void指针，因此将其转换为uint32_t。 */
    ulExecutionCount = ( uint32_t ) pvTimerGetTimerID( xTimer );
    ulExecutionCount++;
    vTimerSetTimerID( xTimer, ( void * ) ulExecutionCount );

    /* 获取当前的时钟节拍计数 */
    xTimeNow = xTaskGetTickCount();

    /* 单次触发定时器的句柄在定时器创建时存储在xOneShotTimer中。
     * 将传入此函数的句柄与xOneShotTimer进行比较，以确定是单次触发定时器
     * 还是自动重载定时器到期，然后输出一个字符串显示回调执行的时间。 */
    if( xTimer == xOneShotTimer )
    {
        vPrintStringAndNumber( "单次触发定时器回调正在执行", xTimeNow );
    }
    else
    {
        /* xTimer不等于xOneShotTimer，因此一定是自动重载定时器到期 */
        vPrintStringAndNumber( "自动重载定时器回调正在执行", xTimeNow );

        if( ulExecutionCount == 5 )
        {
            /* 自动重载定时器执行5次后停止。
             * 此回调函数在RTOS守护进程任务的上下文中执行，
             * 因此不能调用可能导致守护进程任务进入阻塞状态的函数。
             * 因此使用阻塞时间为0。 */
            xTimerStop( xTimer, 0 );
        }
    }
}
/*-----------------------------------------------------------*/
