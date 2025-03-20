/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制的、         *
     *    支持多平台的软件，已经成为了事实上的标准。                        *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者都购买来帮助自己快速入门   *
     *    并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation         *
     *                                                                       *
     *    感谢您的支持！                                                     *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证(版本2)的条款重新分发和/或修改它，
    该许可证由自由软件基金会发布，并由FreeRTOS例外>>!修改!<<。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合作品，而不必提供FreeRTOS
    >>! 内核外部的专有组件的源代码。

    FreeRTOS的发布希望能够有所帮助，但不提供任何保证；甚至不提供对适销性或特定用途
    适用性的暗示保证。完整许可证文本可从以下链接获取：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格!

    ***************************************************************************
     *                                                                       *
     *    遇到问题？ 首先阅读FAQ "我的应用程序无法运行，可能是什么问题？"     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和Real Time Engineers Ltd.联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品的精选，包括FreeRTOS+Trace
    - 一个不可或缺的生产力工具、与DOS兼容的FAT文件系统以及我们的小型线程感知UDP/IP堆栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd将FreeRTOS授权给High Integrity Systems，
    以便在OpenRTOS品牌下销售。低成本的OpenRTOS许可证提供有票证支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供了一个经过安全工程处理且
    独立SIL3认证的版本，用于需要可证明可靠性的安全和任务关键型应用。

    1个制表符 == 4个空格!
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义
 *
 * 这些定义应根据您的特定硬件和应用程序需求进行调整。
 *
 * 这些参数在FreeRTOS.org网站上提供的FreeRTOS API文档的
 * '配置'部分和FreeRTOS参考手册中有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1                   /* 启用抢占式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                   /* 使用优化的任务选择方法 */
#define configMAX_PRIORITIES					5                   /* 定义最大任务优先级数量 */
#define configUSE_IDLE_HOOK						0                   /* 不使用空闲钩子函数 */
#define configUSE_TICK_HOOK						0                   /* 不使用系统节拍钩子函数 */
#define configTICK_RATE_HZ						( 1000 )            /* 系统节拍频率(Hz)，这是在模拟环境中，因此不是真正的实时 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小栈大小，在这个模拟环境中，栈只需要保存一个小结构，因为实际栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 总堆大小 */
#define configMAX_TASK_NAME_LEN					( 12 )              /* 任务名称的最大长度 */
#define configUSE_TRACE_FACILITY				0                   /* 不使用跟踪设施 */
#define configUSE_16_BIT_TICKS					0                   /* 不使用16位计数器(使用32位) */
#define configIDLE_SHOULD_YIELD					1                   /* 空闲任务应当让出CPU */
#define configUSE_MUTEXES						1                   /* 启用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0                   /* 不检查栈溢出，使用Win32模拟器时不适用 */
#define configUSE_RECURSIVE_MUTEXES				1                   /* 启用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10                  /* 队列注册表大小 */
#define configUSE_MALLOC_FAILED_HOOK			1                   /* 使用内存分配失败钩子 */
#define configUSE_APPLICATION_TASK_TAG			0                   /* 不使用应用程序任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1                   /* 启用计数信号量 */
#define configUSE_ALTERNATIVE_API				0                   /* 不使用替代API */
#define configUSE_QUEUE_SETS					1                   /* 启用队列集 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						1                   /* 启用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务优先级(最高优先级) */
#define configTIMER_QUEUE_LENGTH				2                   /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务栈深度 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0                   /* 不生成运行时统计信息 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0                   /* 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2                   /* 协程最大优先级数量 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将uxTaskGetSystemState()
   函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0                   /* 不使用统计格式化函数 */

/* 将以下定义设置为1以包含API函数，或设置为0以排除API函数。
   在大多数情况下，链接器会自动删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1                   /* 包含vTaskPrioritySet函数 */
#define INCLUDE_uxTaskPriorityGet				1                   /* 包含uxTaskPriorityGet函数 */
#define INCLUDE_vTaskDelete						1                   /* 包含vTaskDelete函数 */
#define INCLUDE_vTaskSuspend					1                   /* 包含vTaskSuspend函数 */
#define INCLUDE_vTaskDelayUntil					1                   /* 包含vTaskDelayUntil函数 */
#define INCLUDE_vTaskDelay						1                   /* 包含vTaskDelay函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1                   /* 包含uxTaskGetStackHighWaterMark函数 */
#define INCLUDE_xTaskGetSchedulerState			1                   /* 包含xTaskGetSchedulerState函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1                   /* 包含xTimerGetTimerDaemonTaskHandle函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1                   /* 包含xTaskGetIdleTaskHandle函数 */
#define INCLUDE_pcTaskGetTaskName				1                   /* 包含pcTaskGetTaskName函数 */
#define INCLUDE_eTaskGetState					1                   /* 包含eTaskGetState函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1                   /* 包含xSemaphoreGetMutexHolder函数 */
#define INCLUDE_xTimerPendFunctionCall			1                   /* 包含xTimerPendFunctionCall函数 */

/* 在开发过程中定义configASSERT()是一个好主意。configASSERT()
   使用与标准C assert()宏相同的语义。 */
#include <stdint.h>                                 /* 添加uint32_t类型定义 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
