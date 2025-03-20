/*
    FreeRTOS V9.0.0 - Copyright (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费但专业开发的、健壮的、严格质量控制的、         *
     *    支持良好的跨平台软件，已成为事实上的标准。                         *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者来帮助自己快速入门        *
     *    并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation         *
     *                                                                       *
     *    感谢您的支持！                                                     *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（版本2）重新分发和/或
    修改它，该许可证由自由软件基金会发布，并由FreeRTOS例外条款修改。

    注意：对GPL的修改包括允许您分发包含FreeRTOS的组合作品，而不必提供
    FreeRTOS内核外的专有组件的源代码。

    FreeRTOS的分发希望能有所帮助，但不提供任何保证；甚至没有对适销性或
    特定用途适用性的暗示保证。完整的许可证文本可从以下链接获取：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？首先阅读FAQ"我的应用程序无法运行，可能出了什么问题？"    *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                              *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和
    Real Time Engineers Ltd.联系方式。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品的选择，包括
    FreeRTOS+Trace（不可或缺的生产力工具）、与DOS兼容的FAT文件系统和
    我们的小型线程感知UDP/IP堆栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd许可FreeRTOS给
    High Integrity Systems，以便后者可以以OpenRTOS品牌销售。低成本OpenRTOS
    许可证提供有票据支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供经过安全工程和
    独立SIL3认证的版本，用于需要可证明可靠性的安全和任务关键型应用程序。

    1个制表符 == 4个空格！
*/


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * 应用程序特定定义
 *
 * 这些定义应该根据您的特定硬件和应用程序需求进行调整。
 *
 * 这些参数在FreeRTOS API文档的"配置"部分中有详细描述，
 * 该文档可在FreeRTOS.org网站上和FreeRTOS参考手册中获取。
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION					1               /* 启用抢占式调度 */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION	1               /* 使用优化的任务选择方法 */
#define configMAX_PRIORITIES					5               /* 定义最大优先级数量（0到4） */
#define configUSE_IDLE_HOOK						0               /* 不使用空闲钩子函数 */
#define configUSE_TICK_HOOK						0               /* 不使用时钟中断钩子函数 */
#define configTICK_RATE_HZ						( 1000 )         /* 系统时钟频率为1000Hz（这是模拟环境，因此不是真正的实时） */
#define configMINIMAL_STACK_SIZE				( ( unsigned short ) 50 ) /* 在这个模拟情况下，栈只需要容纳一个小结构，因为真正的栈是win32线程的一部分 */
#define configTOTAL_HEAP_SIZE					( ( size_t ) ( 20 * 1024 ) ) /* 总堆大小为20KB */
#define configMAX_TASK_NAME_LEN					( 12 )          /* 任务名称的最大长度 */
#define configUSE_TRACE_FACILITY				0               /* 不使用跟踪功能 */
#define configUSE_16_BIT_TICKS					0               /* 使用32位系统节拍计数器 */
#define configIDLE_SHOULD_YIELD					1               /* 空闲任务应该在有相同优先级的任务就绪时让出CPU */
#define configUSE_MUTEXES						1               /* 启用互斥量 */
#define configCHECK_FOR_STACK_OVERFLOW			0               /* 不检查栈溢出（在使用Win32模拟器时不适用） */
#define configUSE_RECURSIVE_MUTEXES				1               /* 启用递归互斥量 */
#define configQUEUE_REGISTRY_SIZE				10              /* 队列注册表大小 */
#define configUSE_MALLOC_FAILED_HOOK			1               /* 使用内存分配失败钩子函数 */
#define configUSE_APPLICATION_TASK_TAG			0               /* 不使用应用任务标签 */
#define configUSE_COUNTING_SEMAPHORES			1               /* 启用计数信号量 */
#define configUSE_ALTERNATIVE_API				0               /* 不使用替代API */
#define configUSE_QUEUE_SETS					1               /* 启用队列集 */

/* 软件定时器相关配置选项 */
#define configUSE_TIMERS						0               /* 不使用软件定时器 */
#define configTIMER_TASK_PRIORITY				( configMAX_PRIORITIES - 1 ) /* 定时器任务的优先级（如果启用） */
#define configTIMER_QUEUE_LENGTH				20              /* 定时器命令队列长度 */
#define configTIMER_TASK_STACK_DEPTH			( configMINIMAL_STACK_SIZE * 2 ) /* 定时器任务的栈深度 */

/* 运行时统计收集配置选项 */
#define configGENERATE_RUN_TIME_STATS			0               /* 不生成运行时统计信息 */

/* 协程相关配置选项 */
#define configUSE_CO_ROUTINES 					0               /* 不使用协程 */
#define configMAX_CO_ROUTINE_PRIORITIES 		2               /* 如果使用协程，最大协程优先级为2 */

/* 此演示不使用一个或多个示例统计格式化函数，
   这些函数将uxTaskGetSystemState()函数提供的原始数据
   格式化为人类可读的ASCII形式。 */
#define configUSE_STATS_FORMATTING_FUNCTIONS	0               /* 不使用统计格式化函数 */

/* 将以下定义设置为1以包含API函数，或设置为零以排除API函数。
   在大多数情况下，链接器会自动删除未使用的函数。 */
#define INCLUDE_vTaskPrioritySet				1               /* 包含修改任务优先级的函数 */
#define INCLUDE_uxTaskPriorityGet				1               /* 包含获取任务优先级的函数 */
#define INCLUDE_vTaskDelete						1               /* 包含删除任务的函数 */
#define INCLUDE_vTaskSuspend					1               /* 包含挂起任务的函数 */
#define INCLUDE_vTaskDelayUntil					1               /* 包含精确延时任务的函数 */
#define INCLUDE_vTaskDelay						1               /* 包含延时任务的函数 */
#define INCLUDE_uxTaskGetStackHighWaterMark		1               /* 包含获取任务栈使用峰值的函数 */
#define INCLUDE_xTaskGetSchedulerState			1               /* 包含获取调度器状态的函数 */
#define INCLUDE_xTimerGetTimerDaemonTaskHandle	1               /* 包含获取定时器守护任务句柄的函数 */
#define INCLUDE_xTaskGetIdleTaskHandle			1               /* 包含获取空闲任务句柄的函数 */
#define INCLUDE_pcTaskGetTaskName				1               /* 包含获取任务名称的函数 */
#define INCLUDE_eTaskGetState					1               /* 包含获取任务状态的函数 */
#define INCLUDE_xSemaphoreGetMutexHolder		1               /* 包含获取互斥量持有者的函数 */
#define INCLUDE_xTimerPendFunctionCall			1               /* 包含在定时器服务任务中挂起函数调用的函数 */

/* 在开发过程中定义configASSERT()是个好主意。configASSERT()
   使用与标准C assert()宏相同的语义。 */
extern void vAssertCalled( uint32_t ulLine, const char * const pcFileName );
#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled( __LINE__, __FILE__ ) /* 断言检查，用于捕获错误 */

#endif /* FREERTOS_CONFIG_H */
