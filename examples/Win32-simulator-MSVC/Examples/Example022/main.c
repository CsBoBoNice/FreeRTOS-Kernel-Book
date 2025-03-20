/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 *
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  此文件是FreeRTOS发行版的一部分。
 *
 *  本文件包含FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows端口实现。
 *
 */

/* 标准头文件 */
#include <stdint.h>
#include <stdlib.h>

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "event_groups.h"
#include "timers.h" /* 用于xTimerPendFunctionCallFromISR()函数 */

/* 演示包含文件 */
#include "supporting_functions.h"

/* 本示例中使用的模拟中断编号。数字0到2由FreeRTOS Windows端口本身使用，
 * 因此3是应用程序可用的第一个编号。 */
#define mainINTERRUPT_NUMBER    3

/* 事件组中事件位的定义 */
#define mainFIRST_TASK_BIT      ( 1UL << 0UL ) /* 事件位0，由任务设置 */
#define mainSECOND_TASK_BIT     ( 1UL << 1UL ) /* 事件位1，由任务设置 */
#define mainISR_BIT             ( 1UL << 2UL ) /* 事件位2，由ISR(中断服务程序)设置 */

/* 要创建的任务声明 */
static void vIntegerGenerator( void * pvParameters );
static void vEventBitSettingTask( void * pvParameters );
static void vEventBitReadingTask( void * pvParameters );

/* 可以延迟在RTOS守护任务中运行的函数。
 * 该函数使用pvParameter1参数打印传递给它的字符串。 */
void vPrintStringFromDaemonTask( void * pvParameter1,
                                 uint32_t ulParameter2 );

/* (模拟)中断的服务例程。
 * 这是在事件组中设置事件位的中断。 */
static uint32_t ulEventBitSettingISR( void );

/*-----------------------------------------------------------*/

/* 声明事件组，其中的位由任务和ISR同时设置 */
EventGroupHandle_t xEventGroup;

int main( void )
{
    /* 在使用事件组之前，必须先创建它 */
    xEventGroup = xEventGroupCreate();

    /* 创建在事件组中设置事件位的任务 */
    xTaskCreate( vEventBitSettingTask, "BitSetter", 1000, NULL, 1, NULL );

    /* 创建等待事件组中事件位被设置的任务 */
    xTaskCreate( vEventBitReadingTask, "BitReader", 1000, NULL, 2, NULL );

    /* 创建用于定期生成软件中断的任务 */
    xTaskCreate( vIntegerGenerator, "IntGen", 1000, NULL, 3, NULL );

    /* 安装软件中断的处理程序。执行此操作所需的语法取决于所使用的FreeRTOS端口。
     * 此处显示的语法只能与FreeRTOS Windows端口一起使用，其中此类中断只是模拟的。 */
    vPortSetInterruptHandler( mainINTERRUPT_NUMBER, ulEventBitSettingISR );

    /* 启动调度器，使创建的任务开始执行 */
    vTaskStartScheduler();

    /* 由于vTaskStartScheduler()只有在没有足够的FreeRTOS堆内存可用于创建
     * 空闲任务和（如果配置了）定时器任务时才会返回，因此不应该执行到以下代码行。
     * 堆管理和捕获堆耗尽的技术在书中有详细描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vEventBitSettingTask( void * pvParameters )
{
    const TickType_t xDelay200ms = pdMS_TO_TICKS( 200UL ); /* 将200毫秒转换为系统节拍数 */

    for( ; ; )
    {
        /* 在开始下一个循环之前延迟一小段时间 */
        vTaskDelay( xDelay200ms );

        /* 打印消息说任务即将设置事件位0，然后设置事件位0 */
        vPrintString( "位设置任务 -\t 即将设置位0.\r\n" );
        xEventGroupSetBits( xEventGroup, mainFIRST_TASK_BIT );

        /* 在设置此任务内设置的另一个位之前短暂延迟 */
        vTaskDelay( xDelay200ms );

        /* 打印消息说任务即将设置事件位1，然后设置事件位1 */
        vPrintString( "位设置任务 -\t 即将设置位1.\r\n" );
        xEventGroupSetBits( xEventGroup, mainSECOND_TASK_BIT );
    }
}
/*-----------------------------------------------------------*/

static uint32_t ulEventBitSettingISR( void )
{
    BaseType_t xHigherPriorityTaskWoken;

/* 字符串不会在中断服务中打印，而是发送到RTOS守护任务以进行打印。
 * 因此声明为静态，以确保编译器不会在ISR的栈上分配字符串（因为
 * 从守护任务打印字符串时，ISR的栈帧将不存在）。 */
    static const char * pcString = "位设置ISR -\t 即将设置位2.\r\n";

    /* 如常，xHigherPriorityTaskWoken初始化为pdFALSE */
    xHigherPriorityTaskWoken = pdFALSE;

    /* 打印消息说位2即将被设置。无法从ISR打印消息，
     * 因此通过挂起函数调用在RTOS守护任务的上下文中运行，
     * 将实际输出延迟到RTOS守护任务。 */
    xTimerPendFunctionCallFromISR( vPrintStringFromDaemonTask, ( void * ) pcString, 0, &xHigherPriorityTaskWoken );

    /* 在事件组中设置位2 */
    xEventGroupSetBitsFromISR( xEventGroup, mainISR_BIT, &xHigherPriorityTaskWoken );

    /* xEventGroupSetBitsFromISR()写入定时器命令队列。如果写入定时器命令队列
     * 导致RTOS守护任务离开阻塞状态，并且如果RTOS守护任务的优先级高于
     * 当前执行任务的优先级（被该中断中断的任务），那么xHigherPriorityTaskWoken
     * 将在xEventGroupSetBitsFromISR()内部被设置为pdTRUE。
     *
     * xHigherPriorityTaskWoken用作portYIELD_FROM_ISR()的参数。
     * 如果xHigherPriorityTaskWoken等于pdTRUE，则调用portYIELD_FROM_ISR()
     * 将请求上下文切换。如果xHigherPriorityTaskWoken仍为pdFALSE，
     * 则调用portYIELD_FROM_ISR()将没有效果。
     *
     * Windows端口使用的portYIELD_FROM_ISR()实现包含返回语句，
     * 这就是为什么此函数不显式返回值的原因。 */
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
/*-----------------------------------------------------------*/

static void vEventBitReadingTask( void * pvParameters )
{
    const EventBits_t xBitsToWaitFor = ( mainFIRST_TASK_BIT | mainSECOND_TASK_BIT | mainISR_BIT ); /* 等待三个事件位 */
    EventBits_t xEventGroupValue;

    for( ; ; )
    {
        /* 阻塞等待事件组中事件位被设置 */
        xEventGroupValue = xEventGroupWaitBits( /* 要读取的事件组 */
            xEventGroup,

            /* 要测试的位 */
            xBitsToWaitFor,

            /* 如果解除阻塞条件满足，
             * 则退出时清除位 */
            pdTRUE,

            /* 不等待所有位 */
            pdFALSE,

            /* 不超时 */
            portMAX_DELAY );

        /* 为每个被设置的位打印消息 */
        if( ( xEventGroupValue & mainFIRST_TASK_BIT ) != 0 )
        {
            vPrintString( "位读取任务 -\t 事件位0已设置\r\n" );
        }

        if( ( xEventGroupValue & mainSECOND_TASK_BIT ) != 0 )
        {
            vPrintString( "位读取任务 -\t 事件位1已设置\r\n" );
        }

        if( ( xEventGroupValue & mainISR_BIT ) != 0 )
        {
            vPrintString( "位读取任务 -\t 事件位2已设置\r\n" );
        }

        vPrintString( "\r\n" );
    }
}
/*-----------------------------------------------------------*/

void vPrintStringFromDaemonTask( void * pvParameter1,
                                 uint32_t ulParameter2 )
{
    /* 要打印的字符串通过pvParameter1参数传递给此函数 */
    vPrintString( ( const char * ) pvParameter1 );
}
/*-----------------------------------------------------------*/

static void vIntegerGenerator( void * pvParameters )
{
    TickType_t xLastExecutionTime;
    const TickType_t xDelay500ms = pdMS_TO_TICKS( 500UL ); /* 将500毫秒转换为系统节拍数 */

    /* 初始化vTaskDelayUntil()使用的变量 */
    xLastExecutionTime = xTaskGetTickCount();

    for( ; ; )
    {
        /* 这是一个周期性任务。阻塞直到再次运行的时间到来。
         * 该任务将每500毫秒执行一次。 */
        vTaskDelayUntil( &xLastExecutionTime, xDelay500ms );

        /* 生成将在事件组中设置位的中断 */
        vPortGenerateSimulatedInterrupt( mainINTERRUPT_NUMBER );
    }
}
