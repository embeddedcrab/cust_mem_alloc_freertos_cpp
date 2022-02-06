/*********************************************************************************************************************
 * @file     heap.h
 * @brief    Custom heap Header
 * @version  NA
 * @date     06/02/2022
 *
 */
/******************************************************************************
* Notes:
*
* Change History
* --------------
*
*******************************************************************************/
#ifndef _HEAP_H_
#define _HEAP_H_


#include <stdlib.h>
#include <stdint.h>


#define USE_HEAP_5


#define configASSERT( x ) if ((x) == 0) {for( ;; );}

#define portBYTE_ALIGNMENT      8
#define portBYTE_ALIGNMENT_MASK ( 0x0007 )

#define configTOTAL_HEAP_SIZE       ( (unsigned long) 10485760<<1 )

/* Block sizes must not get too small. */
#define heapMINIMUM_BLOCK_SIZE    ( ( size_t ) ( xHeapStructSize << 1 ) )

/* Assumes 8bit bytes! */
#define heapBITS_PER_BYTE         ( ( size_t ) 8 )

#define portMAX_DELAY ( uint32_t ) 0xffffffffUL


#ifdef USE_HEAP_5
/* Used by heap_5.c to define the start address and size of each memory region
 * that together comprise the total FreeRTOS heap space. */
typedef struct HeapRegion
{
    uint8_t * pucStartAddress;
    size_t xSizeInBytes;
} HeapRegion_t;
#endif

/* Used to pass information about the heap out of vPortGetHeapStats(). */
typedef struct xHeapStats
{
    size_t xAvailableHeapSpaceInBytes;      /* The total heap size currently available - this is the sum of all the free blocks, not the largest block that can be allocated. */
    size_t xSizeOfLargestFreeBlockInBytes;  /* The maximum size, in bytes, of all the free blocks within the heap at the time vPortGetHeapStats() is called. */
    size_t xSizeOfSmallestFreeBlockInBytes; /* The minimum size, in bytes, of all the free blocks within the heap at the time vPortGetHeapStats() is called. */
    size_t xNumberOfFreeBlocks;             /* The number of free memory blocks within the heap at the time vPortGetHeapStats() is called. */
    size_t xMinimumEverFreeBytesRemaining;  /* The minimum amount of total free memory (sum of all free blocks) there has been in the heap since the system booted. */
    size_t xNumberOfSuccessfulAllocations;  /* The number of calls to pvPortMalloc() that have returned a valid memory block. */
    size_t xNumberOfSuccessfulFrees;        /* The number of calls to vPortFree() that has successfully freed a block of memory. */
} HeapStats_t;

/* Define the linked list structure.  This is used to link free blocks in order
 * of their memory address. */
typedef struct A_BLOCK_LINK
{
    struct A_BLOCK_LINK * pxNextFreeBlock; /*<< The next free block in the list. */
    size_t xBlockSize;                     /*<< The size of the free block. */
} BlockLink_t;


/*******------- Public Functions -------*******/

void * pvPortMalloc( size_t xWantedSize );

void vPortFree( void * pv );

size_t xPortGetFreeHeapSize( void );

size_t xPortGetMinimumEverFreeHeapSize( void );

void vPortInitialiseBlocks( void );

#ifdef USE_HEAP_5
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions );
#endif

void vPortGetHeapStats( HeapStats_t * pxHeapStats );


#define portMEMORY_BARRIER() __asm volatile( "" ::: "memory" )

#define vTaskSuspendAll()
#define xTaskResumeAll()

#define mtCOVERAGE_TEST_MARKER()
#define traceMALLOC( pvReturn, xWantedSize )
#define traceFREE( pv, xBlockSize )

#define taskENTER_CRITICAL()
#define taskEXIT_CRITICAL()

#endif  /* heap.h */


/********************************** End of File ******************************/
