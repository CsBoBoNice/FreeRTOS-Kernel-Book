/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS 提供完全免费且专业开发的、健壮的、严格质量控制的、       *
     *    支持的以及跨平台的软件，已成为事实上的标准。                      *
     *                                                                       *
     *    通过购买 FreeRTOS 教程书籍、参考手册或两者来帮助自己快速入门     *
     *    并支持 FreeRTOS 项目：http://www.FreeRTOS.org/Documentation       *
     *                                                                       *
     *    感谢您！                                                          *
     *                                                                       *
    ***************************************************************************

    本文件是 FreeRTOS 发行版的一部分。

    FreeRTOS 是自由软件；您可以根据自由软件基金会发布的 GNU 通用公共许可证
    (版本 2) 重新分发和/或修改它 >>!并由!<< FreeRTOS 例外修改。

    >>! 注意：对 GPL 的修改是为了允许您分发包含 FreeRTOS 的组合作品，
    >>! 而不必提供 FreeRTOS 内核之外的专有组件的源代码。

    FreeRTOS 的分发希望它会有用，但不提供任何保证；甚至没有对适销性或特定
    用途适用性的暗示保证。完整的许可证文本可从以下链接获得：
    http://www.freertos.org/a00114.html

    1 个制表符 == 4 个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？从阅读常见问题解答开始："我的应用程序不运行，可能是     *
     *    什么问题？"                                                       *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和
    Real Time Engineers Ltd. 联系方式。

    http://www.FreeRTOS.org/plus - 一系列 FreeRTOS 生态系统产品，
    包括 FreeRTOS+Trace - 一个不可或缺的生产力工具，一个与 DOS 兼容的
    FAT 文件系统，以及我们的小型线程感知 UDP/IP 堆栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd 将 FreeRTOS 授权给
    High Integrity Systems，以便在 OpenRTOS 品牌下销售。低成本 OpenRTOS
    许可证提供有票务支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems 还提供了一个安全
    工程的独立 SIL3 认证版本，用于需要可证明可靠性的安全和任务关键型应用。

    1 个制表符 == 4 个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定的定义。
 *
 * 这些定义应该针对您特定的硬件和应用需求进行调整。
 *
 * 这些参数在 FreeRTOS.org 网站上的 FreeRTOS API 文档的"配置"部分
 * 和 FreeRTOS 参考手册中有描述。
 *----------------------------------------------------------*/

/* 配置是否使用抢占式调度器 - 设置为1表示使用 */
#define configUSE_PREEMPTION					1
/* 配置是否使用优化的任务选择方法 - 设置为1表示使用 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1
/* 定义最大可用任务优先级数量 */
#define configMAX_PRIORITIES					5
/* 配置是否使用空闲钩子函数 - 设置为0表示不使用 */
#define configUSE_IDLE_HOOK						0
/* 配置是否使用时钟节拍钩子函数 - 设置为0表示不使用 */
#define configUSE_TICK_HOOK						0
/* 设置系统时钟节拍频率(Hz) - 这是模拟环境，不是实时的 */
#define configTICK_RATE_HZ						( 100 )
/* 设置最小堆栈大小 - 在模拟环境中，栈只需要容纳一个小结构，因为真正的栈是Win32线程的一部分 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 )
/* 设置堆的总大小(字节) */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) )
/* 设置任务名称的最大长度 */
#define configMAX_TASK_NAME_LEN					( 12 )
/* 配置是否启用跟踪功能 - 设置为0表示不启用 */
#define configUSE_TRACE_FACILITY				0
/* 配置是否使用16位时钟节拍计数 - 设置为0表示使用32位 */
#define configUSE_16_BIT_TICKS					0
/* 配置空闲任务是否应该在有就绪任务时让出处理器 */
#define configIDLE_SHOULD_YIELD					1
/* 配置是否使用互斥量 */
#define configUSE_MUTEXES						1
/* 配置是否检查栈溢出 - 不适用于Win32模拟器 */
#define configCHECK_FOR_STACK_OVERFLOW			0
/* 配置是否使用递归互斥量 */
#define configUSE_RECURSIVE_MUTEXES				1
/* 设置队列注册表大小 */
#define configQUEUE_REGISTRY_SIZE				10
/* 配置是否使用内存分配失败钩子函数 */
#define configUSE_MALLOC_FAILED_HOOK			1
/* 配置是否使用应用任务标签 */
#define configUSE_APPLICATION_TASK_TAG			0
/* 配置是否使用计数信号量 */
#define configUSE_COUNTING_SEMAPHORES			1
/* 配置是否使用替代API */
#define configUSE_ALTERNATIVE_API				0
/* 配置是否使用队列集 */
#define configUSE_QUEUE_SETS					1

/* 软件定时器相关配置选项 */
/* 配置是否使用软件定时器 */
#define configUSE_TIMERS						0
/* 设置定时器服务任务的优先级 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 )
/* 设置定时器命令队列的长度 */
#define configTIMER_QUEUE_LENGTH				20
/* 设置定时器任务的堆栈深度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 )

/* 运行时统计信息收集配置选项 */
/* 配置是否生成运行时统计信息 */
#define configGENERATE_RUN_TIME_STATS			0

/* 协程相关配置选项 */
/* 配置是否使用协程 */
#define configUSE_CO_ROUTINES 					0
/* 设置协程的最大优先级 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将uxTaskGetSystemState()
   函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0

/* 将以下定义设置为1以包含API函数，或设置为零以排除API函数。
   在大多数情况下，链接器无论如何都会删除未使用的函数。 */
/* 包含vTaskPrioritySet函数 - 用于动态改变任务优先级 */
#define INCLUDE_vTaskPrioritySet				1
/* 包含uxTaskPriorityGet函数 - 用于获取任务优先级 */
#define INCLUDE_uxTaskPriorityGet				1
/* 包含vTaskDelete函数 - 用于删除任务 */
#define INCLUDE_vTaskDelete						1
/* 包含vTaskSuspend函数 - 用于挂起任务 */
#define INCLUDE_vTaskSuspend					1
/* 包含vTaskDelayUntil函数 - 用于精确延时任务 */
#define INCLUDE_vTaskDelayUntil					1
/* 包含vTaskDelay函数 - 用于延时任务 */
#define INCLUDE_vTaskDelay						1
/* 包含uxTaskGetStackHighWaterMark函数 - 用于获取任务栈使用的高水位标记 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1
/* 包含xTaskGetSchedulerState函数 - 用于获取调度器状态 */
#define INCLUDE_xTaskGetSchedulerState			1
/* 包含xTimerGetTimerDaemonTaskHandle函数 - 用于获取定时器守护任务句柄 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1
/* 包含xTaskGetIdleTaskHandle函数 - 用于获取空闲任务句柄 */
#define INCLUDE_xTaskGetIdleTaskHandle			1
/* 包含pcTaskGetTaskName函数 - 用于获取任务名称 */
#define INCLUDE_pcTaskGetTaskName				1
/* 包含eTaskGetState函数 - 用于获取任务状态 */
#define INCLUDE_eTaskGetState					1
/* 包含xSemaphoreGetMutexHolder函数 - 用于获取互斥量持有者 */
#define INCLUDE_xSemaphoreGetMutexHolder		1
/* 包含xTimerPendFunctionCall函数 - 用于挂起函数调用 */
#define INCLUDE_xTimerPendFunctionCall			1

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()
   使用与标准C的assert()宏相同的语义。这有助于捕获配置错误和运行时问题。 */
/* 声明断言失败时调用的函数 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
/* 定义断言宏，当条件为假时调用vAssertCalled函数 */
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
