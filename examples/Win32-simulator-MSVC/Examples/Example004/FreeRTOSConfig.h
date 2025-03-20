/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制的、       *
     *    支持良好的跨平台软件，已成为事实上的标准。                       *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者，帮助自己快速入门       *
     *    并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    谢谢！                                                            *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（版本2）的条款重新分发和/或
    修改它，该许可证由自由软件基金会发布 >>!并由FreeRTOS例外修改!<<。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合作品，而不必提供
    >>! FreeRTOS内核之外的专有组件的源代码。

    FreeRTOS的分发希望它会有用，但不提供任何保证；甚至没有对适销性或特定用途
    适用性的暗示保证。完整的许可文本可从以下链接获得：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？首先阅读常见问题解答"我的应用程序无法运行，可能是       *
     *    什么问题？"                                                       *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和
    Real Time Engineers Ltd.联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品选择，包括FreeRTOS+Trace
    —— 不可或缺的生产力工具、兼容DOS的FAT文件系统以及我们的微型线程感知UDP/IP栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd授权FreeRTOS给
    High Integrity Systems以OpenRTOS品牌销售。低成本OpenRTOS许可证提供
    票务支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供经过安全工程和
    独立SIL3认证的版本，用于需要可证明可靠性的安全和任务关键型应用。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定的定义。
 *
 * 这些定义应根据您特定的硬件和应用程序要求进行调整。
 *
 * 这些参数在FreeRTOS API文档的"配置"部分中有详细描述，
 * 可在FreeRTOS.org网站和FreeRTOS参考手册中找到。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1               /* 设置为1启用抢占式调度 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1               /* 使用优化的任务选择方法 */
#define configMAX_PRIORITIES					5               /* 定义最大优先级数量（0-4） */
#define configUSE_IDLE_HOOK						0               /* 是否使用空闲钩子函数 */
#define configUSE_TICK_HOOK						0               /* 是否使用时钟钩子函数 */
#define configTICK_RATE_HZ						( 1000 )        /* 系统时钟频率（这是模拟环境，非实时） */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小堆栈大小，在模拟环境中较小，因为实际堆栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 总堆大小，字节为单位 */
#define configMAX_TASK_NAME_LEN					( 12 )          /* 任务名称最大长度 */
#define configUSE_TRACE_FACILITY				0               /* 是否启用跟踪功能 */
#define configUSE_16_BIT_TICKS					0               /* 使用32位计数器（0）还是16位计数器（1） */
#define configIDLE_SHOULD_YIELD					1               /* 空闲任务是否应该让出CPU */
#define configUSE_MUTEXES						1               /* 是否使用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0               /* 使用Win32模拟器时不适用堆栈溢出检查 */
#define configUSE_RECURSIVE_MUTEXES				1               /* 是否使用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10              /* 队列注册表大小 */
#define configUSE_MALLOC_FAILED_HOOK			1               /* 是否使用内存分配失败钩子 */
#define configUSE_APPLICATION_TASK_TAG			0               /* 是否使用应用任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1               /* 是否使用计数信号量 */
#define configUSE_ALTERNATIVE_API				0               /* 是否使用替代API */
#define configUSE_QUEUE_SETS					1               /* 是否使用队列集 */

/* 软件计时器相关配置选项 */
#define configUSE_TIMERS						0               /* 不使用软件计时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 计时器服务任务优先级 */
#define configTIMER_QUEUE_LENGTH				20              /* 计时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 计时器任务堆栈深度 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0               /* 不生成运行时统计信息 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0               /* 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2               /* 协程最大优先级 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将uxTaskGetSystemState()
   函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0

/* 将以下定义设置为1以包含API函数，或设置为0以排除API函数。
   在大多数情况下，链接器会自动删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1               /* 包含任务优先级设置函数 */
#define INCLUDE_uxTaskPriorityGet				1               /* 包含获取任务优先级函数 */
#define INCLUDE_vTaskDelete						1               /* 包含删除任务函数 */
#define INCLUDE_vTaskSuspend					1               /* 包含任务挂起函数 */
#define INCLUDE_vTaskDelayUntil					1               /* 包含任务延时至函数 */
#define INCLUDE_vTaskDelay						1               /* 包含任务延时函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1               /* 包含获取任务堆栈高水位函数 */
#define INCLUDE_xTaskGetSchedulerState			1               /* 包含获取调度器状态函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1               /* 包含获取计时器守护任务句柄函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1               /* 包含获取空闲任务句柄函数 */
#define INCLUDE_pcTaskGetTaskName				1               /* 包含获取任务名称函数 */
#define INCLUDE_eTaskGetState					1               /* 包含获取任务状态函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1               /* 包含获取互斥量持有者函数 */
#define INCLUDE_xTimerPendFunctionCall			1               /* 包含挂起函数调用函数 */

/* 在开发期间定义configASSERT()是个好主意。configASSERT()
   使用与标准C断言()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
