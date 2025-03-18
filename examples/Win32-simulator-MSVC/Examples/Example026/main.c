/*
 *  版权所有 Amazon.com Inc. 或其关联公司。保留所有权利。
 *
 *  SPDX-License-Identifier: MIT-0
 *
 *  访问 http://www.FreeRTOS.org 确保您使用的是最新版本。
 *
 *  本文件是FreeRTOS发行版的一部分。
 *
 *  本文件包含在FreeRTOS书籍《掌握FreeRTOS实时内核》中列出的示例的Windows端口实现。
 *
 */

/* FreeRTOS.org 包含文件 */
#include "FreeRTOS.h"
#include "task.h"

/* 演示包含文件 */
#include "supporting_functions.h"

/* 定义常量，用于内存跟踪功能 */
#define mainNUM_ALLOCATED_BLOCKS            5    /* 每个任务分配的内存块数量 */
#define mainNUM_ALLOCATION_ENTRIES          512  /* 最大内存分配记录条目数 */
#define mainNUM_PER_TASK_ALLOCATION_ENTRIES 32   /* 每个任务的最大内存分配记录条目数 */

/*-----------------------------------------------------------*/

/*
 * 分配条目结构，用于跟踪每个内存分配
 * +-----------------+--------------+----------------+-------------------+
 * | 分配任务        | 条目使用中   | 分配大小       | 分配指针          |
 * +-----------------+--------------+----------------+-------------------+
 * |                 |              |                |                   |
 * +-----------------+--------------+----------------+-------------------+
 * |                 |              |                |                   |
 * +-----------------+--------------+----------------+-------------------+
 */
typedef struct AllocationEntry
{
    BaseType_t xInUse;                /* 条目是否正在使用 */
    TaskHandle_t xAllocatingTaskHandle; /* 分配内存的任务句柄 */
    size_t uxAllocatedSize;           /* 分配的内存大小 */
    void * pvAllocatedPointer;        /* 分配的内存指针 */
} AllocationEntry_t;

/* 内存分配记录数组 */
AllocationEntry_t xAllocationEntries[ mainNUM_ALLOCATION_ENTRIES ];

/*
 * 每个任务的内存使用记录结构
 * +------+-----------------------+----------------------+
 * | 任务 | 当前持有内存          | 曾经持有最大内存     |
 * +------+-----------------------+----------------------+
 * |      |                       |                      |
 * +------+-----------------------+----------------------+
 * |      |                       |                      |
 * +------+-----------------------+----------------------+
 */
typedef struct PerTaskAllocationEntry
{
    TaskHandle_t xTask;               /* 任务句柄 */
    size_t uxMemoryCurrentlyHeld;     /* 任务当前持有的内存量 */
    size_t uxMaxMemoryEverHeld;       /* 任务曾经持有的最大内存量 */
} PerTaskAllocationEntry_t;

/* 每个任务的内存使用记录数组 */
PerTaskAllocationEntry_t xPerTaskAllocationEntries[ mainNUM_PER_TASK_ALLOCATION_ENTRIES ];

/*-----------------------------------------------------------*/

/* 要创建的任务。分配器任务创建两个实例，而报告任务只创建一个实例。 */
static void vAllocatorTask( void * pvParameters );  /* 内存分配任务 */
static void vReporterTask( void * pvParameters );   /* 内存使用报告任务 */

/*-----------------------------------------------------------*/

int main( void )
{
    /* 创建两个分配器任务实例，用于分配和释放内存 */
    xTaskCreate( vAllocatorTask, "Allocator1", 1000, NULL, 2, NULL );
    xTaskCreate( vAllocatorTask, "Allocator2", 1000, NULL, 2, NULL );
    
    /* 创建一个报告任务，用于显示每个任务的内存使用情况 */
    xTaskCreate( vReporterTask, "Reporter", 1000, NULL, 3, NULL );

    /* 启动调度器，使创建的任务开始执行 */
    vTaskStartScheduler();

    /* 以下代码行应该永远不会被执行，因为vTaskStartScheduler()
     * 只有在没有足够的FreeRTOS堆内存可用于创建空闲任务和
     * （如果配置了）定时器任务时才会返回。堆管理和陷阱堆
     * 耗尽的技术在书中有描述。 */
    for( ; ; )
    {
    }

    return 0;
}
/*-----------------------------------------------------------*/

/**
 * 分配器任务实现
 * 该任务周期性地分配和释放内存块，用于演示内存跟踪功能
 */
static void vAllocatorTask( void * pvParameters )
{
    uint32_t ulIteration = 0;  /* 迭代计数器 */
    void * pvAllocatedBlocks[ mainNUM_ALLOCATED_BLOCKS ];  /* 存储分配的内存块指针的数组 */

    /* 防止编译器警告，参数未使用 */
    ( void ) pvParameters;

    /* 无限循环 */
    for( ;; )
    {
        /* 如果迭代次数小于分配块数，则分配新内存 */
        if( ulIteration < mainNUM_ALLOCATED_BLOCKS )
        {
            pvAllocatedBlocks[ ulIteration ] = pvPortMalloc( 32 );  /* 分配32字节内存 */
        }
        else
        {
            /* 否则释放之前分配的内存块 */
            vPortFree( pvAllocatedBlocks[ ulIteration - mainNUM_ALLOCATED_BLOCKS ] );
        }

        /* 当迭代次数达到两倍分配块数减1时，重置计数器 */
        if( ulIteration == ( 2 * mainNUM_ALLOCATED_BLOCKS - 1 ) )
        {
            ulIteration = 0;
        }
        else
        {
            ulIteration++;
        }

        /* 延时1秒 */
        vTaskDelay( pdMS_TO_TICKS( 1000 ) );
    }
}
/*-----------------------------------------------------------*/

/**
 * 报告任务实现
 * 该任务定期报告每个任务的内存使用情况
 */
static void vReporterTask( void * pvParameters )
{
    size_t i;  /* 循环计数器 */

    /* 防止编译器警告，参数未使用 */
    ( void ) pvParameters;

    /* 无限循环 */
    for( ;; )
    {
        /* 遍历每个任务的内存分配记录 */
        for( i = 0; i < mainNUM_PER_TASK_ALLOCATION_ENTRIES; i++ )
        {
            /* 如果该条目有效（任务不为NULL） */
            if( xPerTaskAllocationEntries[ i ].xTask != NULL )
            {
                /* 输出分隔线 */
                vPrintString( "-----------------------------------\r\n" );
                /* 输出任务名称 */
                vPrintTwoStrings( "任务名称: ", pcTaskGetName( xPerTaskAllocationEntries[ i ].xTask ) );
                /* 输出当前内存使用量 */
                vPrintStringAndNumber( "当前持有内存: ", xPerTaskAllocationEntries[ i ].uxMemoryCurrentlyHeld );
                /* 输出最大内存使用量 */
                vPrintStringAndNumber( "最大持有内存: ", xPerTaskAllocationEntries[ i ].uxMaxMemoryEverHeld );
                /* 输出分隔线 */
                vPrintString( "-----------------------------------\r\n" );
            }
        }

        /* 延时5秒 */
        vTaskDelay( pdMS_TO_TICKS( 5 * 1000 ) );
    }
}
/*-----------------------------------------------------------*/

/**
 * 内存分配跟踪函数
 * 当使用pvPortMalloc分配内存时，此函数被调用
 * 
 * @param uxAllocatedSize 分配的内存大小
 * @param pv 分配的内存指针
 */
void TracepvPortMalloc( size_t uxAllocatedSize, void * pv )
{
    size_t i;  /* 循环计数器 */
    TaskHandle_t xAllocatingTaskHandle;  /* 分配内存的任务句柄 */
    AllocationEntry_t * pxAllocationEntry = NULL;  /* 内存分配记录指针 */
    PerTaskAllocationEntry_t * pxPerTaskAllocationEntry = NULL;  /* 每任务内存记录指针 */

    /* 确保调度器已启动 */
    if( xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED )
    {
        /* 获取当前任务句柄 */
        xAllocatingTaskHandle = xTaskGetCurrentTaskHandle();

        /* 查找空闲的分配记录条目 */
        for( i = 0; i < mainNUM_ALLOCATION_ENTRIES; i++ )
        {
            if( xAllocationEntries[ i ].xInUse == pdFALSE )
            {
                pxAllocationEntry = &( xAllocationEntries[ i ] );
                break;
            }
        }

        /* 查找该任务的现有内存使用记录 */
        for( i = 0; i < mainNUM_PER_TASK_ALLOCATION_ENTRIES; i++ )
        {
            if( xPerTaskAllocationEntries[ i ].xTask == xAllocatingTaskHandle )
            {
                pxPerTaskAllocationEntry = &( xPerTaskAllocationEntries[ i ] );
                break;
            }
        }

        /* 如果没有找到该任务的记录，查找空闲槽位创建新记录 */
        if( pxPerTaskAllocationEntry == NULL )
        {
            for( i = 0; i < mainNUM_PER_TASK_ALLOCATION_ENTRIES; i++ )
            {
                if( xPerTaskAllocationEntries[ i ].xTask == NULL )
                {
                    pxPerTaskAllocationEntry = &( xPerTaskAllocationEntries[ i ] );
                    break;
                }
            }
        }

        /* 确保在两个表中都有空间 */
        configASSERT( pxAllocationEntry != NULL );
        configASSERT( pxPerTaskAllocationEntry != NULL );

        /* 更新分配记录 */
        pxAllocationEntry->xAllocatingTaskHandle = xAllocatingTaskHandle;
        pxAllocationEntry->xInUse = pdTRUE;
        pxAllocationEntry->uxAllocatedSize = uxAllocatedSize;
        pxAllocationEntry->pvAllocatedPointer = pv;

        /* 更新任务内存使用记录 */
        pxPerTaskAllocationEntry->xTask = xAllocatingTaskHandle;
        pxPerTaskAllocationEntry->uxMemoryCurrentlyHeld += uxAllocatedSize;
        
        /* 更新最大内存使用量（如需要） */
        if( pxPerTaskAllocationEntry->uxMaxMemoryEverHeld < pxPerTaskAllocationEntry->uxMemoryCurrentlyHeld )
        {
            pxPerTaskAllocationEntry->uxMaxMemoryEverHeld = pxPerTaskAllocationEntry->uxMemoryCurrentlyHeld;
        }
    }
}
/*-----------------------------------------------------------*/

/**
 * 内存释放跟踪函数
 * 当使用vPortFree释放内存时，此函数被调用
 * 
 * @param pv 要释放的内存指针
 */
void TracevPortFree( void * pv )
{
    size_t i;  /* 循环计数器 */
    AllocationEntry_t * pxAllocationEntry = NULL;  /* 内存分配记录指针 */
    PerTaskAllocationEntry_t * pxPerTaskAllocationEntry = NULL;  /* 每任务内存记录指针 */

    /* 查找对应的内存分配记录 */
    for( i = 0; i < mainNUM_ALLOCATION_ENTRIES; i++ )
    {
        if( ( xAllocationEntries[ i ].xInUse == pdTRUE ) &&
            ( xAllocationEntries[ i ].pvAllocatedPointer == pv ) )
        {
            pxAllocationEntry = &( xAllocationEntries [ i ] );
            break;
        }
    }

    /* 确保找到了之前分配的内存块记录 */
    configASSERT( pxAllocationEntry != NULL );

    /* 查找分配该内存的任务的记录 */
    for( i = 0; i < mainNUM_PER_TASK_ALLOCATION_ENTRIES; i++ )
    {
        if( xPerTaskAllocationEntries[ i ].xTask == pxAllocationEntry->xAllocatingTaskHandle )
        {
            pxPerTaskAllocationEntry = &( xPerTaskAllocationEntries[ i ] );
            break;
        }
    }

    /* 任务表中必须存在条目 */
    configASSERT( pxPerTaskAllocationEntry != NULL );

    /* 更新任务当前持有的内存量 */
    pxPerTaskAllocationEntry->uxMemoryCurrentlyHeld -= pxAllocationEntry->uxAllocatedSize;

    /* 清除分配记录 */
    pxAllocationEntry->xInUse = pdFALSE;
    pxAllocationEntry->xAllocatingTaskHandle = NULL;
    pxAllocationEntry->uxAllocatedSize = 0;
    pxAllocationEntry->pvAllocatedPointer = NULL;
}
/*-----------------------------------------------------------*/
