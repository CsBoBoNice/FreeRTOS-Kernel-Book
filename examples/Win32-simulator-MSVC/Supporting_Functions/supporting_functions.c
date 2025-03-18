/*
    FreeRTOS V9.0.0 - 版权所有 (C) 2016 Real Time Engineers Ltd.
    保留所有权利

    访问 http://www.FreeRTOS.org 确保您使用的是最新版本。

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS提供完全免费且专业开发的、健壮的、严格质量控制的、        *
     *    支持多平台的软件，已成为事实上的标准。                            *
     *                                                                       *
     *    通过购买FreeRTOS教程书籍、参考手册或两者来帮助自己快速入门        *
     *    并支持FreeRTOS项目：http://www.FreeRTOS.org/Documentation         *
     *                                                                       *
     *    感谢您的支持！                                                     *
     *                                                                       *
    ***************************************************************************

    本文件是FreeRTOS发行版的一部分。

    FreeRTOS是自由软件；您可以根据GNU通用公共许可证（第2版）的条款重新分发
    和/或修改它，该许可证由自由软件基金会发布，并由FreeRTOS例外条款修改。

    >>! 注意：对GPL的修改是为了允许您分发包含FreeRTOS的组合工作，而无需提供
    >>! FreeRTOS内核之外的专有组件的源代码。

    FreeRTOS的分发希望它会有用，但不提供任何保证；甚至没有对适销性或特定
    用途适用性的暗示保证。完整的许可证文本可从以下链接获得：
    http://www.freertos.org/a00114.html

    1个制表符 == 4个空格！

    ***************************************************************************
     *                                                                       *
     *    遇到问题？从阅读FAQ"我的应用程序无法运行，可能出了什么问题？"     *
     *    开始。                                                             *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - 文档、书籍、培训、最新版本、许可证和
    Real Time Engineers Ltd.联系详情。

    http://www.FreeRTOS.org/plus - FreeRTOS生态系统产品的选择，
    包括FreeRTOS+Trace - 不可或缺的生产力工具、DOS兼容的FAT文件系统
    和我们的小型线程感知UDP/IP协议栈。

    http://www.OpenRTOS.com - Real Time Engineers ltd将FreeRTOS授权给
    High Integrity Systems，以OpenRTOS品牌销售。低成本OpenRTOS许可证
    提供有担保的支持、赔偿和中间件。

    http://www.SafeRTOS.com - High Integrity Systems还提供一个安全工程
    和独立SIL3认证的版本，用于需要可证明可靠性的安全和任务关键型应用程序。

    1个制表符 == 4个空格！
*/

/*
 * 本文件包含一些所有示例都使用的支持函数。这些函数分为三类：
 *
 * 1) 输入/输出函数：vPrintString()和vPrintStringAndNumber()。
 *
 * 为了允许最大的可移植性，书中的示例不依赖于任何特定芯片的IO，
 * 而是只输出到控制台。然而，以这种方式打印到控制台不是线程安全的，
 * 所以使用函数将终端输出包装在临界区内，确保输出的完整性。
 *
 * 2) RTOS钩子函数：vApplicationMallocFailedHook()、vApplicationIdleHook()、
 * vApplicationStackOverflowHook()和vApplicationTickHook()。
 *
 * 这些是应用程序开发者可以选择定义的函数，以便在应用程序执行过程中
 * 获得事件通知。更多信息在本文件中的函数定义注释和书中的文本中提供。
 * 钩子函数允许用户代码在特定的RTOS事件发生时执行，如内存分配失败、
 * 空闲任务运行、堆栈溢出检测和每个系统节拍。
 *
 * 3) configASSERT()实现：vAssertCalled()
 *
 * FreeRTOS源代码使用assert()函数来捕获用户和其他错误。configASSERT()
 * 在FreeRTOSConfig.h中定义为调用vAssertCalled()，后者在本文件中实现。
 * 这是一种调试机制，用于捕获和定位运行时错误。
 */

/* 标准包含文件 */
#include <stdio.h>
#include <conio.h>

/* FreeRTOS包含文件 */
#include "FreeRTOS.h"
#include "task.h"

/* 如果此变量为true，则按键将结束应用程序。
   一些示例将此设置为pdFALSE，以允许应用程序使用按键。 */
BaseType_t xKeyPressesStopApplication = pdTRUE;

/*-----------------------------------------------------------*/

void vPrintString( const char *pcString )
{
BaseType_t xKeyHit = pdFALSE;

	/* 打印字符串，使用临界区作为互斥的简单方法。
	   这确保了在多任务环境中输出不会被中断或混乱。 */
	taskENTER_CRITICAL();
	{
		printf( "%s", pcString );
		fflush( stdout );  /* 刷新输出缓冲区，确保文本立即显示 */

		/* 允许任何键停止应用程序 */
		if( xKeyPressesStopApplication == pdTRUE )
		{
			xKeyHit = _kbhit();  /* 检查是否有键被按下 */
		}
	}
	taskEXIT_CRITICAL();

    /* 允许任何键停止应用程序运行。
       实际使用按键值的真实应用程序也应该保护对键盘的访问。 */
	if( xKeyHit != pdFALSE )
	{
		vTaskEndScheduler();  /* 停止RTOS调度器 */
	}
}
/*-----------------------------------------------------------*/

void vPrintStringAndNumber( const char *pcString, uint32_t ulValue )
{
	/* 打印字符串和数值，使用临界区作为互斥的简单方法 */
	taskENTER_CRITICAL();
	{
		printf( "%s %lu\r\n", pcString, ulValue );
		fflush( stdout );
	}
	taskEXIT_CRITICAL();

	/* 允许任何键停止应用程序运行 */
	if( xKeyPressesStopApplication == pdTRUE )
	{
		if( _kbhit() )
		{
			vTaskEndScheduler();
		}
	}
}
/*-----------------------------------------------------------*/

void vPrintTwoStrings( const char *pcString1, const char *pcString2 )
{
	/* 打印两个字符串，使用任务挂起作为互斥方法
       与临界区不同，这会暂停所有任务的调度 */
	vTaskSuspendAll();
	{
		printf( "当前时间 %lu: %s %s\r\n", xTaskGetTickCount(), pcString1, pcString2 );
	}
	xTaskResumeAll();

	/* 允许任何键停止应用程序运行 */
	if( xKeyPressesStopApplication == pdTRUE )
	{
		if( _kbhit() )
		{
			vTaskEndScheduler();
		}
	}
}
/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* 只有当FreeRTOSConfig.h中configUSE_MALLOC_FAILED_HOOK设置为1时，
	   vApplicationMallocFailedHook()才会被调用。这是一个钩子函数，
	   当调用pvPortMalloc()失败时会被调用。
	   
	   当内核创建任务、队列、定时器、事件组或信号量时，pvPortMalloc()会在内部被调用。
	   示例应用程序的各个部分也会调用它。如果使用heap_1.c、heap_2.c或heap_4.c，
	   则pvPortMalloc()可用的堆大小由FreeRTOSConfig.h中的configTOTAL_HEAP_SIZE定义，
	   并且可以使用xPortGetFreeHeapSize() API函数查询剩余的空闲堆空间大小。 */
	vAssertCalled( __LINE__, __FILE__ );
}
/*-----------------------------------------------------------*/

/* 此处包含一个vApplicationIdleHook()示例实现，以求完整性，
   但实际上并未构建（它由#if 0排除），因为它也由实际使用该函数的示例定义。 */
#if 0
	void vApplicationIdleHook( void )
	{
		/* 只有当FreeRTOSConfig.h中configUSE_IDLE_HOOK设置为1时，
		   vApplicationIdleHook()才会被调用。它将在空闲任务的每次迭代时被调用。
		   
		   重要的是添加到此钩子函数的代码不得以任何方式尝试阻塞
		   （例如，指定了阻塞时间的xQueueReceive()调用，或vTaskDelay()调用）。
		   
		   如果应用程序使用vTaskDelete() API函数，那么允许vApplicationIdleHook()
		   返回到其调用函数也很重要，因为空闲任务负责清理内核分配给已删除任务的内存。 */
	}
#endif /* 0 */
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* 如果configCHECK_FOR_STACK_OVERFLOW定义为1或2，则执行运行时堆栈溢出检查。
	   当检测到堆栈溢出时，会调用此钩子函数。
	   这个函数允许开发者在堆栈溢出情况发生时采取适当的措施，如记录错误或重启系统。 */
	vAssertCalled( __LINE__, __FILE__ );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* 如果FreeRTOSConfig.h中configUSE_TICK_HOOK设置为1，则每个节拍中断都会调用此函数。
	   用户代码可以在此处添加，但节拍钩子是从中断上下文调用的，
	   因此代码不得尝试阻塞，并且只能使用中断安全的FreeRTOS API函数
	   （那些以FromISR()结尾的函数）。 
	   
	   这个钩子对于需要精确定时或周期性执行的短任务非常有用，如LED闪烁或
	   其他需要与系统节拍同步的操作。 */
}
/*-----------------------------------------------------------*/

void vAssertCalled( uint32_t ulLine, const char * const pcFile )
{
/* 以下两个变量仅用于确保参数不会被优化掉，
   因此在调试器中查看时可用。 */
volatile uint32_t ulLineNumber = ulLine, ulSetNonZeroInDebuggerToReturn = 0;
volatile const char * const pcFileName = pcFile;

	taskENTER_CRITICAL();
	{
		while( ulSetNonZeroInDebuggerToReturn == 0 )
		{
			/* 如果您希望在调试器中跳出此函数以查看assert()位置，
			   请将ulSetNonZeroInDebuggerToReturn设置为非零值。
			   这是一个无限循环，用于在断言失败时暂停程序执行，
			   便于调试人员检查失败原因。 */
		}
	}
	taskEXIT_CRITICAL();

	/* 移除设置但随后未引用变量可能导致的编译器警告。 */
	( void ) pcFileName;
	( void ) ulLineNumber;
}
/*-----------------------------------------------------------*/

