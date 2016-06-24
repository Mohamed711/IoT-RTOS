
#ifndef MMU_H_
#define MMU_H_


#include <stdlib.h>
#include <stdint.h>

#include "../RTOS.h"


/*-----------------------------------------------------------*/

void *pvPortMalloc(size_t xWantedSize);	//allocate the desired size for a process
void vPortInitialiseBlocks(void);	//to clear heap and reallocate it
size_t xPortGetFreeHeapSize(void);	//get the free heap size( size of unallocated heap)


#endif /* MMU_H_ */
