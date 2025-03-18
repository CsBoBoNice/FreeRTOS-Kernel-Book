/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制的、          *
     *    支持跨平台的软件，已成为事实上的标准。                              *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者都购买来帮助自己            *
     *    快速入门并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation  *
     *                                                                       *
     *    感谢您的支持！                                                      *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（第2版）的条款
    重新分发和/或修改它，该许可证由自由软件基金会发布，并经FreeRTOS例外条款修改。

    >>! 注意：对GPL的修改旨在允许您分发包含FreeRTOS的组合作品，
    >>! 而无需提供FreeRTOS内核之外的专有组件的源代码。

    FreeRTOS的分发希望能够有所帮助，但不提供任何保证；甚至不提供
    适销性或特定用途适用性的隐含保证。完整的许可证文本可从以下
    链接获取：http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？从阅读FAQ开始："我的应用程序无法运行，可能是什么问题？"    *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、
    许可证和Real Time Engineers Ltd.的联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品的选择，
    包括FreeRTOS+Trace（一个不可或缺的生产力工具）、DOS兼容的FAT文件系统
    以及我们的小型线程感知UDP/IP协议栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd许可FreeRTOS给High
    Integrity Systems以OpenRTOS品牌销售。低成本OpenRTOS许可证提供有票据支持、
    赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供经过安全工程
    和独立SIL3认证的版本，用于需要可证明可靠性的安全和关键任务应用。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义
 *
 * 这些定义应根据您的特定硬件和应用需求进行调整。
 *
 * 这些参数在FreeRTOS.org网站上的FreeRTOS API文档的"配置"部分
 * 和FreeRTOS参考手册中有详细描述。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1                /* 1: 使用抢占式调度器；0: 使用协作式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1                /* 1: 使用优化的任务选择方法；0: 使用通用方法 */
#define configMAX_PRIORITIES					5                /* 定义应用程序任务的最高优先级 */
#define configUSE_IDLE_HOOK						0                /* 1: 使用空闲钩子；0: 不使用空闲钩子 */
#define configUSE_TICK_HOOK						0                /* 1: 使用时钟钩子；0: 不使用时钟钩子 */
#define configTICK_RATE_HZ						( 1000 )         /* 系统时钟频率，即每秒中断次数。这是一个模拟环境，因此不是实时的 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小堆栈大小。在此模拟情况下，堆栈只需要容纳一个小结构，因为实际堆栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 堆内存总大小（字节） */
#define configMAX_TASK_NAME_LEN					( 12 )           /* 任务名称的最大长度 */
#define configUSE_TRACE_FACILITY				0                /* 1: 包含额外的结构成员和函数以协助可视化和跟踪；0: 不包含 */
#define configUSE_16_BIT_TICKS					0                /* 1: 使用16位无符号整型作为时钟计数类型；0: 使用32位无符号整型 */
#define configIDLE_SHOULD_YIELD					1                /* 1: 空闲任务遇到就绪的同优先级任务时应让出处理器；0: 不让出 */
#define configUSE_MUTEXES						1                /* 1: 包含互斥量相关API；0: 不包含 */
#define configCHECK_FOR_STACK_OVERFLOW			0                /* 0: 不检查堆栈溢出；使用Win32模拟器时不适用 */
#define configUSE_RECURSIVE_MUTEXES				1                /* 1: 包含递归互斥量相关API；0: 不包含 */
#define configQUEUE_REGISTRY_SIZE				10               /* 定义可以注册的队列和信号量的最大数量 */
#define configUSE_MALLOC_FAILED_HOOK			1                /* 1: 使用内存分配失败钩子；0: 不使用 */
#define configUSE_APPLICATION_TASK_TAG			0                /* 1: 包含应用程序任务标签功能；0: 不包含 */
#define configUSE_COUNTING_SEMAPHORES			1                /* 1: 包含计数信号量相关API；0: 不包含 */
#define configUSE_ALTERNATIVE_API				0                /* 1: 使用队列和信号量的备选API；0: 使用标准API（已弃用） */
#define configUSE_QUEUE_SETS					1                /* 1: 启用队列集功能；0: 禁用 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						1                /* 1: 启用软件定时器；0: 禁用 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务的优先级 */
#define configTIMER_QUEUE_LENGTH				20               /* 定时器命令队列的长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器服务任务的堆栈大小 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0                /* 1: 生成运行时统计数据；0: 不生成 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0                /* 1: 包含协程支持；0: 不包含 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2                /* 定义协程的最大优先级数 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将uxTaskGetSystemState()
函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0                /* 1: 使用统计格式化函数；0: 不使用 */

/* 将以下定义设置为1以包含API函数，或设置为0以排除API函数。
在大多数情况下，链接器会自动删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1                /* 1: 包含vTaskPrioritySet()函数；0: 不包含 */
#define INCLUDE_uxTaskPriorityGet				1                /* 1: 包含uxTaskPriorityGet()函数；0: 不包含 */
#define INCLUDE_vTaskDelete						1                /* 1: 包含vTaskDelete()函数；0: 不包含 */
#define INCLUDE_vTaskSuspend					1                /* 1: 包含vTaskSuspend()函数和阻塞延迟；0: 不包含 */
#define INCLUDE_vTaskDelayUntil					1                /* 1: 包含vTaskDelayUntil()函数；0: 不包含 */
#define INCLUDE_vTaskDelay						1                /* 1: 包含vTaskDelay()函数；0: 不包含 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1                /* 1: 包含uxTaskGetStackHighWaterMark()函数；0: 不包含 */
#define INCLUDE_xTaskGetSchedulerState			1                /* 1: 包含xTaskGetSchedulerState()函数；0: 不包含 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1                /* 1: 包含xTimerGetTimerDaemonTaskHandle()函数；0: 不包含 */
#define INCLUDE_xTaskGetIdleTaskHandle			1                /* 1: 包含xTaskGetIdleTaskHandle()函数；0: 不包含 */
#define INCLUDE_pcTaskGetTaskName				1                /* 1: 包含pcTaskGetTaskName()函数；0: 不包含 */
#define INCLUDE_eTaskGetState					1                /* 1: 包含eTaskGetState()函数；0: 不包含 */
#define INCLUDE_xSemaphoreGetMutexHolder		1                /* 1: 包含xSemaphoreGetMutexHolder()函数；0: 不包含 */
#define INCLUDE_xTimerPendFunctionCall			1                /* 1: 包含xTimerPendFunctionCall()函数；0: 不包含 */

/* 在开发时定义configASSERT()是一个好主意。configASSERT()
使用与标准C assert()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
