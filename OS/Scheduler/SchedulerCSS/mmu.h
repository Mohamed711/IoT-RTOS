#ifndef MMU_H_
#define MMU_H_

#include <stdlib.h>
#include <stdint.h>

#define MPU_WRAPPERS_INCLUDED_FROM_API_FILE
#include "headers.h"
#include "Config.h"
#undef MPU_WRAPPERS_INCLUDED_FROM_API_FILE

/*
static union xRTOS_HEAP
{
	#if portBYTE_ALIGNMENT == 8
		volatile portDOUBLE dDummy;
	#else
		volatile unsigned long ulDummy;
	#endif	
		unsigned char ucHeap[configTOTAL_HEAP_SIZE];
} xHeap;

static size_t xNextFreeByte = (size_t)0;
*/

#define configADJUSTED_HEAP_SIZE	( configTOTAL_HEAP_SIZE - portBYTE_ALIGNMENT )

/* Allocate the memory for the heap. */
static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];
static size_t xNextFreeByte = ( size_t ) 0;
/*-----------------------------------------------------------*/

void *pvPortMalloc(size_t xWantedSize);
void vPortInitialiseBlocks(void);
size_t xPortGetFreeHeapSize(void);

#endif