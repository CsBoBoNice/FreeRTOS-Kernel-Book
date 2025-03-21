# 目录

## [1 序言](ch01.md#1-preface)
  + [1.1 在小型嵌入式系统中进行多任务处理](ch01.md#11-multitasking-in-small-embedded-systems)
    + [1.1.1 关于 FreeRTOS 内核](ch01.md#111-about-the-freertos-kernel)
    + [1.1.2 价值主张](ch01.md#112-value-proposition)
    + [1.1.3 关于术语的说明](ch01.md#113-a-note-about-terminology)
    + [1.1.4 为什么使用 RTOS？](ch01.md#114-why-use-an-rtos)
    + [1.1.5 FreeRTOS 内核特性](ch01.md#115-freertos-kernel-features)
    + [1.1.6 许可，以及 FreeRTOS、OpenRTOS 和 SafeRTOS 系列](ch01.md#116-licensing-and-the-freertos-openrtos-and-safertos-family)
  + [1.2 包含的源文件和项目](ch01.md#12-included-source-files-and-projects)
    + [1.2.1 获取本书附带的示例](ch01.md#121-obtaining-the-examples-that-accompany-this-book)

## [2 FreeRTOS 内核发行版](ch02.md#2-the-freertos-kernel-distribution)
  + [2.1 简介](ch02.md#21-introduction)
  + [2.2 理解 FreeRTOS 发行版](ch02.md#22-understanding-the-freertos-distribution)
    + [2.2.1 定义：FreeRTOS 端口](ch02.md#221-definition-freertos-port)
    + [2.2.2 构建 FreeRTOS](ch02.md#222-building-freertos)
    + [2.2.3 FreeRTOSConfig.h](ch02.md#223-freertosconfigh)
    + [2.2.4 官方发行版](ch02.md#224-official-distributions)
    + [2.2.5 所有端口通用的 FreeRTOS 源文件](ch02.md#225-freertos-source-files-common-to-all-ports)
    + [2.2.6 特定于端口的 FreeRTOS 源文件](ch02.md#226-freertos-source-files-specific-to-a-port)
    + [2.2.7 包含路径](ch02.md#227-include-paths)
    + [2.2.8 头文件](ch02.md#228-header-files)
  + [2.3 演示应用程序](ch02.md#23-demo-applications)
  + [2.4 创建 FreeRTOS 项目](ch02.md#24-creating-a-freertos-project)
    + [2.4.1 调整提供的演示项目之一](ch02.md#241-adapting-one-of-the-supplied-demo-projects)
    + [2.4.2 从头开始创建一个新项目](ch02.md#242-creating-a-new-project-from-scratch)
  + [2.5 数据类型和编码风格指南](ch02.md#25-data-types-and-coding-style-guide)
    + [2.5.1 数据类型](ch02.md#251-data-types)
    + [2.5.2 变量名](ch02.md#252-variable-names)
    + [2.5.3 函数名](ch02.md#253-function-names)
    + [2.5.4 格式](ch02.md#254-formatting)
    + [2.5.5 宏名](ch02.md#255-macro-names)
    + [2.5.6 过度类型转换的理由](ch02.md#256-rationale-for-excessive-type-casting)

## [3 堆内存管理](ch03.md#3-heap-memory-management)
  + [3.1 简介](ch03.md#31-introduction)
    + [3.1.1 先决条件](ch03.md#311-prerequisites)
    + [3.1.2 范围](ch03.md#312-scope)
    + [3.1.3 在静态和动态内存分配之间切换](ch03.md#313-switching-between-static-and-dynamic-memory-allocation)
    + [3.1.4 使用动态内存分配](ch03.md#314-using-dynamic-memory-allocation)
    + [3.1.5 动态内存分配选项](ch03.md#315-options-for-dynamic-memory-allocation)
  + [3.2 示例内存分配方案](ch03.md#32-example-memory-allocation-schemes)
    + [3.2.1 Heap_1](ch03.md#321-heap_1)
    + [3.2.2 Heap_2](ch03.md#322-heap_2)
    + [3.2.3 Heap_3](ch03.md#323-heap_3)
    + [3.2.4 Heap_4](ch03.md#324-heap_4)
    + [3.2.5 Heap_5](ch03.md#325-heap_5)
    + [3.2.6 初始化 heap_5：vPortDefineHeapRegions() API 函数](ch03.md#326-initialising-heap_5-the-vportdefineheapregions-api-function)
  + [3.3 与堆相关的实用函数和宏](ch03.md#33-heap-related-utility-functions-and-macros)
    + [3.3.1 定义堆起始地址](ch03.md#331-defining-the-heap-start-address)
    + [3.3.2 xPortGetFreeHeapSize() API 函数](ch03.md#332-the-xportgetfreeheapsize-api-function)
    + [3.3.3 xPortGetMinimumEverFreeHeapSize() API 函数](ch03.md#333-the-xportgetminimumeverfreeheapsize-api-function)
    + [3.3.4 vPortGetHeapStats() API 函数](ch03.md#334-the-vportgetheapstats-api-function)
    + [3.3.5 收集每个任务的堆使用统计信息](ch03.md#335-collecting-per-task-heap-usage-statistics)
    + [3.3.6 malloc 失败挂钩函数](ch03.md#336-malloc-failed-hook-functions)
    + [3.3.7 将任务堆栈放置在快速内存中](ch03.md#337-placing-task-stacks-in-fast-memory)
  + [3.4 使用静态内存分配](ch03.md#34-using-static-memory-allocation)
    + [3.4.1 启用静态内存分配](ch03.md#341-enabling-static-memory-allocation)
    + [3.4.2 静态内部内核内存](ch03.md#342-static-internal-kernel-memory)
      + [3.4.2.1 vApplicationGetTimerTaskMemory](ch03.md#3421-vapplicationgettimertaskmemory)
      + [3.4.2.2 vApplicationGetIdleTaskMemory](ch03.md#3422-vapplicationgetidletaskmemory)

## [4 任务管理](ch04.md#4-task-management)
  + [4.1 简介](ch04.md#41-introduction)
    + [4.1.1 范围](ch04.md#411-scope)
  + [4.2 任务函数](ch04.md#42-task-functions)
  + [4.3 顶级任务状态](ch04.md#43-top-level-task-states)
  + [4.4 任务创建](ch04.md#44-task-creation)
    + [4.4.1 xTaskCreate() API 函数](ch04.md#441-the-xtaskcreate-api-function)
  + [4.5 任务优先级](ch04.md#45-task-priorities)
    + [通用调度器](ch04.md#451-generic-scheduler)
    + [针对架构优化的调度器](ch04.md#452-architecture-optimized-scheduler)
  + [4.6 时间测量和滴答中断](ch04.md#46-time-measurement-and-the-tick-interrupt)
  + [4.7 扩展 *未运行* 状态](ch04.md#47-expanding-the-not-running-state)
    + [4.7.1 *阻塞* 状态](ch04.md#471-the-blocked-state)
    + [4.7.2 *挂起* 状态](ch04.md#472-the-suspended-state)
    + [4.7.3 就绪状态](ch04.md#473-the-ready-state)
    + [4.7.4 完成状态转换图](ch04.md#474-completing-the-state-transition-diagram)
    + [4.7.5 vTaskDelayUntil() API 函数](ch04.md#475-the-vtaskdelayuntil-api-function)
  + [4.8 空闲任务和空闲任务挂钩](ch04.md#48-the-idle-task-and-the-idle-task-hook)
    + [4.8.1 空闲任务挂钩函数](ch04.md#481-idle-task-hook-functions)
    + [4.8.2 空闲任务挂钩函数实现的限制](ch04.md#482-limitations-on-the-implementation-of-idle-task-hook-functions)
  + [4.9 更改任务的优先级](ch04.md#49-changing-the-priority-of-a-task)
    + [4.9.1 vTaskPrioritySet() API 函数](ch04.md#491-the-vtaskpriorityset-api-function)
    + [4.9.2 uxTaskPriorityGet() API 函数](ch04.md#492-the-uxtaskpriorityget-api-function)
  + [4.10 删除任务](ch04.md#410-deleting-a-task)
    + [4.10.1 vTaskDelete() API 函数](ch04.md#4101-the-vtaskdelete-api-function)
  + [4.11 线程局部存储和重入](ch04.md#411-thread-local-storage-and-reentrancy)
    + [4.11.1 C 运行时线程局部存储实现](ch04.md#4111-c-runtime-thread-local-storage-implementations)
    + [4.11.2 自定义 C 运行时线程局部存储](ch04.md#4112-custom-c-runtime-thread-local-storage)
    + [4.11.3 应用程序线程局部存储](ch04.md#4113-application-thread-local-storage)
  + [4.12 调度算法](ch04.md#412-scheduling-algorithms)
    + [4.12.1 任务状态和事件回顾](ch04.md#4121-a-recap-of-task-states-and-events)
    + [4.12.2 选择调度算法](ch04.md#4122-selecting-the-scheduling-algorithm)
    + [4.12.3 带时间片划分的优先级抢占式调度](ch04.md#4123-prioritized-preemptive-scheduling-with-time-slicing)
    + [4.12.4 不带时间片划分的优先级抢占式调度](ch04.md#4124-prioritized-preemptive-scheduling-without-time-slicing)
    + [4.12.5 协同调度](ch04.md#4125-cooperative-scheduling)

## [5 队列管理](ch05.md#5-queue-management)
  + [5.1 简介](ch05.md#51-introduction)
    + [5.1.1 范围](ch05.md#511-scope)
  + [5.2 队列的特性](ch05.md#52-characteristics-of-a-queue)
    + [5.2.1 数据存储](ch05.md#521-data-storage)
    + [5.2.2 多任务访问](ch05.md#522-access-by-multiple-tasks)
    + [5.2.3 读取队列时阻塞](ch05.md#523-blocking-on-queue-reads)
    + [5.2.4 写入队列时阻塞](ch05.md#524-blocking-on-queue-writes)
    + [5.2.5 在多个队列上阻塞](ch05.md#525-blocking-on-multiple-queues)
    + [5.2.6 创建队列：静态分配和动态分配队列](ch05.md#526-creating-queues-statically-allocated-and-dynamically-allocated-queues)
  + [5.3 使用队列](ch05.md#53-using-a-queue)
    + [5.3.1 xQueueCreate() API 函数](ch05.md#531-the-xqueuecreate-api-function)
    + [5.3.2 xQueueSendToBack() 和 xQueueSendToFront() API 函数](ch05.md#532-the-xqueuesendtoback-and-xqueuesendtofront-api-functions)
    + [5.3.3 xQueueReceive() API 函数](ch05.md#533-the-xqueuereceive-api-function)
    + [5.3.4 uxQueueMessagesWaiting() API 函数](ch05.md#534-the-uxqueuemessageswaiting-api-function)
  + [5.4 从多个来源接收数据](ch05.md#54-receiving-data-from-multiple-sources)
  + [5.5 处理大型或可变大小的数据](ch05.md#55-working-with-large-or-variable-sized-data)
    + [5.5.1 队列指针](ch05.md#551-queuing-pointers)
    + [5.5.2 使用队列发送不同类型和长度的数据[^9]](ch05.md#552-using-a-queue-to-send-different-types-and-lengths-of-data9)
  + [5.6 从多个队列接收](ch05.md#56-receiving-from-multiple-queues)
    + [5.6.1 队列集合](ch05.md#561-queue-sets)
    + [5.6.2 xQueueCreateSet() API 函数](ch05.md#562-the-xqueuecreateset-api-function)
    + [5.6.3 xQueueAddToSet() API 函数](ch05.md#563-the-xqueueaddtoset-api-function)
    + [5.6.4 xQueueSelectFromSet() API 函数](ch05.md#564-the-xqueueselectfromset-api-function)
    + [5.6.5 更实际的队列集合用例](ch05.md#565-more-realistic-queue-set-use-cases)
  + [5.7 使用队列创建邮箱](ch05.md#57-using-a-queue-to-create-a-mailbox)
    + [5.7.1 xQueueOverwrite() API 函数](ch05.md#571-the-xqueueoverwrite-api-function)
    + [5.7.2 xQueuePeek() API 函数](ch05.md#572-the-xqueuepeek-api-function)

## [6 软件定时器管理](ch06.md#6-software-timer-management)
  + [6.1 章节介绍和范围](ch06.md#61-chapter-introduction-and-scope)
    + [6.1.1 范围](ch06.md#611-scope)
  + [6.2 软件定时器回调函数](ch06.md#62-software-timer-callback-functions)
  + [6.3 软件定时器的属性和状态](ch06.md#63-attributes-and-states-of-a-software-timer)
    + [6.3.1 软件定时器的周期](ch06.md#631-period-of-a-software-timer)
    + [6.3.2 单次触发和自动重载定时器](ch06.md#632-one-shot-and-auto-reload-timers)
    + [6.3.3 软件定时器状态](ch06.md#633-software-timer-states)
  + [6.4 软件定时器的上下文](ch06.md#64-the-context-of-a-software-timer)
    + [6.4.1 RTOS守护进程（定时器服务）任务](ch06.md#641-the-rtos-daemon-timer-service-task)
    + [6.4.2 定时器命令队列](ch06.md#642-the-timer-command-queue)
    + [6.4.3 守护进程任务调度](ch06.md#643-daemon-task-scheduling)
  + [6.5 创建和启动软件定时器](ch06.md#65-creating-and-starting-a-software-timer)
    + [6.5.1 xTimerCreate() API 函数](ch06.md#651-the-xtimercreate-api-function)
    + [6.5.2 xTimerStart() API 函数](ch06.md#652-the-xtimerstart-api-function)
  + [6.6 定时器ID](ch06.md#66-the-timer-id)
    + [6.6.1 vTimerSetTimerID() API 函数](ch06.md#661-the-vtimersettimerid-api-function)
    + [6.6.2 pvTimerGetTimerID() API 函数](ch06.md#662-the-pvtimergettimerid-api-function)
  + [6.7 更改定时器的周期](ch06.md#67-changing-the-period-of-a-timer)
    + [6.7.1 xTimerChangePeriod() API 函数](ch06.md#671-the-xtimerchangeperiod-api-function)
  + [6.8 重置软件定时器](ch06.md#68-resetting-a-software-timer)
    + [6.8.1 xTimerReset() API 函数](ch06.md#681-the-xtimerreset-api-function)

## [7 中断管理](ch07.md#7-interrupt-management)
  + [7.1 介绍](ch07.md#71-introduction)
    + [7.1.1 事件](ch07.md#711-events)
    + [7.1.2 范围](ch07.md#712-scope)
  + [7.2 在中断服务例程 (ISR) 中使用 FreeRTOS API](ch07.md#72-using-the-freertos-api-from-an-isr)
    + [7.2.1 中断安全 API](ch07.md#721-the-interrupt-safe-api)
    + [7.2.2 使用单独中断安全 API 的优势](ch07.md#722-the-benefits-of-using-a-separate-interrupt-safe-api)
    + [7.2.3 使用单独中断安全 API 的缺点](ch07.md#723-the-disadvantages-of-using-a-separate-interrupt-safe-api)
    + [7.2.4 xHigherPriorityTaskWoken 参数](ch07.md#724-the-xhigherprioritytaskwoken-parameter)
    + [7.2.5 portYIELD_FROM_ISR() 和 portEND_SWITCHING_ISR() 宏](ch07.md#725-the-portyield_from_isr-and-portend_switching_isr-macros)
  + [7.3 推迟中断处理](ch07.md#73-deferred-interrupt-processing)
  + [7.4 用于同步的二进制信号量](ch07.md#74-binary-semaphores-used-for-synchronization)
    + [7.4.1 xSemaphoreCreateBinary() API 函数](ch07.md#741-the-xsemaphorecreatebinary-api-function)
    + [7.4.2 xSemaphoreTake() API 函数](ch07.md#742-the-xsemaphoretake-api-function)
    + [7.4.3 xSemaphoreGiveFromISR() API 函数](ch07.md#743-the-xsemaphoregivefromisr-api-function)
    + [7.4.4 改进示例 7.1 中使用的任务的实现](ch07.md#744-improving-the-implementation-of-the-task-used-in-example-71)
  + [7.5 计数信号量](ch07.md#75-counting-semaphores)
    + [7.5.1 xSemaphoreCreateCounting() API 函数](ch07.md#751-the-xsemaphorecreatecounting-api-function)
  + [7.6 将工作推迟到 RTOS 守护进程任务](ch07.md#76-deferring-work-to-the-rtos-daemon-task)
    + [7.6.1 xTimerPendFunctionCallFromISR() API 函数](ch07.md#761-the-xtimerpendfunctioncallfromisr-api-function)
  + [7.7 在中断服务例程中 (ISR) 使用队列](ch07.md#77-using-queues-within-an-interrupt-service-routine)
    + [7.7.1 xQueueSendToFrontFromISR() 和 xQueueSendToBackFromISR() API 函数](ch07.md#771-the-xqueuesendtofrontfromisr-and-xqueuesendtobackfromisr-api-functions)
    + [7.7.2 在 ISR 中使用队列时的注意事项](ch07.md#772-considerations-when-using-a-queue-from-an-isr)
  + [7.8 中断嵌套](ch07.md#78-interrupt-nesting)
    + [7.8.1 注意事项：ARM Cortex-M[^22] 和 ARM GIC 用户](ch07.md#781-a-note-to-arm-cortex-m22-and-arm-gic-users)

## [8 资源管理](ch08.md#8-resource-management)
  + [8.1 章节介绍和范围](ch08.md#81-chapter-introduction-and-scope)
    + [8.1.1 互斥](ch08.md#811-mutual-exclusion)
    + [8.1.2 范围](ch08.md#812-scope)
  + [8.2 临界区和挂起调度器](ch08.md#82-critical-sections-and-suspending-the-scheduler)
    + [8.2.1 基本临界区](ch08.md#821-basic-critical-sections)
    + [8.2.2 挂起（或锁定）调度器](ch08.md#822-suspending-or-locking-the-scheduler)
    + [8.2.3 vTaskSuspendAll() API 函数](ch08.md#823-the-vtasksuspendall-api-function)
    + [8.2.4 xTaskResumeAll() API 函数](ch08.md#824-the-xtaskresumeall-api-function)
  + [8.3 互斥锁（和二进制信号量）](ch08.md#83-mutexes-and-binary-semaphores)
    + [8.3.1 xSemaphoreCreateMutex() API 函数](ch08.md#831-the-xsemaphorecreatemutex-api-function)
    + [8.3.2 优先级反转](ch08.md#832-priority-inversion)
    + [8.3.3 优先级继承](ch08.md#833-priority-inheritance)
    + [8.3.4 互锁（或致命拥抱）](ch08.md#834-deadlock-or-deadly-embrace)
    + [8.3.5 递归互斥锁](ch08.md#835-recursive-mutexes)
    + [8.3.6 互斥锁和任务调度](ch08.md#836-mutexes-and-task-scheduling)
  + [8.4 守门人任务](ch08.md#84-gatekeeper-tasks)
    + [8.4.1 重新编写 vPrintString() 以使用守门人任务](ch08.md#841-re-writing-vprintstring-to-use-a-gatekeeper-task)

## [9 事件组](ch09.md#9-event-groups)
  + [9.1 章节介绍和范围](ch09.md#91-chapter-introduction-and-scope)
    + [9.1.1 范围](ch09.md#911-scope)
  + [9.2 事件组的特性](ch09.md#92-characteristics-of-an-event-group)
    + [9.2.1 事件组、事件标志和事件位](ch09.md#921-event-groups-event-flags-and-event-bits)
    + [9.2.2 关于 EventBits_t 数据类型的更多信息](ch09.md#922-more-about-the-eventbits_t-data-type)
    + [9.2.3 多任务访问](ch09.md#923-access-by-multiple-tasks)
    + [9.2.4 使用事件组的实际示例](ch09.md#924-a-practical-example-of-using-an-event-group)
  + [9.3 使用事件组进行事件管理](ch09.md#93-event-management-using-event-groups)
    + [9.3.1 xEventGroupCreate() API 函数](ch09.md#931-the-xeventgroupcreate-api-function)
    + [9.3.2 xEventGroupSetBits() API 函数](ch09.md#932-the-xeventgroupsetbits-api-function)
    + [9.3.3 xEventGroupSetBitsFromISR() API 函数](ch09.md#933-the-xeventgroupsetbitsfromisr-api-function)
    + [9.3.4 xEventGroupWaitBits() API 函数](ch09.md#934-the-xeventgroupwaitbits-api-function)
    + [9.3.5 xEventGroupGetStaticBuffer() API 函数](ch09.md#935-the-xeventgroupgetstaticbuffer-api-function)
  + [9.4 使用事件组进行任务同步](ch09.md#94-task-synchronization-using-an-event-group)
    + [9.4.1 xEventGroupSync() API 函数](ch09.md#941-the-xeventgroupsync-api-function)

## [10 任务通知](ch10.md#10-task-notifications)
  + [10.1 介绍](ch10.md#101-introduction)
    + [10.1.1 通过中间对象进行通信](ch10.md#1011-communicating-through-intermediary-objects)
    + [10.1.2 任务通知——直接到任务的通信](ch10.md#1012-task-notificationsdirect-to-task-communication)
    + [10.1.3 范围](ch10.md#1013-scope)
  + [10.2 任务通知：优点和局限性](ch10.md#102-task-notifications-benefits-and-limitations)
    + [10.2.1 任务通知的性能优势](ch10.md#1021-performance-benefits-of-task-notifications)
    + [10.2.2 任务通知的 RAM 占用优势](ch10.md#1022-ram-footprint-benefits-of-task-notifications)
    + [10.2.3 任务通知的局限性](ch10.md#1023-limitations-of-task-notifications)
  + [10.3 使用任务通知](ch10.md#103-using-task-notifications)
    + [10.3.1 任务通知 API 选项](ch10.md#1031-task-notification-api-options)
      + [10.3.1.1 API 函数的完整列表 <sup>27</sup>](ch10.md#10311-the-complete-list-of-api-functions-sup27sup)
    + [10.3.2 xTaskNotifyGive() API 函数](ch10.md#1032-the-xtasknotifygive-api-functions)
    + [10.3.3 vTaskNotifyGiveFromISR() API 函数](ch10.md#1033-the-vtasknotifygivefromisr-api-function)
    + [10.3.4 ulTaskNotifyTake() API 函数](ch10.md#1034-the-ultasknotifytake-api-function)
    + [10.3.5 xTaskNotify() 和 xTaskNotifyFromISR() API 函数](ch10.md#1035-the-xtasknotify-and-xtasknotifyfromisr-api-functions)
    + [10.3.6 xTaskNotifyWait() API 函数](ch10.md#1036-the-xtasknotifywait-api-function)
    + [10.3.7 任务通知在外设驱动程序中的使用：UART 示例](ch10.md#1037-task-notifications-used-in-peripheral-device-drivers-uart-example)
    + [10.3.8 任务通知在外设驱动程序中的使用：ADC 示例](ch10.md#1038-task-notifications-used-in-peripheral-device-drivers-adc-example)
    + [10.3.9 任务通知在应用程序中的直接使用](ch10.md#1039-task-notifications-used-directly-within-an-application)

## [11 低功耗支持](ch11.md#11-low-power-support)
  + [11.1 节能介绍](ch11.md#111-power-saving-introduction)
  + [11.2 FreeRTOS 休眠模式](ch11.md#112-freertos-sleep-modes)
  + [11.3 函数和启用内置无计时器空闲功能](ch11.md#113-functions-and-enabling-built-in-tickless-idle-functionality)
    + [11.3.1 portSUPPRESS_TICKS_AND_SLEEP() 宏](ch11.md#1131-the-portsuppress_ticks_and_sleep-macro)
    + [11.3.2 vPortSuppressTicksAndSleep 函数](ch11.md#1132-the-vportsuppressticksandsleep-function)
    + [11.3.3 eTaskConfirmSleepModeStatus 函数](ch11.md#1133-the-etaskconfirmsleepmodestatus-function)
    + [11.3.4 configPRE_SLEEP_PROCESSING 配置](ch11.md#1134-the-configpre_sleep_processing-configuration)
    + [11.3.5 configPOST_SLEEP_PROCESSING 配置](ch11.md#1135-the-configpost_sleep_processing-configuration)
  + [11.4 实现 portSUPPRESS_TICKS_AND_SLEEP() 宏](ch11.md#114-implementing-portsuppress_ticks_and_sleep-macro)
  + [11.5 空闲任务挂钩函数](ch11.md#115-idle-task-hook-function)

## [12 开发者支持](ch12.md#12-developer-support)
  + [12.1 简介](ch12.md#121-introduction)
  + [12.2 configASSERT()](ch12.md#122-configassert)
    + [12.2.1 configASSERT() 定义示例](ch12.md#1221-example-configassert-definitions)
  + [12.3 FreeRTOS 的 Tracealyzer](ch12.md#123-tracealyzer-for-freertos)
  + [12.4 调试相关挂钩（回调）函数](ch12.md#124-debug-related-hook-callback-functions)
    + [12.4.1 内存分配失败挂钩](ch12.md#1241-malloc-failed-hook)
  + [12.5 查看运行时和任务状态信息](ch12.md#125-viewing-run-time-and-task-state-information)
    + [12.5.1 任务运行时统计信息](ch12.md#1251-task-run-time-statistics)
    + [12.5.2 运行时统计时钟](ch12.md#1252-the-run-time-statistics-clock)
    + [12.5.3 配置应用程序以收集运行时统计信息](ch12.md#1253-configuring-an-application-to-collect-run-time-statistics)
    + [12.5.4 uxTaskGetSystemState() API 函数](ch12.md#1254-the-uxtaskgetsystemstate-api-function)
    + [12.5.5 vTaskListTasks() 辅助函数](ch12.md#1255-the-vtasklisttasks-helper-function)
    + [12.5.6 vTaskGetRunTimeStatistics() 辅助函数](ch12.md#1256-the-vtaskgetruntimestatistics-helper-function)
    + [12.5.7 生成和显示运行时统计信息，一个实际示例](ch12.md#1257-generating-and-displaying-run-time-statistics-a-worked-example)
  + [12.6 跟踪挂钩宏](ch12.md#126-trace-hook-macros)
    + [12.6.1 可用的跟踪挂钩宏](ch12.md#1261-available-trace-hook-macros)
    + [12.6.2 定义跟踪挂钩宏](ch12.md#1262-defining-trace-hook-macros)
    + [12.6.3 FreeRTOS 兼容的调试器插件](ch12.md#1263-freertos-aware-debugger-plug-ins)

## [13 故障排除](ch13.md#13-troubleshooting)
  + [13.1 章节介绍和范围](ch13.md#131-chapter-introduction-and-scope)
  + [13.2 中断优先级](ch13.md#132-interrupt-priorities)
  + [13.3 堆栈溢出](ch13.md#133-stack-overflow)
    + [13.3.1 uxTaskGetStackHighWaterMark() API 函数](ch13.md#1331-the-uxtaskgetstackhighwatermark-api-function)
    + [13.3.2 运行时堆栈检查—概述](ch13.md#1332-run-time-stack-checkingoverview)
    + [13.3.3 运行时堆栈检查—方法 1](ch13.md#1333-run-time-stack-checkingmethod-1)
    + [13.3.4 运行时堆栈检查—方法 2](ch13.md#1334-run-time-stack-checkingmethod-2)
    + [13.3.5 运行时堆栈检查—方法 3](ch13.md#1334-run-time-stack-checkingmethod-3)
  + [13.4 printf() 和 sprintf() 的使用](ch13.md#134-use-of-printf-and-sprintf)
    + [13.4.1 printf-stdarg.c](ch13.md#1341-printf-stdargc)
  + [13.5 常见的其他错误来源](ch13.md#135-other-common-sources-of-error)
    + [13.5.1 症状：向演示程序添加一个简单任务会导致演示程序崩溃](ch13.md#1351-symptom-adding-a-simple-task-to-a-demo-causes-the-demo-to-crash)
    + [13.5.2 症状：在中断中调用 API 函数会导致应用程序崩溃](ch13.md#1352-symptom-using-an-api-function-within-an-interrupt-causes-the-application-to-crash)
    + [13.5.3 症状：应用程序有时会在中断服务例程中崩溃](ch13.md#1353-symptom-sometimes-the-application-crashes-within-an-interrupt-service-routine)
    + [13.5.4 症状：尝试启动第一个任务时，调度程序崩溃](ch13.md#1354-symptom-the-scheduler-crashes-when-attempting-to-start-the-first-task)
    + [13.5.5 症状：中断意外地保持禁用状态，或者关键部分不能正确嵌套](ch13.md#1355-symptom-interrupts-are-unexpectedly-left-disabled-or-critical-sections-do-not-nest-correctly)
    + [13.5.6 症状：在启动调度程序之前，应用程序就会崩溃](ch13.md#1356-symptom-the-application-crashes-even-before-the-scheduler-is-started)
    + [13.5.7 症状：在调度程序挂起时或在关键部分内部调用 API 函数会导致应用程序崩溃](ch13.md#1357-symptom-calling-api-functions-while-the-scheduler-is-suspended-or-from-inside-a-critical-section-causes-the-application-to-crash)
  + [13.6 其他调试步骤](ch13.md#136-additional-debugging-steps)


## 示例：
+ [示例 4.1 创建任务](ch04.md#example4.1)
+ [示例 4.2 使用任务参数](ch04.md#example4.2)
+ [示例 4.3 实验优先级](ch04.md#example4.3)
+ [示例 4.4 使用 *Blocked* 状态创建延迟](ch04.md#example4.4)
+ [示例 4.5 将示例任务转换为使用 vTaskDelayUntil()](ch04.md#example4.5)
+ [示例 4.6 组合阻塞和非阻塞任务](ch04.md#example4.6)
+ [示例 4.7 定义空闲任务挂钩函数](ch04.md#example4.7)
+ [示例 4.8 删除任务](ch04.md#example4.8)
+ [示例 5.1 从队列接收时阻塞](ch05.md#example5.1)
+ [示例 5.2 向队列发送时阻塞，以及在队列上发送结构体](ch05.md#example5.2)
+ [示例 5.3 使用队列集](ch05.md#example5.3)
+ [示例 6.1 创建单次和自动重载定时器](ch06.md#example6.1)
+ [示例 6.2 使用回调函数参数和软件定时器 ID](ch06.md#example6.2)
+ [示例 6.3 重置软件定时器](ch06.md#example6.3)
+ [示例 7.1 使用二进制信号量同步任务与中断](ch07.md#example7.1)
+ [示例 7.2 使用计数信号量同步任务与中断](ch07.md#example7.2)
+ [示例 7.3 集中式延迟中断处理](ch07.md#example7.3)
+ [示例 7.4 在中断中向队列发送和接收](ch07.md#example7.4)
+ [示例 8.1 重新编写 vPrintString() 以使用信号量](ch08.md#example8.1)
+ [示例 8.2 打印任务的替代实现](ch08.md#example8.2)
+ [示例 9.1 实验事件组](ch09.md#example9.1)
+ [示例 9.2 同步任务](ch09.md#example9.2)
+ [示例 10.1 使用任务通知代替信号量，方法 1](ch10.md#example10.1)
+ [示例 10.2 使用任务通知代替信号量，方法 2](ch10.md#example10.2)

## 图表：
+ [图 2.1 FreeRTOS 分发中的顶级目录](ch02.md#fig2.1)
+ [图 2.2 FreeRTOS 目录树中的核心 FreeRTOS 源代码文件](ch02.md#fig2.2)
+ [图 2.3 FreeRTOS 目录树中的特定于端口的源代码文件](ch02.md#fig2.3)
+ [图 2.4 演示目录层级结构](ch02.md#fig2.4)
+ [图 3.1 每次创建任务时，从 heap_1 数组分配的 RAM](ch03.md#fig3.1)
+ [图 3.2 任务创建和删除时，从 heap_2 数组分配和释放的 RAM](ch03.md#fig3.2)
+ [图 3.3 从 heap_4 数组分配和释放的 RAM](ch03.md#fig3.3)
+ [图 3.4 内存映射](ch03.md#fig3.4)
+ [图 4.1 顶级任务状态和转换](ch04.md#fig4.1)
+ [图 4.2 执行示例 4.1 产生的输出](ch04.md#fig4.2)
+ [图 4.3 两个示例 4.1 任务的实际执行模式](ch04.md#fig4.3)
+ [图 4.4 扩展的执行序列，显示中断定时器正在执行](ch04.md#fig4.4)
+ [图 4.5 以不同的优先级运行两个任务](ch04.md#fig4.5)
+ [图 4.6 当一个任务的优先级高于...时，执行模式](ch04.md#fig4.6)
+ [图 4.7 完整的任务状态机](ch04.md#fig4.7)
+ [图 4.8 执行示例 4.4 产生的输出](ch04.md#fig4.8)
+ [图 4.9 当任务使用 vTaskDelay() 代替空循环时，执行序列](ch04.md#fig4.9)
+ [图 4.10 粗体线条表示任务执行的状态转换...](ch04.md#fig4.10)
+ [图 4.11 执行示例 4.6 产生的输出](ch04.md#fig4.11)
+ [图 4.12 示例 4.6 的执行模式](ch04.md#fig4.12)
+ [图 4.13 执行示例 4.7 产生的输出](ch04.md#fig4.13)
+ [图 4.14 运行示例 4.8 时任务执行序列](ch04.md#fig4.14)
+ [图 4.15 执行示例 4.8 产生的输出](ch04.md#fig4.15)
+ [图 4.16 执行示例 4.9 产生的输出](ch04.md#fig4.16)
+ [图 4.17 示例 4.9 的执行序列](ch04.md#fig4.17)
+ [图 4.18 突出显示任务优先级和抢占的执行模式...](ch04.md#fig4.18)
+ [图 4.19 突出显示任务优先级和时间分片的执行模式...](ch04.md#fig4.19)
+ [图 4.20 与图 4.19 中所示的相同场景的执行模式...](ch04.md#fig4.20)
+ [图 4.21 演示具有相同优先级的任务如何...的执行模式](ch04.md#fig4.21)
+ [图 4.22 演示协作调度器行为的执行模式](ch04.md#fig4.22)
+ [图 5.1 向队列写入和从中读取的示例序列](ch05.md#fig5.1)
+ [图 5.2 执行示例 5.1 产生的输出](ch05.md#fig5.2)
+ [图 5.3 示例 5.1 产生的执行序列](ch05.md#fig5.3)
+ [图 5.4 在队列上发送结构体的示例场景](ch05.md#fig5.4)
+ [图 5.5 示例 5.2 产生的输出](ch05.md#fig5.5)
+ [图 5.6 示例 5.2 产生的执行序列](ch05.md#fig5.6)
+ [图 5.7 执行示例 5.3 产生的输出](ch05.md#fig5.7)
+ [图 6.1 单次触发软件定时器和自动重载软件定时器之间的行为差异](ch06.md#fig6.1)
+ [图 6.2 自动重载软件定时器的状态和转换](ch06.md#fig6.2)
+ [图 6.3 单次触发软件定时器的状态和转换](ch06.md#fig6.3)
+ [图 6.4 软件定时器 API 函数使用定时器命令队列与 RTOS 守护任务进行通信](ch06.md#fig6.4)
+ [图 6.5 调用 xTimerStart() 的任务优先级高于守护任务优先级时的执行模式](ch06.md#fig6.5)
+ [图 6.6 调用 xTimerStart() 的任务优先级低于守护任务优先级时的执行模式](ch06.md#fig6.6)
+ [图 6.7 执行示例 6.1 产生的输出](ch06.md#fig6.7)
+ [图 6.8 执行示例 6.2 产生的输出](ch06.md#fig6.8)
+ [图 6.9 启动和重置一个周期为 6 个时钟周期（ticks）的软件定时器](ch06.md#fig6.9)
+ [图 6.10 执行示例 6.3 产生的输出](ch06.md#fig6.10)
+ [图 7.1 在高优先级任务中完成中断处理](ch07.md#fig7.1)
+ [图 7.2 使用二进制信号量实现延迟中断处理](ch07.md#fig7.2)
+ [图 7.3 使用二进制信号量同步任务与中断](ch07.md#fig7.3)
+ [图 7.4 执行示例 7.1 产生的输出](ch07.md#fig7.4)
+ [图 7.5 执行示例 7.1 的执行序列](ch07.md#fig7.5)
+ [图 7.6 一个中断在任务完成第一个事件处理之前发生时的场景](ch07.md#fig7.6)
+ [图 7.7 两个中断在任务完成第一个事件处理之前发生时的场景](ch07.md#fig7.7)
+ [图 7.8 使用计数信号量](ch07.md#fig7.8)
+ [图 7.9 执行示例 7.2 产生的输出](ch07.md#fig7.9)
+ [图 7.10 执行示例 7.3 产生的输出](ch07.md#fig7.10)
+ [图 7.11 执行示例 7.3 的执行序列](ch07.md#fig7.11)
+ [图 7.12 执行示例 7.4 产生的输出](ch07.md#fig7.12)
+ [图 7.13 示例 7.4 产生的执行序列](ch07.md#fig7.13)
+ [图 7.14 影响中断嵌套行为的常量](ch07.md#fig7.14)
+ [图 7.15 具有四个优先级位的 Cortex-M 微控制器如何存储优先级 101](ch07.md#fig7.15)
+ [图 8.1 使用互斥锁实现互斥](ch08.md#fig8.1)
+ [图 8.2 执行示例 8.1 产生的输出](ch08.md#fig8.2)
+ [图 8.3 示例 8.1 的可能执行序列](ch08.md#fig8.3)
+ [图 8.4 一种最坏情况的优先级反转场景](ch08.md#fig8.4)
+ [图 8.5 优先级继承最大限度地减少优先级反转的影响](ch08.md#fig8.5)
+ [图 8.6 具有相同优先级的任务使用同一互斥锁时的一种可能的执行序列](ch08.md#fig8.6)
+ [图 8.7 如果创建了两个清单 8.15 中任务的实例并赋予相同的优先级，则可能发生的执行序列](ch08.md#fig8.7)
+ [图 8.8 执行示例 8.2 产生的输出](ch08.md#fig8.8)
+ [图 9.1 事件标志到位号的映射，在 EventBits_t 类型的变量中](ch09.md#fig9.1)
+ [图 9.2 一个事件组，其中只有位 1、4 和 7 被设置，所有其他事件标志都已清除，从而形成事件组](ch09.md#fig9.2)
+ [图 9.3 以 xWaitForAllBits 设置为 pdFALSE 执行示例 9.1 产生的输出](ch09.md#fig9.3)
+ [图 9.4 以 xWaitForAllBits 设置为 pdTRUE 执行示例 9.1 产生的输出](ch09.md#fig9.4)
+ [图 9.5 执行示例 9.2 产生的输出](ch09.md#fig9.5)
+ [图 10.1 通信对象用于将事件从一个任务发送到另一个任务](ch10.md#fig10.1)
+ [图 10.2 任务通知用于将事件直接从一个任务发送到另一个任务](ch10.md#fig10.2)
+ [图 10.3 执行示例 7.1 产生的输出](ch10.md#fig10.3)
+ [图 10.4 执行示例 10.1 的执行序列](ch10.md#fig10.4)
+ [图 10.5 执行示例 10.2 产生的输出](ch10.md#fig10.5)
+ [图 10.6 从应用程序任务到云服务器以及返回的通信路径](ch10.md#fig10.6)
+ [图 12.1 FreeRTOS+Trace 包含超过 20 个相互连接的视图](ch12.md#fig12.1)
+ [图 12.2 FreeRTOS+Trace 主跟踪视图 - 超过 20 个相互连接的跟踪视图之一](ch12.md#fig12.2)
+ [图 12.3 FreeRTOS+Trace CPU 负载视图 - 超过 20 个相互连接的跟踪视图之一](ch12.md#fig12.3)
+ [图 12.4 FreeRTOS+Trace 响应时间视图 - 超过 20 个相互连接的跟踪视图之一](ch12.md#fig12.4)
+ [图 12.5 FreeRTOS+Trace 用户事件绘图视图 - 超过 20 个相互连接的跟踪视图之一](ch12.md#fig12.5)
+ [图 12.6 FreeRTOS+Trace 内核对象历史视图 - 超过 20 个相互连接的跟踪视图之一](ch12.md#fig12.6)
+ [图 12.7 vTaskListTasks() 生成的示例输出](ch12.md#fig12.7)
+ [图 12.8 vTaskGetRunTimeStatistics() 生成的示例输出](ch12.md#fig12.8)


## 代码清单：
+ [清单 2.1 新的 main() 函数模板](ch02.md#list2.1)
+ [清单 3.1 vPortDefineHeapRegions() API 函数原型](ch03.md#list3.1)
+ [清单 3.2 HeapRegion_t 结构](ch03.md#list3.2)
+ [清单 3.3 描述 RAM 三个区域的 3 个 HeapRegion_t 结构数组](ch03.md#list3.3)
+ [清单 3.4 描述 RAM2 和 RAM3 的全部，但 RAM1 的部分，的 HeapRegion_t 结构数组](ch03.md#list3.4)
+ [清单 3.5 使用 GCC 语法声明将由 heap_4 使用的数组，并将数组放置在名为 .my_heap 的内存段中](ch03.md#list3.5)
+ [清单 3.6 使用 IAR 语法声明将由 heap_4 使用的数组，并将数组放置在绝对地址 0x20000000](ch03.md#list3.6)
+ [清单 3.7 xPortGetFreeHeapSize() API 函数原型](ch03.md#list3.7)
+ [清单 3.8 xPortGetMinimumEverFreeHeapSize() API 函数原型](ch03.md#list3.8)
+ [清单 3.9 vPortGetHeapStatus() API 函数原型](ch03.md#list3.9)
+ [清单 3.10 HeapStatus_t() 结构](ch03.md#list3.10)
+ [清单 3.11 收集每个任务的堆内存使用统计信息](ch03.md#list3.11)
+ [清单 3.12 malloc 失败挂钩函数名称和原型](ch03.md#list3.12)
+ [清单 3.13 将 pvPortMallocStack() 和 vPortFreeStack() 宏映射到应用程序定义的内存分配器](ch03.md#list3.13)
+ [清单 3.14 vApplicationGetTimerTaskMemory 的典型实现](ch03.md#list3.14)
+ [清单 3.15 vApplicationGetIdleTaskMemory 的典型实现](ch03.md#list3.15)
+ [清单 4.1 任务函数原型](ch04.md#list4.1)
+ [清单 4.2 典型任务函数结构](ch04.md#list4.2)
+ [清单 4.3 xTaskCreate() API 函数原型](ch04.md#list4.3)
+ [清单 4.4 示例 4.1 中使用的第一个任务的实现](ch04.md#list4.4)
+ [清单 4.5 示例 4.1 中使用的第二个任务的实现](ch04.md#list4.5)
+ [清单 4.6 启动示例 4.1 中的任务](ch04.md#list4.6)
+ [清单 4.7 在调度器启动后从另一个任务中创建任务](ch04.md#list4.7)
+ [清单 4.8 用于在示例 4.2 中创建两个任务的单个任务函数](ch04.md#list4.8)
+ [清单 4.9 示例 2 的 main() 函数](ch04.md#list4.9)
+ [清单 4.10 使用 pdMS_TO_TICKS() 宏将 200 毫秒转换为...](ch04.md#list4.10)
+ [清单 4.11. 以不同的优先级创建两个任务](ch04.md#list4.11)
+ [清单 4.12 vTaskDelay() API 函数原型](ch04.md#list4.12)
+ [清单 4.13 用调用替换空循环延迟后，示例任务的源代码...](ch04.md#list4.13)
+ [清单 4.14 vTaskDelayUntil() API 函数原型](ch04.md#list4.14)
+ [清单 4.15 使用 vTaskDelayUntil() 实现示例任务](ch04.md#list4.15)
+ [清单 4.16 示例 4.6 中使用的连续处理任务](ch04.md#list4.16)
+ [清单 4.17 示例 4.6 中使用的周期性任务](ch04.md#list4.17)
+ [清单 4.18 空闲任务挂钩函数名称和原型](ch04.md#list4.18)
+ [清单 4.19 一个非常简单的空闲挂钩函数](ch04.md#list4.19)
+ [清单 4.20 示例任务的源代码现在打印出 ulIdleCycleCount 值](ch04.md#list4.20)
+ [清单 4.21 vTaskPrioritySet() API 函数原型](ch04.md#list4.21)
+ [清单 4.22 uxTaskPriorityGet() API 函数原型](ch04.md#list4.22)
+ [清单 4.23 示例 4.8 中任务 1 的实现](ch04.md#list4.23)
+ [清单 4.24 示例 4.8 中任务 2 的实现](ch04.md#list4.24)
+ [清单 4.25 示例 4.8 中 main() 的实现](ch04.md#list4.25)
+ [清单 4.26 vTaskDelete() API 函数原型](ch04.md#list4.26)
+ [清单 4.27 示例 4.9 中 main() 的实现](ch04.md#list4.27)
+ [清单 4.28 示例 4.9 中任务 1 的实现](ch04.md#list4.28)
+ [清单 4.29 示例 4.9 中任务 2 的实现](ch04.md#list4.29)
+ [清单 4.30 线程局部存储指针 API 函数的原型](ch04.md#list4.30)
+ [清单 5.1 xQueueCreate() API 函数原型](ch05.md#list5.1)
+ [清单 5.2 xQueueSendToFront() API 函数原型](ch05.md#list5.2)
+ [清单 5.3 xQueueSendToBack() API 函数原型](ch05.md#list5.3)
+ [清单 5.4 xQueueReceive() API 函数原型](ch05.md#list5.4)
+ [清单 5.5 uxQueueMessagesWaiting() API 函数原型](ch05.md#list5.5)
+ [清单 5.6 示例 5.1 中使用的发送任务的实现](ch05.md#list5.6)
+ [清单 5.7 示例 5.1 的接收任务的实现](ch05.md#list5.7)
+ [清单 5.8 示例 5.1 中 main() 的实现](ch05.md#list5.8)
+ [清单 5.9 要在队列中传递的结构的定义，以及示例中使用的两个变量的声明](ch05.md#list5.9)
+ [清单 5.10 示例 5.2 中使用的发送任务的实现](ch05.md#list5.10)
+ [清单 5.11 示例 5.2 的接收任务的定义](ch05.md#list5.11)
+ [清单 5.12 示例 5.2 中 main() 的实现](ch05.md#list5.12)
+ [清单 5.13 创建一个包含指针的队列](ch05.md#list5.13)
+ [清单 5.14 使用队列发送指向缓冲区的指针](ch05.md#list5.14)
+ [清单 5.15 使用队列接收指向缓冲区的指针](ch05.md#list5.15)
+ [清单 5.16 在 FreeRTOS+TCP 中用于将事件发送到 TCP/IP 任务的结构](ch05.md#list5.16)
+ [清单 5.17 伪代码，显示如何使用 IPStackEvent_t 结构将从网络接收到的数据发送到 TCP/IP 任务](ch05.md#list5.17)
+ [清单 5.18 伪代码，显示如何使用 IPStackEvent_t 结构将接受连接的套接字句柄发送到 TCP/IP 任务](ch05.md#list5.18)
+ [清单 5.19 伪代码，显示如何使用 IPStackEvent_t 结构将网络关闭事件发送到 TCP/IP 任务](ch05.md#list5.19)
+ [清单 5.20 伪代码，显示如何接收和处理 IPStackEvent_t 结构](ch05.md#list5.20)
+ [清单 5.21 xQueueCreateSet() API 函数原型](ch05.md#list5.21)
+ [清单 5.22 xQueueAddToSet() API 函数原型](ch05.md#list5.22)
+ [清单 5.23 xQueueSelectFromSet() API 函数原型](ch05.md#list5.23)
+ [清单 5.24 示例 5.3 中 main() 的实现](ch05.md#list5.24)
+ [清单 5.25 示例 5.3 中使用的发送任务](ch05.md#list5.25)
+ [清单 5.26 示例 5.3 中使用的接收任务](ch05.md#list5.26)
+ [清单 5.27 使用包含队列和信号量的队列集](ch05.md#list5.27)
+ [清单 5.28 将队列创建为邮箱使用](ch05.md#list5.28)
+ [清单 5.29 xQueueOverwrite() API 函数原型](ch05.md#list5.29)
+ [清单 5.30 使用 xQueueOverwrite() API 函数](ch05.md#list5.30)
+ [清单 5.31 xQueuePeek() API 函数原型](ch05.md#list5.31)
+ [清单 5.32 使用 xQueuePeek() API 函数](ch05.md#list5.32)
+ [清单 6.1 软件定时器回调函数原型](ch06.md#list)
+ [清单 6.2 xTimerDelete() API 函数原型](ch06.md#list6.2)
+ [清单 6.3 xTimerCreate() API 函数原型](ch06.md#list6.3)
+ [清单 6.4 xTimerStart() API 函数原型](ch06.md#list6.4)
+ [清单 6.5 创建和启动示例 6.1 中使用的定时器](ch06.md#list6.5)
+ [清单 6.6 示例 6.1 中单次定时器使用的回调函数](ch06.md#list6.5)
+ [清单 6.7 示例 6.1 中自动重载定时器使用的回调函数](ch06.md#list6.7)
+ [清单 6.8 vTimerSetTimerID() API 函数原型](ch06.md#list6.8)
+ [清单 6.9 pvTimerGetTimerID() API 函数原型](ch06.md#list6.9)
+ [清单 6.10 创建示例 6.2 中使用的定时器](ch06.md#list6.10)
+ [清单 6.11 示例 6.2 中使用的定时器回调函数](ch06.md#list6.11)
+ [清单 6.12 xTimerChangePeriod() API 函数原型](ch06.md#list6.12)
+ [清单 6.13 使用 xTimerChangePeriod()](ch06.md#list6.13)
+ [清单 6.14 xTimerReset() API 函数原型](ch06.md#list6.14)
+ [清单 6.15 示例 6.3 中单次定时器的回调函数](ch06.md#list6.15)
+ [清单 6.16 示例 6.3 中用于重置软件定时器的任务](ch06.md#list6.16)
+ [清单 7.1 portEND_SWITCHING_ISR() 宏](ch07.md#list7.1)
+ [清单 7.2 portYIELD_FROM_ISR() 宏](ch07.md#list7.2)
+ [清单 7.3 xSemaphoreCreateBinary() API 函数原型](ch07.md#list7.3)
+ [清单 7.4 xSemaphoreTake() API 函数原型](ch07.md#list7.4)
+ [清单 7.5 xSemaphoreGiveFromISR() API 函数原型](ch07.md#list)
+ [清单 7.6 在示例 7.1 中定期生成软件中断的任务的实现](ch07.md#list7.6)
+ [清单 7.7 将中断处理推迟到中断处理任务的实现（该任务...](ch07.md#list7.7.)
+ [清单 7.8 示例 7.1 中使用的软件中断的 ISR](ch07.md#list7.8)
+ [清单 7.9 示例 7.1 中 main() 的实现](ch07.md#list7.9)
+ [清单 7.10 使用 UART 接收，推荐的推迟中断处理任务的结构](ch07.md#list7.10)
+ [清单 7.11 xSemaphoreCreateCounting() API 函数原型](ch07.md#list7.11)
+ [清单 7.12 用于在示例 7.2 中创建计数信号量的 xSemaphoreCreateCounting() 的调用](ch07.md#list7.12)
+ [清单 7.13 示例 7.2 中使用的中断服务例程的实现](ch07.md#list7.13)
+ [清单 7.14 xTimerPendFunctionCallFromISR() API 函数原型](ch07.md#list7.14)
+ [清单 7.15 xTimerPendFunctionCallFromISR() 中 xFunctionToPend 参数传递的函数的原型](ch07.md#list7.15)
+ [清单 7.16 示例 7.3 中使用的软件中断处理程序](ch07.md#list7.16)
+ [清单 7.17 在示例 7.3 中中断所必需的处理执行的函数](ch07.md#list7.17)
+ [清单 7.18 示例 7.3 中 main() 的实现](ch07.md#list7.18)
+ [清单 7.19 xQueueSendToFrontFromISR() API 函数原型](ch07.md#list7.19)
+ [清单 7.20 xQueueSendToBackFromISR() API 函数原型](ch07.md#list7.20)
+ [清单 7.21 在示例 7.4 中写入队列的任务的实现](ch07.md#list7.21)
+ [清单 7.22 示例 7.4 中使用的中断服务例程的实现](ch07.md#list7.22)
+ [清单 7.23 从中断服务例程接收字符串并在示例 7.4 中打印的任务](ch07.md#list7.23)
+ [清单 7.24 示例 7.4 的 main() 函数](ch07.md#list7.24)
+ [清单 8.1 读、改、写序列示例](ch08.md#list8.1)
+ [清单 8.2 重入函数示例](ch08.md#list8.2)
+ [清单 8.3 非重入函数示例](ch08.md#list8.3)
+ [清单 8.4 使用临界区来保护对寄存器的访问](ch08.md#list8.4)
+ [清单 8.5 vPrintString() 的可能实现](ch08.md#list8.5)
+ [清单 8.6 在中断服务例程中使用临界区](ch08.md#list8.6)
+ [清单 8.7 vTaskSuspendAll() API 函数原型](ch08.md#list8.7)
+ [清单 8.8 xTaskResumeAll() API 函数原型](ch08.md#list8.8)
+ [清单 8.9 vPrintString() 的实现](ch08.md#list8.9)
+ [清单 8.10 xSemaphoreCreateMutex() API 函数原型](ch08.md#list8.10)
+ [清单 8.11 prvNewPrintString() 的实现](ch08.md#list8.11)
+ [清单 8.12 示例 8.1 中 prvPrintTask() 的实现](ch08.md#list8.12)
+ [清单 8.13 示例 8.1 中 main() 的实现](ch08.md#list8.13)
+ [清单 8.14 创建和使用递归互斥锁](ch08.md#list8.14)
+ [清单 8.15 在紧循环中使用互斥锁的任务](ch08.md#list8.15)
+ [清单 8.16 确保在循环中使用互斥锁的任务获得更公平的处理时间...](ch08.md#list8.16)
+ [清单 8.17 滴答钩子函数的名称和原型](ch08.md#list8.17)
+ [清单 8.18 守门员任务](ch08.md#list8.18)
+ [清单 8.19 示例 8.2 中打印任务的实现](ch08.md#list8.19)
+ [清单 8.20 滴答钩子的实现](ch08.md#list8.20)
+ [清单 8.21 示例 8.2 中 main() 的实现](ch08.md#list8.21)
+ [清单 9.1 xEventGroupCreate() API 函数原型](ch09.md#list9.1)
+ [清单 9.2. xEventGroupSetBits() API 函数原型](ch09.md#list9.2)
+ [清单 9.3 xEventGroupSetBitsFromISR() API 函数原型](ch09.md#list9.3)
+ [清单 9.4 xEventGroupWaitBits() API 函数原型](ch09.md#list9.4)
+ [清单 9.5 xEventGroupGetStaticBuffer() API 函数原型](ch09.md#list9.5)
+ [清单 9.6 示例 9.1 中使用的事件位定义](ch09.md#list9.6)
+ [清单 9.7 在示例 9.1 中设置事件组中两个位的任务](ch09.md#list9.7)
+ [清单 9.8 在示例 9.1 中设置事件组中第 2 位的中断服务例程](ch09.md#list9.8)
+ [清单 9.9 在示例 9.1 中阻塞以等待事件位变为设置的任务](ch09.md#list9.9)
+ [清单 9.10 在示例 9.1 中创建事件组和任务](ch09.md#list9.10)
+ [清单 9.11 两个任务相互同步以确保共享 TCP 端口的伪代码...](ch09.md#list9.11)
+ [清单 9.12 xEventGroupSync() API 函数原型](ch09.md#list9.12)
+ [清单 9.13 示例 9.2 中使用的任务的实现](ch09.md#list9.13)
+ [清单 9.14 示例 9.2 中使用的 main() 函数](ch09.md#list9.14)
+ [清单 10.1 xTaskNotifyGive() API 函数原型](ch10.md#list10.1)
+ [清单 10.2 vTaskNotifyGiveFromISR() API 函数原型](ch10.md#list10.2)
+ [清单 10.3 ulTaskNotifyTake() API 函数原型](ch10.md#list10.3)
+ [清单 10.4 将中断处理推迟到中断处理任务的实现（该任务...](ch10.md#list10.4)
+ [清单 10.5 示例 10.1 中使用的中断服务例程的实现](ch10.md#list10.5)
+ [清单 10.6 将中断处理推迟到中断处理任务的实现（该任务...](ch10.md#list10.6)
+ [清单 10.7 示例 10.2 中使用的中断服务例程的实现](ch10.md#list10.7)
+ [清单 10.8 xTaskNotify() 和 xTaskNotifyFromISR() API 函数的原型](ch10.md#list10.8)
+ [清单 10.9 xTaskNotifyWait() API 函数原型](ch10.md#list10.9)
+ [清单 10.10 伪代码演示如何使用二进制信号量在驱动程序库传输中...](ch10.md#list10.10)
+ [清单 10.11 伪代码演示如何使用任务通知在驱动程序库传输中...](ch10.md#list10.11)
+ [清单 10.12 伪代码演示如何使用任务通知在驱动程序库接收中...](ch10.md#list10.12)
+ [清单 10.13 伪代码演示如何使用任务通知将值传递给任务](ch10.md#list10.13)
+ [清单 10.14 发送到服务器任务的队列结构和数据类型](ch10.md#list10.14)
+ [清单 10.15 云读取 API 函数的实现](ch10.md#list10.15)
+ [清单 10.16 服务器任务处理读取请求](ch10.md#list10.16)
+ [清单 10.17 云写入 API 函数的实现](ch10.md#list10.17)
+ [清单 10.18 服务器任务处理发送请求](ch10.md#list10.18)
+ [清单 11.1 portSUPPRESS_TICKS_AND_SLEEP 宏的原型](ch11.md#list11.1)
+ [清单 11.2 vPortSuppressTicksAndSleep API 函数原型](ch11.md#list11.2)
+ [清单 11.3 eTaskConfirmSleepModeStatus API 函数原型](ch11.md#list11.3)
+ [清单 11.4 configPRE_SLEEP_PROCESSING 宏的原型](ch11.md#list11.4)
+ [清单 11.5 configPOST_SLEEP_PROCESSING 宏的原型](ch11.md#list11.5)
+ [清单 11.6 portSUPPRESS_TICKS_AND_SLEEP() 用户自定义实现的示例](ch11.md#list11.6)
+ [清单 11.7 vApplicationIdleHook API 函数原型](ch11.md#list11.7)
+ [清单 12.1 使用标准的 C assert() 宏来检查 pxMyPointer 是否为 NULL](ch12.md#list12.1)
+ [清单 12.2 在调试器控制下执行时有用的简单 configASSERT() 定义](ch12.md#list12.2)
+ [清单 12.3 configASSERT() 定义，记录断言失败的源代码行](ch12.md#list12.3)
+ [清单 12.4 uxTaskGetSystemState() API 函数原型](ch12.md#list12.4)
+ [清单 12.5 TaskStatus_t 结构](ch12.md#list12.5)
+ [清单 12.6 vTaskListTasks() API 函数原型](ch12.md#list12.6)
+ [清单 12.7 vTaskList() API 函数原型](ch12.md#list12.7)
+ [清单 12.8 vTaskGetRunTimeStatistics() API 函数原型](ch12.md#list12.8)
+ [清单 12.9 vTaskGetRunTimeStats() API 函数原型](ch12.md#list12.9)
+ [清单 12.10 用于计算定时器溢出的 16 位定时器溢出中断处理程序](ch12.md#list12.10)
+ [清单 12.11 添加到 FreeRTOSConfig.h 以启用运行时统计信息收集的宏](ch12.md#list12.11)
+ [清单 12.12 打印收集的运行时统计信息的任务](ch12.md#list12.12)
+ [清单 13.1 uxTaskGetStackHighWaterMark() API 函数原型](ch13.md#list13.1)
+ [清单 13.2 uxTaskGetStackHighWaterMark2() API 函数原型](ch13.md#list13.2)
+ [清单 13.3 堆栈溢出挂钩函数原型](ch13.md#list13.3)


## 表格：
+ [表 1 需要在项目中包含的 FreeRTOS 源代码文件](ch02.md#tbl1)
+ [表 2 TickType_t 数据类型和 configTICK_TYPE_WIDTH_IN_BITS 配置](ch02.md#tbl2)
+ [表 3 宏前缀](ch02.md#tbl3)
+ [表 4 常用宏定义](ch02.md#tbl4)
+ [表 5 用于配置内核调度算法的 FreeRTOSConfig.h 设置](ch04.md#tbl5)
+ [表 6 uxBitsToWaitFor 和 xWaitForAllBits 参数的影响](ch09.md#tbl6)

