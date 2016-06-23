
#ifndef MMU_H_
#define MMU_H_


#include <stdlib.h>
#include <stdint.h>

#include "../RTOS.h"

/* Allocate the memory for the heap. */
static uint8_t ucHeap[ configTOTAL_HEAP_SIZE ];	//create the heap array with size of the heap. It's static as it'll be used for all
static size_t xNextFreeByte = ( size_t ) 0;	//initialize the heap
/*-----------------------------------------------------------*/

void *pvPortMalloc(size_t xWantedSize);	//allocate the desired size for a process
void vPortInitialiseBlocks(void);	//to clear heap and reallocate it
size_t xPortGetFreeHeapSize(void);	//get the free heap size( size of unallocated heap)




#endif /* MMU_H_ */
