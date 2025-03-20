/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>! NOTE: The modification to the GPL is included to allow you to distribute
    >>! a combined work that includes FreeRTOS without being obliged to provide
    >>! the source code for proprietary components outside of the FreeRTOS
    >>! kernel.

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>  /* 添加 stdint.h 以解决 uint32_t 未定义的问题 */

/*-----------------------------------------------------------
 * 应用程序特定定义。
 *
 * 这些定义应根据您特定的硬件和应用程序需求进行调整。
 *
 * 这些参数在 FreeRTOS.org 网站上提供的 FreeRTOS API 文档的
 * "配置"部分和 FreeRTOS 参考手册中有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1                   /* 启用抢占式调度 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                   /* 使用优化的任务选择方法 */
#define configMAX_PRIORITIES					5                   /* 最大优先级数量 */
#define configUSE_IDLE_HOOK						0                   /* 不使用空闲钩子 */
#define configUSE_TICK_HOOK						0                   /* 不使用时钟钩子 */
#define configTICK_RATE_HZ						( 1000 )            /* 这是模拟环境，因此不是实时的 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 在这个模拟环境中，栈只需要容纳一个小结构，因为真正的栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 堆总大小 */
#define configMAX_TASK_NAME_LEN					( 12 )              /* 最大任务名称长度 */
#define configUSE_TRACE_FACILITY				0                   /* 不使用跟踪功能 */
#define configUSE_16_BIT_TICKS					0                   /* 不使用16位时钟节拍 */
#define configIDLE_SHOULD_YIELD					1                   /* 空闲任务应该让出CPU */
#define configUSE_MUTEXES						1                   /* 启用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0                   /* 不检查栈溢出（使用Win32模拟器时不适用） */
#define configUSE_RECURSIVE_MUTEXES				1                   /* 启用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10                  /* 队列注册表大小 */
#define configUSE_MALLOC_FAILED_HOOK			1                   /* 使用内存分配失败钩子 */
#define configUSE_APPLICATION_TASK_TAG			0                   /* 不使用应用任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1                   /* 启用计数信号量 */
#define configUSE_ALTERNATIVE_API				0                   /* 不使用替代API */
#define configUSE_QUEUE_SETS					1                   /* 启用队列集 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						0                   /* 不使用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器任务优先级 */
#define configTIMER_QUEUE_LENGTH				20                  /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务栈深度 */

/* 运行时统计信息收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0                   /* 不生成运行时统计信息 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0                   /* 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2                   /* 协程最大优先级 */

/* 这个演示不使用一个或多个示例统计格式化函数，
   这些函数将 uxTaskGetSystemState() 函数提供的原始数据格式化为
   人类可读的ASCII格式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0                   /* 不使用统计格式化函数 */

/* 将以下定义设置为1可包含API函数，设置为0可排除API函数。
   在大多数情况下，链接器会自动删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1                   /* 包含任务优先级设置函数 */
#define INCLUDE_uxTaskPriorityGet				1                   /* 包含获取任务优先级函数 */
#define INCLUDE_vTaskDelete						1                   /* 包含删除任务函数 */
#define INCLUDE_vTaskSuspend					1                   /* 包含挂起任务函数 */
#define INCLUDE_vTaskDelayUntil					1                   /* 包含任务延时到函数 */
#define INCLUDE_vTaskDelay						1                   /* 包含任务延时函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1                   /* 包含获取任务栈高水位函数 */
#define INCLUDE_xTaskGetSchedulerState			1                   /* 包含获取调度器状态函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1                   /* 包含获取定时器守护任务句柄函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1                   /* 包含获取空闲任务句柄函数 */
#define INCLUDE_pcTaskGetTaskName				1                   /* 包含获取任务名称函数 */
#define INCLUDE_eTaskGetState					1                   /* 包含获取任务状态函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1                   /* 包含获取互斥量持有者函数 */
#define INCLUDE_xTimerPendFunctionCall			1                   /* 包含定时器挂起函数调用 */

/* 在开发时定义 configASSERT() 是个好主意。configASSERT() 
   使用与标准C assert() 宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
