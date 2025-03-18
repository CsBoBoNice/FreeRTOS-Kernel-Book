/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 * 
 *  此文件包含FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows端口实现。
 *
 */

/* 标准包含文件 */
#include <conio.h>

/* FreeRTOS包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* 演示包含文件 */
#include "supporting_functions.h"

/* 分配给单次触发定时器的周期 */
#define mainBACKLIGHT_TIMER_PERIOD    ( pdMS_TO_TICKS( 5000UL ) ) /* 将5000毫秒转换为系统节拍数 */

/*-----------------------------------------------------------*/

/*
 * 定时器使用的回调函数
 * 此函数在定时器到期时被调用，用于关闭背光
 */
static void prvBacklightTimerCallback( TimerHandle_t xTimer );

/*
 * 在真实应用程序中，运行在真实目标上时，可能会在中断中读取按钮按下事件。
 * 这允许应用程序由事件驱动，并防止在没有按键按下时轮询按键而浪费CPU时间。
 * 在使用FreeRTOS Windows端口时，使用真实中断是不切实际的，
 * 因此创建vKeyHitTask()任务来提供按键读取功能，通过简单地轮询键盘实现。
 */
static void vKeyHitTask( void * pvParameters );

/*-----------------------------------------------------------*/

/* 这个示例没有真实的背光可以打开和关闭，
 * 所以使用以下变量来保存背光的状态。 */
static BaseType_t xSimulatedBacklightOn = pdFALSE;  /* 初始化为关闭状态 */

/* 用于关闭背光的软件定时器 */
static TimerHandle_t xBacklightTimer = NULL;

/*-----------------------------------------------------------*/

int main( void )
{
    /* 程序开始时背光处于关闭状态 */
    xSimulatedBacklightOn = pdFALSE;

    /* 创建单次触发定时器，并将创建的定时器句柄存储在xBacklightTimer中 */
    xBacklightTimer = xTimerCreate( 
        "Backlight",                  /* 定时器的文本名称 - 不被FreeRTOS使用 */
        mainBACKLIGHT_TIMER_PERIOD,   /* 定时器的周期（以节拍为单位） */
        pdFALSE,                      /* 设置uxAutoReload为pdFALSE创建单次触发定时器 */
        0,                            /* 定时器ID在此示例中未使用 */
        prvBacklightTimerCallback     /* 由创建的定时器使用的回调函数 */
    ); 

    /* 在真实应用程序中，运行在真实目标上时，可能会在中断中读取按钮按下事件。
     * 这允许应用程序由事件驱动，并防止在没有按键按下时轮询按键而浪费CPU时间。
     * 在使用FreeRTOS Windows端口时，使用真实中断是不切实际的，
     * 因此创建vKeyHitTask()任务来提供按键读取功能，通过简单地轮询键盘实现。 */
    xTaskCreate( 
        vKeyHitTask,              /* 任务函数 */
        "Key poll",               /* 任务名称 */
        configMINIMAL_STACK_SIZE, /* 任务栈大小 */
        NULL,                     /* 无任务参数 */
        tskIDLE_PRIORITY,         /* 任务优先级与空闲任务相同 */
        NULL                      /* 不需要保存任务句柄 */
    );

    /* 启动定时器 */
    xTimerStart( xBacklightTimer, 0 );

    /* 启动调度器 */
    vTaskStartScheduler();

    /* 与之前的示例一样，vTaskStartScheduler()不应该返回，
     * 因此不应到达以下几行代码。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void prvBacklightTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();  /* 获取当前系统节拍计数 */

    /* 背光定时器已到期，关闭背光 */
    xSimulatedBacklightOn = pdFALSE;

    /* 打印关闭背光的时间 */
    vPrintStringAndNumber( "定时器到期，在时间点关闭背光\t", xTimeNow );
}
/*-----------------------------------------------------------*/

static void vKeyHitTask( void * pvParameters )
{
    const TickType_t xShortDelay = pdMS_TO_TICKS( 50 );  /* 短延迟50毫秒 */
    extern BaseType_t xKeyPressesStopApplication;        /* 外部变量声明 */
    TickType_t xTimeNow;

    /* 此示例使用按键操作，因此防止按键操作用于结束应用程序 */
    xKeyPressesStopApplication = pdFALSE;

    vPrintString( "按任意键打开背光。\r\n" );

    /* 在真实应用程序中，运行在真实目标上时，可能会在中断中读取按钮按下事件。
     * 这允许应用程序由事件驱动，并防止在没有按键按下时轮询按键而浪费CPU时间。
     * 在使用FreeRTOS Windows端口时，使用真实中断是不切实际的，
     * 因此创建此任务来提供按键读取功能，通过简单地轮询键盘实现。 */
    for( ; ; )
    {
        /* 检查是否有按键被按下 */
        if( _kbhit() != 0 )
        {
            /* 记录检测到按键按下的时间 */
            xTimeNow = xTaskGetTickCount();

            /* 按键已被按下 */
            if( xSimulatedBacklightOn == pdFALSE )
            {
                /* 背光之前是关闭的，所以打开它并打印背光打开的时间 */
                xSimulatedBacklightOn = pdTRUE;
                vPrintStringAndNumber( "按键按下，在时间点打开背光\t", xTimeNow );
            }
            else
            {
                /* 背光已经打开，所以打印一条消息表示软件定时器将被重置，
                 * 并打印重置的时间 */
                vPrintStringAndNumber( "按键按下，在时间点重置软件定时器\t", xTimeNow );
            }

            /* 重置软件定时器。如果背光之前是关闭的，
             * 这个调用将启动定时器。如果背光之前是打开的，
             * 这个调用将重新启动定时器。
             * 真实应用程序可能会在中断中读取按键按下事件。
             * 如果这个函数是中断服务例程，则必须使用xTimerResetFromISR()
             * 而不是xTimerReset()。 */
            xTimerReset( xBacklightTimer, xShortDelay );

            /* 读取并丢弃被按下的键 */
            ( void ) _getch();
        }

        /* 不要太快地轮询 */
        vTaskDelay( xShortDelay );
    }
}
/*-----------------------------------------------------------*/
