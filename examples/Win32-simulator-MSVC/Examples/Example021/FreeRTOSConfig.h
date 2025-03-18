/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、强健的、严格质量控制的、         *
     *    支持多平台的软件，已成为事实上的标准。                             *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者兼而有之来帮助自己快速     *
     *    入门并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation      *
     *                                                                       *
     *    感谢您的支持！                                                     *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据自由软件基金会发布的GNU通用公共许可证（版本2）条款
    进行重新分发和/或修改，>>!并由!<<FreeRTOS例外条款修改。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合作品，而不必提供
    >>! FreeRTOS内核之外的专有组件的源代码。

    FreeRTOS的发布希望能够有所帮助，但不提供任何保证；甚至不提供对适销性或特定
    用途适用性的暗示保证。完整的许可证文本可从以下链接获得：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？首先阅读FAQ"我的应用程序无法运行，可能出了什么问题？"    *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证以及
    Real Time Engineers Ltd.的联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品的选择，包括FreeRTOS+Trace
    （一个不可或缺的生产力工具）、与DOS兼容的FAT文件系统和我们的微型线程感知UDP/IP栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd授权FreeRTOS给High
    Integrity Systems，以OpenRTOS品牌销售。低成本OpenRTOS许可证提供有偿支持、
    赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供了一个经安全工程处理
    并独立SIL3认证的版本，用于安全和任务关键型应用，这些应用需要可证明的可靠性。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义。
 *
 * 这些定义应根据您特定的硬件和应用需求进行调整。
 *
 * 这些参数在FreeRTOS.org网站上提供的FreeRTOS API文档的"配置"部分
 * 和FreeRTOS参考手册中有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1   /* 1: 使用抢占式调度器, 0: 使用协作式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1   /* 1: 使用特定于端口的优化任务选择方法, 0: 使用通用方法 */
#define configMAX_PRIORITIES					5   /* 定义最大可用优先级数量为5 */
#define configUSE_IDLE_HOOK						0   /* 0: 不使用空闲钩子函数 */
#define configUSE_TICK_HOOK						1   /* 1: 使用系统时钟中断钩子函数 */
#define configTICK_RATE_HZ						( 1000 ) /* 系统时钟节拍频率为1000Hz（在这个模拟环境中，并非真实时间） */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小任务堆栈大小（在这种模拟情况下，堆栈只需要容纳一个小结构体，因为真实堆栈是win32线程的一部分） */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 设置总堆大小为20KB */
#define configMAX_TASK_NAME_LEN					( 12 ) /* 任务名称的最大长度 */
#define configUSE_TRACE_FACILITY				0   /* 0: 不使用跟踪功能 */
#define configUSE_16_BIT_TICKS					0   /* 0: 使用32位系统时钟计数器, 1: 使用16位 */
#define configIDLE_SHOULD_YIELD					1   /* 1: 空闲任务在同优先级的任务就绪时应该让出处理器 */
#define configUSE_MUTEXES						1   /* 1: 启用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0   /* 0: 不检查堆栈溢出（当使用Win32模拟器时不适用） */
#define configUSE_RECURSIVE_MUTEXES				1   /* 1: 启用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10  /* 队列注册表大小，用于调试目的 */
#define configUSE_MALLOC_FAILED_HOOK			1   /* 1: 使用内存分配失败钩子函数 */
#define configUSE_APPLICATION_TASK_TAG			0   /* 0: 不使用应用任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1   /* 1: 启用计数信号量 */
#define configUSE_ALTERNATIVE_API				0   /* 0: 不使用替代API（已弃用） */
#define configUSE_QUEUE_SETS					1   /* 1: 启用队列集 */

/* 软件定时器相关配置选项。 */
#define configUSE_TIMERS						0   /* 0: 不使用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务的优先级 */
#define configTIMER_QUEUE_LENGTH				20  /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器服务任务堆栈深度 */

/* 运行时统计信息收集配置选项。 */
#define configGENERATE_RUN_TIME_STATS			0   /* 0: 不生成运行时统计信息 */

/* 协程相关配置选项。 */
#define configUSE_CO_ROUTINES 					0   /* 0: 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2   /* 协程可用的最大优先级数量 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将由uxTaskGetSystemState()函数
提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0   /* 0: 不使用统计格式化函数 */

/* 将以下定义设置为1以包含API函数，或设置为0以排除API函数。
在大多数情况下，链接器会自动移除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1   /* 包含vTaskPrioritySet()函数 */
#define INCLUDE_uxTaskPriorityGet				1   /* 包含uxTaskPriorityGet()函数 */
#define INCLUDE_vTaskDelete						1   /* 包含vTaskDelete()函数 */
#define INCLUDE_vTaskSuspend					1   /* 包含vTaskSuspend()函数 */
#define INCLUDE_vTaskDelayUntil					1   /* 包含vTaskDelayUntil()函数 */
#define INCLUDE_vTaskDelay						1   /* 包含vTaskDelay()函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1   /* 包含uxTaskGetStackHighWaterMark()函数 */
#define INCLUDE_xTaskGetSchedulerState			1   /* 包含xTaskGetSchedulerState()函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1   /* 包含xTimerGetTimerDaemonTaskHandle()函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1   /* 包含xTaskGetIdleTaskHandle()函数 */
#define INCLUDE_pcTaskGetTaskName				1   /* 包含pcTaskGetTaskName()函数 */
#define INCLUDE_eTaskGetState					1   /* 包含eTaskGetState()函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1   /* 包含xSemaphoreGetMutexHolder()函数 */
#define INCLUDE_xTimerPendFunctionCall			1   /* 包含xTimerPendFunctionCall()函数 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()使用与标准C assert()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
