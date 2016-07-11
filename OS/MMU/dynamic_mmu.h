/*
 * MMU.h
 *
 * Created: 7/10/2016 10:34:33 PM
 *  Author: sameh
 */ 



#include <stdlib.h>
#include <stdint.h>

#if (DYNAMIC_MEMORY_ALLOCATION == 0x01)
void *pvPortMalloc(size_t xWantedSize);
void vPortFree( void *pv );
size_t xPortGetFreeHeapSize( void );
static void prvHeapInit( void );
#endif