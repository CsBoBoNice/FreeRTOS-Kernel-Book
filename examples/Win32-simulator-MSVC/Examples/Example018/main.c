/*
 *  版权所有 Amazon.com Inc. 或其附属公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 * 
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是 FreeRTOS 发行版的一部分。
 * 
 *  本文件包含《掌握 FreeRTOS 实时内核》一书中列出的示例的 Windows 端口实现。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

/* 演示所需的包含文件 */
#include "supporting_functions.h"


/* 本示例中使用的模拟中断的编号。编号 0 到 2 
 * 由 FreeRTOS Windows 端口本身使用，因此 3 是应用程序可用的第一个编号。 */
#define mainINTERRUPT_NUMBER    3

/* 要创建的任务 */
static void vPeriodicTask(void *pvParameters);

/* 执行延迟中断处理的函数。该函数
 * 在守护任务的上下文中执行。 */
static void vDeferredHandlingFunction(void *pvParameter1,
                                      uint32_t ulParameter2);

/* 模拟中断的服务例程。这是任务将与之
 * 同步的中断。 */
static uint32_t ulExampleInterruptHandler(void);

/*-----------------------------------------------------------*/

int main(void)
{
/* 生成软件中断的任务创建时使用的优先级
 * 低于守护任务的优先级。守护任务的优先级
 * 由 FreeRTOSConfig.h 中的 configTIMER_TASK_PRIORITY 编译时配置常量设置。 */
    const UBaseType_t ulPeriodicTaskPriority = configTIMER_TASK_PRIORITY - 1;

    /* 创建将周期性生成软件中断的任务 */
    xTaskCreate(vPeriodicTask, "Periodic", 1000, NULL, ulPeriodicTaskPriority, NULL);

    /* 为软件中断安装处理程序。执行此操作所需的语法
     * 取决于所使用的 FreeRTOS 端口。这里显示的语法
     * 只能与 FreeRTOS Windows 端口一起使用，因为在 Windows 端口中
     * 这种中断只是模拟的。 */
    vPortSetInterruptHandler(mainINTERRUPT_NUMBER, ulExampleInterruptHandler);

    /* 启动调度程序，使创建的任务开始执行 */
    vTaskStartScheduler();

    /* 下面的代码永远不应该被执行，因为 vTaskStartScheduler()
    * 只有在 FreeRTOS 堆内存不足以创建空闲任务和
    * 定时器任务（如果配置了的话）时才会返回。堆管理和
    * 捕获堆耗尽的技术在书中有详细描述。 */
    for(;;)
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

static void vPeriodicTask(void *pvParameters)
{
    const TickType_t xDelay500ms = pdMS_TO_TICKS(500UL); /* 将500毫秒转换为系统节拍数 */

    /* 与大多数任务一样，此任务在无限循环内实现 */
    for(;;)
    {
        /* 此任务仅用于"模拟"中断。这是通过
         * 周期性生成模拟软件中断来实现的。阻塞等待直到
         * 到再次生成软件中断的时间。 */
        vTaskDelay(xDelay500ms);

        /* 生成中断，在生成中断前后打印消息，
         * 以便从输出中可以看出执行顺序。
         *
         * 用于生成软件中断的语法取决于
         * 所使用的 FreeRTOS 端口。下面使用的语法只能用于
         * FreeRTOS Windows 端口，在该端口中这些中断只是
         * 模拟的。 */
        vPrintString("周期性任务 - 即将生成中断。\r\n");
        vPortGenerateSimulatedInterrupt(mainINTERRUPT_NUMBER);
        vPrintString("周期性任务 - 中断已生成。\r\n\r\n\r\n");
    }
}
/*-----------------------------------------------------------*/

static uint32_t ulExampleInterruptHandler(void)
{
    static uint32_t ulParameterValue = 0;
    BaseType_t xHigherPriorityTaskWoken;

    /* xHigherPriorityTaskWoken 参数必须初始化为 pdFALSE，
     * 因为如果在中断安全的 API 函数内需要进行上下文切换，
     * 它将被设置为 pdTRUE。 */
    xHigherPriorityTaskWoken = pdFALSE;

    /* 将指向中断延迟处理函数的指针发送到
     * 守护任务。延迟处理函数的 pvParameter1 参数未使用，
     * 因此只需设置为 NULL。延迟处理函数的 ulParameter2
     * 参数用于传递每次发生此中断时递增的数字。 */
    xTimerPendFunctionCallFromISR(vDeferredHandlingFunction, NULL, ulParameterValue, &xHigherPriorityTaskWoken);
    ulParameterValue++;

    /* 将 xHigherPriorityTaskWoken 值传递给 portYIELD_FROM_ISR()。如果
     * xHigherPriorityTaskWoken 在 xTimerPendFunctionCallFromISR() 内部被设置为 pdTRUE，
     * 则调用 portYIELD_FROM_ISR() 将请求上下文切换。如果 xHigherPriorityTaskWoken 仍为 pdFALSE，
     * 则调用 portYIELD_FROM_ISR() 不会产生任何影响。Windows 端口使用的
     * portYIELD_FROM_ISR() 实现包含一个 return 语句，
     * 这就是为什么此函数不显式返回值的原因。 */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}
/*-----------------------------------------------------------*/

static void vDeferredHandlingFunction(void *pvParameter1,
                                      uint32_t ulParameter2)
{
    /* 通过将 pvParameter1 声明为未使用来消除编译器警告，
     * 因为在此示例中未使用 pvParameter1。 */
    (void)pvParameter1;

    /* 处理事件 - 在这种情况下，只需打印出一条消息和
     * ulParameter2 的值。 */
    vPrintStringAndNumber("处理函数 - 正在处理事件 ", ulParameter2);
}
