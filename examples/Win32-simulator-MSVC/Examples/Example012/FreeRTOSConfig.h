/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制、          *
     *    支持多平台的软件，已成为事实上的标准。                            *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者都购买来帮助自己          *
     *    快速入门并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation *
     *                                                                       *
     *    谢谢您的支持！                                                    *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS分发版的一部分。

    FreeRTOS是自由软件；您可以根据自由软件基金会发布的GNU通用公共许可证（版本2）
    重新分发和/或修改它，>>!并经过FreeRTOS例外条款修改!<<。

    >>! 注意：对GPL的修改允许您分发包含FreeRTOS的合并作品，而无需提供FreeRTOS内核
    >>! 之外的专有组件的源代码。

    FreeRTOS的分发希望能对您有所帮助，但不提供任何保证；甚至没有对适销性或特定
    用途适用性的默示保证。完整的许可证文本可从以下链接获取：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？首先阅读FAQ"我的应用程序无法运行，可能是什么问题？"      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和Real Time 
    Engineers Ltd.联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品选择，包括FreeRTOS+Trace
    （不可或缺的生产力工具）、DOS兼容FAT文件系统和我们的轻量级线程感知UDP/IP协议栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd授权FreeRTOS给High Integrity 
    Systems，以OpenRTOS品牌出售。低成本OpenRTOS许可证提供技术支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供经过安全工程和独立SIL3
    认证的版本，用于需要可证明可靠性的安全和任务关键型应用。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义
 *
 * 这些定义应根据您特定的硬件和应用需求进行调整。
 *
 * 这些参数在FreeRTOS.org网站上提供的FreeRTOS API文档的'配置'部分
 * 和FreeRTOS参考手册中有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1                       /* 1: 使用抢占式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                       /* 1: 使用特定于端口的优化任务选择 */
#define configMAX_PRIORITIES					5                       /* 定义可用的最大任务优先级（0-4） */
#define configUSE_IDLE_HOOK						0                       /* 0: 不使用空闲钩子函数 */
#define configUSE_TICK_HOOK						0                       /* 0: 不使用时钟中断钩子函数 */
#define configTICK_RATE_HZ						( 1000 )                /* 系统时钟节拍频率为1000Hz（这是模拟环境，非实时） */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小堆栈大小（在模拟环境中，实际堆栈是win32线程的一部分） */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 堆内存总大小为20KB */
#define configMAX_TASK_NAME_LEN					( 12 )                  /* 任务名称的最大长度 */
#define configUSE_TRACE_FACILITY				0                       /* 0: 不启用跟踪功能 */
#define configUSE_16_BIT_TICKS					0                       /* 0: 使用32位时钟节拍计数 */
#define configIDLE_SHOULD_YIELD					1                       /* 1: 空闲任务应该向其他同优先级任务让步 */
#define configUSE_MUTEXES						1                       /* 1: 启用互斥锁 */
#define configCHECK_FOR_STACK_OVERFLOW			0                       /* 使用Win32模拟器时不适用堆栈溢出检查 */
#define configUSE_RECURSIVE_MUTEXES				1                       /* 1: 启用递归互斥锁 */
#define configQUEUE_REGISTRY_SIZE				10                      /* 队列注册表大小，允许调试器查询10个队列/信号量 */
#define configUSE_MALLOC_FAILED_HOOK			1                       /* 1: 启用内存分配失败钩子函数 */
#define configUSE_APPLICATION_TASK_TAG			0                       /* 0: 不使用应用程序任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1                       /* 1: 启用计数型信号量 */
#define configUSE_ALTERNATIVE_API				0                       /* 0: 不使用已废弃的替代API */
#define configUSE_QUEUE_SETS					1                       /* 1: 启用队列集功能 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						0                       /* 0: 不使用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务的优先级 */
#define configTIMER_QUEUE_LENGTH				20                      /* 定时器命令队列的长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务堆栈深度 */

/* 运行时间统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0                       /* 0: 不生成运行时统计数据 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0                       /* 0: 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2                       /* 可用的协程优先级数量 */

/* 此演示不使用示例统计格式化函数，这些函数将uxTaskGetSystemState()函数
   提供的原始数据格式化为人类可读的ASCII形式 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0                       /* 0: 不使用统计格式化函数 */

/* 将以下定义设置为1表示包含API函数，设置为0表示排除API函数。
   在大多数情况下，链接器会自动移除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1                       /* 包含改变任务优先级的函数 */
#define INCLUDE_uxTaskPriorityGet				1                       /* 包含获取任务优先级的函数 */
#define INCLUDE_vTaskDelete						1                       /* 包含删除任务的函数 */
#define INCLUDE_vTaskSuspend					1                       /* 包含挂起/恢复任务的函数 */
#define INCLUDE_vTaskDelayUntil					1                       /* 包含绝对延时函数 */
#define INCLUDE_vTaskDelay						1                       /* 包含相对延时函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1                       /* 包含获取任务堆栈使用高水位的函数 */
#define INCLUDE_xTaskGetSchedulerState			1                       /* 包含获取调度器状态的函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1                       /* 包含获取定时器守护任务句柄的函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1                       /* 包含获取空闲任务句柄的函数 */
#define INCLUDE_pcTaskGetTaskName				1                       /* 包含获取任务名称的函数 */
#define INCLUDE_eTaskGetState					1                       /* 包含获取任务状态的函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1                       /* 包含获取互斥锁持有者的函数 */
#define INCLUDE_xTimerPendFunctionCall			1                       /* 包含在定时器服务任务上异步执行函数的功能 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()
   使用与标准C assert()宏相同的语义。 */
#include <stdint.h>  /* 为了使用uint32_t类型 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
