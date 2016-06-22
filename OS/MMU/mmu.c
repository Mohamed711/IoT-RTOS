
#include <stdlib.h>
#include <stdint.h>

#include"mmu.h"

/* void* means that it's a generic type it can return any type or you can say It is a pointer with unknown type.
	It's used here as the memory is typeless(because it does not have a properly constructed object in it yet).
   The function returns: a pointer to the start address of the allocated memory. */
void *pvPortMalloc( size_t xWantedSize )
{
void *pvReturn = NULL; 

	/* just to check if the byte alignment type is 1 byte or another type as in 1 byte type you don't need to make byte alignment */
	#if portBYTE_ALIGNMENT != 1
		if( xWantedSize & portBYTE_ALIGNMENT_MASK ) 
		{
			/* the aim of this operation is to check if the size is divisible by the byte alignment number */
			/* if he entered here then Byte alignment is required to make the size can be divisible by the byte alignment number*/
			xWantedSize += ( portBYTE_ALIGNMENT - ( xWantedSize & portBYTE_ALIGNMENT_MASK ) );
		}
	#endif

	processSuspendAll();	
	
		/* Check if the wanted size is available or not */
		if( ( ( xNextFreeByte + xWantedSize ) < configTOTAL_HEAP_SIZE ) &&
			( ( xNextFreeByte + xWantedSize ) > xNextFreeByte )	)/* Check for overflow. */
		{
			/* pvReturn now points to the address of the first allocated byte */ 
			pvReturn = &( ucHeap[ xNextFreeByte ] );
			/* increment the index of the allocated memory with the size newly allocated */
			xNextFreeByte += xWantedSize;			
		}	
	processResumeAll();
	//try to put anything here it'll be ignored due to processResumeAll() after fixing it remove next line
	int x=xNextFreeByte ;
	
	
		if( pvReturn == NULL )
		{
			EnterCriticalSection();
			for(;;);
			ExitCriticalSection();
		}
	
	

	
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

