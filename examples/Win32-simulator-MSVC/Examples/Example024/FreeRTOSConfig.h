/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS 提供完全免费但专业开发的、健壮的、严格质量控制的、       *
     *    支持良好的跨平台软件，已成为事实上的标准。                        *
     *                                                                       *
     *    通过购买 FreeRTOS 教程书籍、参考手册或两者兼而有之，             *
     *    来帮助自己快速入门并支持 FreeRTOS 项目：                         *
     *    http://www.FreeRTOS.org/Documentation                             *
     *                                                                       *
     *    感谢您的支持！                                                    *
     *                                                                       *
    ***************************************************************************

    本文件是 FreeRTOS 发行版的一部分。

    FreeRTOS 是自由软件；您可以根据自由软件基金会发布的 GNU 通用公共许可证
    (版本 2) 条款 >>!并经 FreeRTOS 例外条款修改!<< 进行重新分发或修改。

    >>! 注意：对 GPL 的修改是为了允许您分发包含 FreeRTOS 的组合作品，而不必
    >>! 提供 FreeRTOS 内核之外的专有组件的源代码。

    FreeRTOS 分发的目的是希望它有用，但不提供任何保证；甚至没有对适销性或
    特定用途适用性的默示保证。完整的许可证文本可从以下链接获得：
    http://www.freertos.org/a00114.html

    1 个制表符 == 4 个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？首先阅读常见问题解答"我的应用程序无法运行，           *
     *    可能出了什么问题？"                                              *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、
    许可证和 Real Time Engineers Ltd. 联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS 生态系统产品的选择，
    包括 FreeRTOS+Trace - 不可或缺的生产力工具、与 DOS 兼容的 FAT 文件系统，
    以及我们小巧的线程感知 UDP/IP 协议栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd 将 FreeRTOS 许可给 High
    Integrity Systems，以 OpenRTOS 品牌销售。低成本 OpenRTOS 许可提供有票据
    支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems 还提供经过安全工程和
    独立 SIL3 认证的版本，用于需要可证明可靠性的安全和关键任务应用。

    1 个制表符 == 4 个空格！
*/

/* 添加标准整数类型的头文件以解决uint32_t未定义的问题 */
#include <stdint.h>

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义。
 *
 * 这些定义应根据您特定的硬件和应用程序需求进行调整。
 *
 * 这些参数在 FreeRTOS.org 网站上提供的 FreeRTOS API 文档的
 * "配置"部分和 FreeRTOS 参考手册中有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1          /* 启用抢占式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1          /* 使用优化的任务选择方法 */
#define configMAX_PRIORITIES					5          /* 最大任务优先级数（0-4） */
#define configUSE_IDLE_HOOK						0          /* 不使用空闲钩子函数 */
#define configUSE_TICK_HOOK						0          /* 不使用时钟钩子函数 */
#define configTICK_RATE_HZ						( 100 )    /* 系统时钟频率（这是模拟环境，不是实时的） */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小栈大小（在此模拟情况下，栈只需要容纳一个小结构，因为实际栈是win32线程的一部分） */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 总堆内存大小（20KB） */
#define configMAX_TASK_NAME_LEN					( 12 )      /* 任务名称最大长度 */
#define configUSE_TRACE_FACILITY				0          /* 不使用跟踪功能 */
#define configUSE_16_BIT_TICKS					0          /* 使用32位时钟计数 */
#define configIDLE_SHOULD_YIELD					1          /* 空闲任务应该让出CPU */
#define configUSE_MUTEXES						1          /* 启用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0          /* 当使用Win32模拟器时不适用栈溢出检查 */
#define configUSE_RECURSIVE_MUTEXES				1          /* 启用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10         /* 队列注册表大小 */
#define configUSE_MALLOC_FAILED_HOOK			1          /* 使用内存分配失败钩子 */
#define configUSE_APPLICATION_TASK_TAG			0          /* 不使用应用任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1          /* 启用计数信号量 */
#define configUSE_ALTERNATIVE_API				0          /* 不使用替代API */
#define configUSE_QUEUE_SETS					1          /* 启用队列集 */
#define configUSE_TASK_NOTIFICATIONS			1          /* 启用任务通知功能 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						0          /* 不使用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器任务优先级 */
#define configTIMER_QUEUE_LENGTH				20         /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务栈深度 */

/* 运行时统计信息收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0          /* 不生成运行时统计信息 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0          /* 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2          /* 协程最大优先级数 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将由 uxTaskGetSystemState() 
 * 函数提供的原始数据格式化为人类可读的 ASCII 形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0

/* 将以下定义设置为 1 以包含 API 函数，或设置为零以排除 API 函数。
 * 在大多数情况下，链接器将删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1          /* 包含任务优先级设置函数 */
#define INCLUDE_uxTaskPriorityGet				1          /* 包含获取任务优先级函数 */
#define INCLUDE_vTaskDelete						1          /* 包含任务删除函数 */
#define INCLUDE_vTaskSuspend					1          /* 包含任务挂起函数 */
#define INCLUDE_vTaskDelayUntil					1          /* 包含任务延时至函数 */
#define INCLUDE_vTaskDelay						1          /* 包含任务延时函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1          /* 包含获取任务栈高水位标记函数 */
#define INCLUDE_xTaskGetSchedulerState			1          /* 包含获取调度器状态函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1          /* 包含获取定时器守护任务句柄函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1          /* 包含获取空闲任务句柄函数 */
#define INCLUDE_pcTaskGetTaskName				1          /* 包含获取任务名称函数 */
#define INCLUDE_eTaskGetState					1          /* 包含获取任务状态函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1          /* 包含获取互斥量持有者函数 */
#define INCLUDE_xTimerPendFunctionCall			1          /* 包含定时器挂起函数调用 */

/* 在开发期间定义 configASSERT() 是个好主意。configASSERT() 使用与标准 C 
 * assert() 宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
