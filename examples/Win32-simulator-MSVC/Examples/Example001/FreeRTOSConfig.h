/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制的、         *
     *    支持良好的跨平台软件，已成为事实上的标准。                         *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者兼而有之，                 *
     *    帮助自己快速入门并支持FreeRTOS项目：                              *
     *    http://www.FreeRTOS.org/Documentation                             *
     *                                                                       *
     *    感谢您的支持！                                                     *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证(版本2)的条款
    重新分发和/或修改它，该许可证由自由软件基金会发布，
    >>!并经过!<< FreeRTOS例外条款的修改。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的
    >>! 组合作品，而不必提供FreeRTOS内核外专有组件的
    >>! 源代码。

    FreeRTOS的分发希望能够有所帮助，但不提供任何保证；
    甚至不提供对适销性或特定用途适用性的隐含保证。
    完整的许可证文本可从以下链接获取：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？先阅读FAQ"我的应用程序无法运行，可能是什么原因？"        *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、
    许可证和Real Time Engineers Ltd.联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品，
    包括FreeRTOS+Trace（必不可少的生产力工具）、DOS兼容的FAT文件系统
    以及我们的小型线程感知UDP/IP协议栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd将FreeRTOS授权给
    High Integrity Systems，以OpenRTOS品牌销售。低成本的OpenRTOS许可
    提供票务支持、赔偿保证和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供经过安全
    工程处理且独立SIL3认证的版本，用于安全和任务关键型应用，
    这些应用需要可证明的可靠性。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义。
 *
 * 这些定义应根据您的特定硬件和应用程序需求进行调整。
 *
 * 关于这些参数的详细描述，请参见FreeRTOS.org网站上的
 * FreeRTOS API文档的'配置'部分和FreeRTOS参考手册。
 *----------------------------------------------------------*/

/* 基本系统配置 */
#define configUSE_PREEMPTION					1               /* 1: 使用抢占式调度器; 0: 使用合作式调度器 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1               /* 1: 使用硬件优化的任务选择; 0: 使用通用方法 */
#define configMAX_PRIORITIES					5               /* 定义最大可用任务优先级数，范围为0到(configMAX_PRIORITIES-1) */
#define configUSE_IDLE_HOOK						0               /* 1: 使用空闲任务钩子; 0: 不使用 */
#define configUSE_TICK_HOOK						0               /* 1: 使用时钟中断钩子; 0: 不使用 */
#define configTICK_RATE_HZ						( 100 )         /* 系统时钟节拍频率，单位Hz，这是一个模拟环境，因此不是真实的实时性能 */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 最小堆栈大小，在这个模拟环境中，堆栈只需保存一个小结构，因为实际堆栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 堆总大小，单位字节 */
#define configMAX_TASK_NAME_LEN					( 12 )          /* 最大任务名称长度 */
#define configUSE_TRACE_FACILITY				0               /* 1: 启用追踪功能; 0: 禁用 */
#define configUSE_16_BIT_TICKS					0               /* 1: 使用16位计数器作为时钟节拍计数; 0: 使用32位计数器 */
#define configIDLE_SHOULD_YIELD					1               /* 1: 空闲任务应该在其时间片内让出CPU; 0: 不让出 */
#define configUSE_MUTEXES						1               /* 1: 启用互斥量; 0: 禁用 */
#define configCHECK_FOR_STACK_OVERFLOW			0               /* 0: 禁用堆栈溢出检测 - 在使用Win32模拟器时不适用 */
#define configUSE_RECURSIVE_MUTEXES				1               /* 1: 启用递归互斥量; 0: 禁用 */
#define configQUEUE_REGISTRY_SIZE				10              /* 定义可以在队列注册中注册的最大队列和信号量数量 */
#define configUSE_MALLOC_FAILED_HOOK			1               /* 1: 使用内存分配失败钩子; 0: 不使用 */
#define configUSE_APPLICATION_TASK_TAG			0               /* 1: 允许为任务分配标签; 0: 不允许 */
#define configUSE_COUNTING_SEMAPHORES			1               /* 1: 启用计数信号量; 0: 禁用 */
#define configUSE_ALTERNATIVE_API				0               /* 1: 使用替代API; 0: 使用标准API - 现已弃用 */
#define configUSE_QUEUE_SETS					1               /* 1: 启用队列集; 0: 禁用 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						0               /* 1: 启用软件定时器; 0: 禁用 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器服务任务优先级 */
#define configTIMER_QUEUE_LENGTH				20              /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务堆栈深度 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0               /* 1: 生成运行时统计数据; 0: 不生成 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0               /* 1: 启用协程; 0: 禁用 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2               /* 定义协程最大优先级数 */

/* 此演示不使用一个或多个示例统计格式化函数，这些函数将由uxTaskGetSystemState()函数
提供的原始数据格式化为人类可读的ASCII形式 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0               /* 1: 使用统计格式化函数; 0: 不使用 */

/* 
 * 将以下定义设置为1以包含API函数，或设置为0以排除API函数。
 * 在大多数情况下，链接器会自动移除未使用的函数。
 * 这些定义控制哪些可选API函数被编译到项目中
 */
#define INCLUDE_vTaskPrioritySet				1               /* 包含任务优先级设置功能 */
#define INCLUDE_uxTaskPriorityGet				1               /* 包含获取任务优先级功能 */
#define INCLUDE_vTaskDelete						1               /* 包含删除任务功能 */
#define INCLUDE_vTaskSuspend					1               /* 包含任务挂起功能 */
#define INCLUDE_vTaskDelayUntil					1               /* 包含精确延时功能 */
#define INCLUDE_vTaskDelay						1               /* 包含相对延时功能 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1               /* 包含获取任务堆栈最大使用量功能 */
#define INCLUDE_xTaskGetSchedulerState			1               /* 包含获取调度器状态功能 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1               /* 包含获取定时器守护任务句柄功能 */
#define INCLUDE_xTaskGetIdleTaskHandle			1               /* 包含获取空闲任务句柄功能 */
#define INCLUDE_pcTaskGetTaskName				1               /* 包含获取任务名称功能 */
#define INCLUDE_eTaskGetState					1               /* 包含获取任务状态功能 */
#define INCLUDE_xSemaphoreGetMutexHolder		1               /* 包含获取互斥量持有者功能 */
#define INCLUDE_xTimerPendFunctionCall			1               /* 包含定时器挂起函数调用功能 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()
使用与标准C assert()宏相同的语义。它用于验证重要参数或执行条件检查。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ )

#endif /* FREERTOS_CONFIG_H */
