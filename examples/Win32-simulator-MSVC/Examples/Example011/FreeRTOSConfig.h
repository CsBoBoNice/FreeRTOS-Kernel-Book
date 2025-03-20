/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 以确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制的、         *
     *    支持良好的跨平台软件，已成为事实上的标准。                         *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者兼具，                     *
     *    帮助自己快速入门并支持FreeRTOS项目：                               *
     *    http://www.FreeRTOS.org/Documentation                              *
     *                                                                       *
     *    感谢您的支持！                                                     *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（版本2）的条款
    重新分发和/或修改它，该许可证由自由软件基金会发布，并经FreeRTOS例外条款修改。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合作品，
    >>! 而不必提供FreeRTOS内核之外的专有组件的源代码。

    FreeRTOS的分发希望能够有所帮助，但不提供任何保证；
    甚至不提供对适销性或特定用途适用性的暗示保证。
    完整的许可证文本可从以下链接获取：http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？首先阅读常见问题解答"我的应用程序无法运行，可能有什么问题？"*
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和
    Real Time Engineers Ltd. 联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品选择，
    包括FreeRTOS+Trace（不可或缺的生产力工具）、与DOS兼容的FAT文件系统
    以及我们的小型线程感知UDP/IP协议栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd授权FreeRTOS给
    High Integrity Systems，以OpenRTOS品牌销售。低成本OpenRTOS许可证
    提供有票证支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供了一个经过安全工程
    和独立SIL3认证的版本，用于需要可证明可靠性的安全和关键任务应用程序。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定的定义
 *
 * 这些定义应根据您特定的硬件和应用程序需求进行调整。
 *
 * 这些参数在FreeRTOS.org网站上提供的FreeRTOS API文档的"配置"部分
 * 和FreeRTOS参考手册中有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1               /* 设置为1启用抢占式调度器，0为协作式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1               /* 使用特定于硬件的方法选择下一个要运行的任务，提高性能 */
#define configMAX_PRIORITIES					5               /* 定义系统中任务可以使用的最大优先级数 */
#define configUSE_IDLE_HOOK						0               /* 设置为1启用空闲钩子功能，可在空闲任务中执行自定义代码 */
#define configUSE_TICK_HOOK						0               /* 设置为1启用时钟钩子功能，可在每个系统时钟中断中执行代码 */
#define configTICK_RATE_HZ						( 1000 )        /* 系统时钟频率，单位Hz。这是模拟环境，不是实时的 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小堆栈大小。在这个模拟情况下，堆栈只需容纳一个小结构，因为实际堆栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 系统堆总大小，单位字节 */
#define configMAX_TASK_NAME_LEN					( 12 )          /* 任务名称的最大长度，包括结束符 */
#define configUSE_TRACE_FACILITY				0               /* 设置为1启用追踪功能，用于调试和性能分析 */
#define configUSE_16_BIT_TICKS					0               /* 设置为1使用16位系统节拍计数器，0使用32位计数器 */
#define configIDLE_SHOULD_YIELD					1               /* 设置为1使空闲任务在有同优先级就绪任务时让出处理器 */
#define configUSE_MUTEXES						1               /* 设置为1启用互斥量功能 */
#define configCHECK_FOR_STACK_OVERFLOW			0               /* 堆栈溢出检测级别，0为禁用。在Win32模拟器中不适用 */
#define configUSE_RECURSIVE_MUTEXES				1               /* 设置为1启用递归互斥量功能 */
#define configQUEUE_REGISTRY_SIZE				10              /* 队列注册表大小，用于调试工具 */
#define configUSE_MALLOC_FAILED_HOOK			1               /* 设置为1启用内存分配失败钩子函数 */
#define configUSE_APPLICATION_TASK_TAG			0               /* 设置为1启用应用任务标签功能 */
#define configUSE_COUNTING_SEMAPHORES			1               /* 设置为1启用计数信号量功能 */
#define configUSE_ALTERNATIVE_API				0               /* 已废弃的配置，保留为向后兼容 */
#define configUSE_QUEUE_SETS					1               /* 设置为1启用队列集功能 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						0               /* 设置为1启用软件定时器功能 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务的优先级 */
#define configTIMER_QUEUE_LENGTH				20              /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器服务任务的堆栈深度 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0               /* 设置为1启用运行时统计收集功能 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0               /* 设置为1启用协程功能 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2               /* 协程可使用的最大优先级数 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将uxTaskGetSystemState()
函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0               /* 设置为1启用统计格式化功能 */

/* 将以下定义设置为1以包含API函数，设置为0以排除API函数。
在大多数情况下，链接器会无论如何删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1               /* 包含vTaskPrioritySet()函数 */
#define INCLUDE_uxTaskPriorityGet				1               /* 包含uxTaskPriorityGet()函数 */
#define INCLUDE_vTaskDelete						1               /* 包含vTaskDelete()函数 */
#define INCLUDE_vTaskSuspend					1               /* 包含vTaskSuspend()函数 */
#define INCLUDE_vTaskDelayUntil					1               /* 包含vTaskDelayUntil()函数 */
#define INCLUDE_vTaskDelay						1               /* 包含vTaskDelay()函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1               /* 包含uxTaskGetStackHighWaterMark()函数，用于监控任务堆栈使用情况 */
#define INCLUDE_xTaskGetSchedulerState			1               /* 包含xTaskGetSchedulerState()函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1               /* 包含xTimerGetTimerDaemonTaskHandle()函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1               /* 包含xTaskGetIdleTaskHandle()函数 */
#define INCLUDE_pcTaskGetTaskName				1               /* 包含pcTaskGetTaskName()函数 */
#define INCLUDE_eTaskGetState					1               /* 包含eTaskGetState()函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1               /* 包含xSemaphoreGetMutexHolder()函数 */
#define INCLUDE_xTimerPendFunctionCall			1               /* 包含xTimerPendFunctionCall()函数 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()
使用与标准C assert()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ ) /* 断言宏，用于调试和验证代码正确性 */

#endif /* FREERTOS_CONFIG_H */
