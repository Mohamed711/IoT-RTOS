
#include <stdlib.h>
#include <stdint.h>

#include"mmu.h"
#include"Config.h"

void *pvPortMalloc( size_t xWantedSize )
{
void *pvReturn = NULL; 

	/* Ensure that blocks are always aligned to the required number of bytes */
	#if portBYTE_ALIGNMENT != 1
		if( xWantedSize & portBYTE_ALIGNMENT_MASK )
		{
			/* Byte alignment required */
			xWantedSize += ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) );
		}
	#endif

	processSuspendAll();	
	
		/* Check if the wanted size is available or not */
		if( ( ( xNextFreeByte + xWantedSize ) < configTOTAL_HEAP_SIZE ) &&
			( ( xNextFreeByte + xWantedSize ) > xNextFreeByte )	)/* Check for overflow. */
		{
			/* Return the next free byte */ 
			pvReturn = &( ucHeap[ xNextFreeByte ] );
			/* increment the index with the size allocated */
			xNextFreeByte += xWantedSize;			
		}	
	processResumeAll();
	
	#if( configUSE_MALLOC_FAILED_HOOK == 1 )
	{
		if( pvReturn == NULL )
		{
			//extern void vApplicationMallocFailedHook( void );
			//vApplicationMallocFailedHook();
			
		}
	}
	#endif	

	return pvReturn;
}
/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

void vPortInitialiseBlocks(void)
{
	/* Only required when static memory is not cleared */
	xNextFreeByte = (size_t)0;
}
/*-----------------------------------------------------------*/

size_t xPortGetFreeHeapSize(void)
{
	return (configTOTAL_HEAP_SIZE - xNextFreeByte);
}

