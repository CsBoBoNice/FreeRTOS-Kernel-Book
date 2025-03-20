/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    All rights reserved

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费但专业开发的、稳健的、严格质量控制的、         *
     *    支持良好的跨平台软件，已成为事实上的标准。                          *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者来帮助自己快速入门         *
     *    并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation         *
     *                                                                       *
     *    感谢您的支持！                                                     *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（版本2）的条款重新分发和/或
    修改它，该许可证由自由软件基金会发布，并由FreeRTOS例外条款修改。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合工作，而不必提供
    >>! FreeRTOS内核之外的专有组件的源代码。

    FreeRTOS的分发希望能够有所帮助，但不提供任何保证；甚至没有对适销性或
    特定用途适用性的暗示保证。完整的许可证文本可从以下链接获取：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？首先阅读FAQ"我的应用程序无法运行，可能是什么原因？"      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证以及
    Real Time Engineers Ltd.的联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品的选择，包括
    FreeRTOS+Trace - 一个不可或缺的生产力工具、与DOS兼容的FAT文件系统
    以及我们的小型线程感知UDP/IP协议栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd授权FreeRTOS给
    High Integrity Systems，在OpenRTOS品牌下销售。低成本OpenRTOS许可证
    提供有票证支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供了一个经过安全
    工程和独立SIL3认证的版本，用于需要可证明的可靠性的安全和任务关键型应用。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/* 包含stdint.h以获取uint32_t类型的定义 */
#include <stdint.h>

/*-----------------------------------------------------------
 * 应用程序特定的定义。
 *
 * 这些定义应根据您特定的硬件和应用程序要求进行调整。
 *
 * 这些参数在FreeRTOS.org网站上和FreeRTOS参考手册中的"配置"部分有详细说明。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1           /* 设置为1启用抢占式调度 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1           /* 设置为1启用硬件优化的任务选择 */
#define configMAX_PRIORITIES					5           /* 定义系统最大优先级数量为5 */
#define configUSE_IDLE_HOOK						0           /* 设置为0禁用空闲钩子函数 */
#define configUSE_TICK_HOOK						0           /* 设置为0禁用时钟中断钩子函数 */
#define configTICK_RATE_HZ						( 1000 )    /* 系统时钟频率为1000Hz，因为这是模拟环境，所以并非真实时间 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小堆栈大小，在这个模拟环境中，实际堆栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 总堆大小为20KB */
#define configMAX_TASK_NAME_LEN					( 12 )      /* 任务名称最大长度为12个字符 */
#define configUSE_TRACE_FACILITY				0           /* 设置为0禁用跟踪功能 */
#define configUSE_16_BIT_TICKS					0           /* 设置为0使用32位系统时钟计数器 */
#define configIDLE_SHOULD_YIELD					1           /* 设置为1让空闲任务在有同等优先级任务就绪时让出CPU */
#define configUSE_MUTEXES						1           /* 设置为1启用互斥量功能 */
#define configCHECK_FOR_STACK_OVERFLOW			0           /* 禁用堆栈溢出检查，在Win32模拟器中不适用 */
#define configUSE_RECURSIVE_MUTEXES				1           /* 设置为1启用递归互斥量功能 */
#define configQUEUE_REGISTRY_SIZE				10          /* 队列注册表大小为10个条目 */
#define configUSE_MALLOC_FAILED_HOOK			1           /* 设置为1启用内存分配失败钩子函数 */
#define configUSE_APPLICATION_TASK_TAG			0           /* 设置为0禁用应用任务标记功能 */
#define configUSE_COUNTING_SEMAPHORES			1           /* 设置为1启用计数信号量功能 */
#define configUSE_ALTERNATIVE_API				0           /* 设置为0不使用替代API */
#define configUSE_QUEUE_SETS					1           /* 设置为1启用队列集功能 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						1           /* 设置为1启用软件定时器功能 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务优先级为最高优先级 */
#define configTIMER_QUEUE_LENGTH				2           /* 定时器命令队列长度为2 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务堆栈深度为最小堆栈大小的2倍 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0           /* 设置为0禁用运行时统计收集 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0           /* 设置为0禁用协程功能 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2           /* 协程最大优先级数量为2 */

/* 这个演示不使用一个或多个示例统计格式化函数，这些函数将由uxTaskGetSystemState()
   函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0           /* 设置为0禁用统计格式化函数 */

/* 将以下定义设置为1以包含API函数，或设置为零以排除API函数。
   在大多数情况下，链接器会自动删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1           /* 包含任务优先级设置函数 */
#define INCLUDE_uxTaskPriorityGet				1           /* 包含获取任务优先级函数 */
#define INCLUDE_vTaskDelete						1           /* 包含任务删除函数 */
#define INCLUDE_vTaskSuspend					1           /* 包含任务挂起函数 */
#define INCLUDE_vTaskDelayUntil					1           /* 包含任务绝对延时函数 */
#define INCLUDE_vTaskDelay						1           /* 包含任务相对延时函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1           /* 包含获取任务堆栈最高水位标记函数 */
#define INCLUDE_xTaskGetSchedulerState			1           /* 包含获取调度器状态函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1           /* 包含获取定时器守护任务句柄函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1           /* 包含获取空闲任务句柄函数 */
#define INCLUDE_pcTaskGetTaskName				1           /* 包含获取任务名称函数 */
#define INCLUDE_eTaskGetState					1           /* 包含获取任务状态函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1           /* 包含获取互斥量持有者函数 */
#define INCLUDE_xTimerPendFunctionCall			1           /* 包含挂起函数调用到定时器服务任务函数 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()使用与标准C assert()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
