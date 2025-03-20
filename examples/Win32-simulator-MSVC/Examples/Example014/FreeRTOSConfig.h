/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且经过专业开发的、健壮的、严格质量控制的、    *
     *    支持良好的跨平台软件，已成为事实上的标准。                        *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者来帮助自己快速入门        *
     *    并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation         *
     *                                                                       *
     *    谢谢您！                                                           *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（版本2）的条款
    重新分发和/或修改它，该许可证由自由软件基金会发布
    >>!并由FreeRTOS例外修改!<<。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合作品，
    >>! 而不必提供FreeRTOS内核外部专有组件的源代码。

    FreeRTOS的分发希望它是有用的，但不提供任何保证；
    甚至没有对适销性或特定用途适用性的暗示保证。
    完整的许可证文本可从以下链接获得：http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？请先阅读FAQ"我的应用程序无法运行，可能出了什么问题？"  *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、
    许可证和Real Time Engineers Ltd.联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品选择，
    包括FreeRTOS+Trace（不可或缺的生产力工具）、与DOS兼容的FAT文件系统
    和我们的小型线程感知UDP/IP堆栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd将FreeRTOS许可给
    High Integrity Systems，以便在OpenRTOS品牌下销售。低成本OpenRTOS许可证
    提供有票据支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供安全工程处理
    并独立SIL3认证的版本，用于安全和任务关键型应用程序，
    这些应用需要可证明的可靠性。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义。
 *
 * 这些定义应根据您特定的硬件和应用程序要求进行调整。
 *
 * 这些参数在FreeRTOS API文档的"配置"部分中描述，
 * 该文档可在FreeRTOS.org网站和FreeRTOS参考手册中获得。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1     /* 启用抢占式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1     /* 启用优化的任务选择方法（特定于硬件架构的优化） */
#define configMAX_PRIORITIES					5     /* 最大任务优先级数，不包括空闲任务优先级（通常为0） */
#define configUSE_IDLE_HOOK						0     /* 不使用空闲任务钩子函数 */
#define configUSE_TICK_HOOK						0     /* 不使用时钟中断钩子函数 */
#define configTICK_RATE_HZ						( 1000 ) /* 时钟中断频率为1000Hz（1ms每个节拍），这是模拟环境而非实时环境 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 在此模拟情况下，堆栈只需容纳一个小结构，因为实际堆栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 总堆大小为20KB */
#define configMAX_TASK_NAME_LEN					( 12 ) /* 任务名称的最大长度 */
#define configUSE_TRACE_FACILITY				0    /* 不使用跟踪工具 */
#define configUSE_16_BIT_TICKS					0    /* 使用32位时钟节拍计数而非16位 */
#define configIDLE_SHOULD_YIELD					1    /* 空闲任务应该在有同等优先级的任务准备好时让出CPU */
#define configUSE_MUTEXES						1    /* 启用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0    /* 不检查堆栈溢出，在使用Win32模拟器时不适用 */
#define configUSE_RECURSIVE_MUTEXES				1    /* 启用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10   /* 队列注册表大小（用于调试） */
#define configUSE_MALLOC_FAILED_HOOK			1    /* 启用内存分配失败钩子函数 */
#define configUSE_APPLICATION_TASK_TAG			0    /* 不使用应用程序任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1    /* 启用计数信号量 */
#define configUSE_ALTERNATIVE_API				0    /* 不使用替代API */
#define configUSE_QUEUE_SETS					1    /* 启用队列集 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						1    /* 启用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务的优先级，设为最高优先级 */
#define configTIMER_QUEUE_LENGTH				2    /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务堆栈深度 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0    /* 不生成运行时统计信息 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0    /* 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2    /* 如果使用协程，协程的最大优先级数 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将
   uxTaskGetSystemState()函数提供的原始数据格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0    /* 不使用统计格式化函数 */

/* 将以下定义设为1以包含API函数，或设为0以排除API函数。
   在大多数情况下，链接器将自动移除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1    /* 包含vTaskPrioritySet函数 */
#define INCLUDE_uxTaskPriorityGet				1    /* 包含uxTaskPriorityGet函数 */
#define INCLUDE_vTaskDelete						1    /* 包含vTaskDelete函数 */
#define INCLUDE_vTaskSuspend					1    /* 包含vTaskSuspend函数 */
#define INCLUDE_vTaskDelayUntil					1    /* 包含vTaskDelayUntil函数 */
#define INCLUDE_vTaskDelay						1    /* 包含vTaskDelay函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1    /* 包含uxTaskGetStackHighWaterMark函数（用于监控堆栈使用） */
#define INCLUDE_xTaskGetSchedulerState			1    /* 包含xTaskGetSchedulerState函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1    /* 包含xTimerGetTimerDaemonTaskHandle函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1    /* 包含xTaskGetIdleTaskHandle函数 */
#define INCLUDE_pcTaskGetTaskName				1    /* 包含pcTaskGetTaskName函数 */
#define INCLUDE_eTaskGetState					1    /* 包含eTaskGetState函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1    /* 包含xSemaphoreGetMutexHolder函数 */
#define INCLUDE_xTimerPendFunctionCall			1    /* 包含xTimerPendFunctionCall函数 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()使用与标准C的assert()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ ) /* 断言宏，在条件不满足时调用vAssertCalled函数 */

#endif /* FREERTOS_CONFIG_H */
