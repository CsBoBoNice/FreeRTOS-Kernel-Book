/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制的、       *
     *    支持良好的跨平台软件，已成为事实上的标准。                        *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者来帮助自己快速入门       *
     *    并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    谢谢您！                                                          *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（版本2）的条款
    重新分发和/或修改它，该许可证由自由软件基金会发布>>!并被FreeRTOS例外修改!<<。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合作品，
    >>! 而无需提供FreeRTOS内核外的专有组件的源代码。

    FreeRTOS的分发希望它会有用，但不提供任何保证；
    甚至没有适销性或特定用途适用性的暗示保证。
    完整的许可证文本可从以下链接获取：http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？请先阅读FAQ"我的应用程序不运行，可能是什么问题？"      *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和Real Time Engineers Ltd.联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品选择，
    包括FreeRTOS+Trace - 不可或缺的生产力工具、与DOS兼容的FAT文件系统以及我们的小型线程感知UDP/IP堆栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd授权FreeRTOS给High
    Integrity Systems，以OpenRTOS品牌销售。低成本OpenRTOS许可证提供票据支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供经过安全工程和独立SIL3认证的版本，
    用于需要可证明可靠性的安全和任务关键型应用。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定的定义
 *
 * 这些定义应根据您特定的硬件和应用需求进行调整。
 *
 * 这些参数在FreeRTOS.org网站上和FreeRTOS参考手册的
 * "配置"部分有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1       /* 启用抢占式调度 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1       /* 使用优化的任务选择方法 */
#define configMAX_PRIORITIES					5       /* 最大任务优先级数（0-4） */
#define configUSE_IDLE_HOOK						0       /* 不使用空闲钩子 */
#define configUSE_TICK_HOOK						0       /* 不使用滴答钩子 */
#define configTICK_RATE_HZ						( 1000 ) /* 这是一个模拟环境，因此不是实时的。滴答频率为1000Hz */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 在这个模拟情况下，栈只需保存一个小结构，因为实际栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 总堆大小为20KB */
#define configMAX_TASK_NAME_LEN					( 12 )    /* 任务名称的最大长度 */
#define configUSE_TRACE_FACILITY				0       /* 不使用跟踪功能 */
#define configUSE_16_BIT_TICKS					0       /* 不使用16位滴答计数 */
#define configIDLE_SHOULD_YIELD					1       /* 空闲任务应该让出CPU */
#define configUSE_MUTEXES						1       /* 启用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0       /* 使用Win32模拟器时不适用于栈溢出检查 */
#define configUSE_RECURSIVE_MUTEXES				1       /* 启用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10      /* 队列注册表大小为10 */
#define configUSE_MALLOC_FAILED_HOOK			1       /* 启用内存分配失败钩子 */
#define configUSE_APPLICATION_TASK_TAG			0       /* 不使用应用任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1       /* 启用计数信号量 */
#define configUSE_ALTERNATIVE_API				0       /* 不使用替代API */
#define configUSE_QUEUE_SETS					1       /* 启用队列集 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						0       /* 不使用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器任务优先级为最高优先级减1 */
#define configTIMER_QUEUE_LENGTH				20      /* 定时器命令队列长度为20 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务栈深度为最小栈大小的2倍 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0       /* 不生成运行时统计 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0       /* 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2       /* 最大协程优先级数（0-1） */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将uxTaskGetSystemState()
   函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0       /* 不使用统计格式化函数 */

/* 将以下定义设置为1以包含API函数，或设置为零以排除API函数。
   在大多数情况下，链接器会删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1       /* 包含vTaskPrioritySet函数 */
#define INCLUDE_uxTaskPriorityGet				1       /* 包含uxTaskPriorityGet函数 */
#define INCLUDE_vTaskDelete						1       /* 包含vTaskDelete函数 */
#define INCLUDE_vTaskSuspend					1       /* 包含vTaskSuspend函数 */
#define INCLUDE_vTaskDelayUntil					1       /* 包含vTaskDelayUntil函数 */
#define INCLUDE_vTaskDelay						1       /* 包含vTaskDelay函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1       /* 包含uxTaskGetStackHighWaterMark函数 */
#define INCLUDE_xTaskGetSchedulerState			1       /* 包含xTaskGetSchedulerState函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1       /* 包含xTimerGetTimerDaemonTaskHandle函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1       /* 包含xTaskGetIdleTaskHandle函数 */
#define INCLUDE_pcTaskGetTaskName				1       /* 包含pcTaskGetTaskName函数 */
#define INCLUDE_eTaskGetState					1       /* 包含eTaskGetState函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1       /* 包含xSemaphoreGetMutexHolder函数 */
#define INCLUDE_xTimerPendFunctionCall			1       /* 包含xTimerPendFunctionCall函数 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()
   使用与标准C assert()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
