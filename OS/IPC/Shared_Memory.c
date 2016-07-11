/******************************************************************************
 *	OurOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *
 *  All rights reserved
 *
 *  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *****************************************************************************/

#include <stdint.h>
#include <stdlib.h>

#include "../RTOS.h"
#include "Shared_Memory.h"
#include "../Resource Management/Resource_Management.h"
#include "../mmu/mmu.h"
#include "../Scheduler/realTimeClock.h"
//*****************************************************************************
//
//! Shared Memory data structure
//!
//! \param pcHead is a pointer to the beginning of the shared memory storage area.
//! \param SizeInBytes is the number of bytes allocated for the shared memory storage area.
//! \param Semaphore is a binary semaphore data structure used for synchronization and to avoid readers-writers’ problems.
//!
//*****************************************************************************
typedef struct {
	uint32_t * pcHead;
	binarySemaphoreStruct_t Semaphore;
} SharedMem_t;

SharedMemHandle_t xSharedMemGenericCreate( )
{
	SharedMem_t *pxNewSharedMem;
	//size_t xSharedMemSizeInBytes;
	SharedMemHandle_t xReturn = NULL;

	/* Allocate the new shared memory structure and storage area. */

	pxNewSharedMem = (SharedMem_t * ) pvPortMalloc( sizeof ( SharedMem_t ) + 4 );
	if( pxNewSharedMem != NULL )
	{

		/* Jump past the shared memory structure to find the location of the shared memory
		storage area. */
		pxNewSharedMem->pcHead = ( ( int32_t * ) pxNewSharedMem ) + sizeof( SharedMem_t );


		/* Initialise the shared memory members as described above where the shared memory type
		is defined. */
		//pxNewSharedMem->SizeInBytes = uxSharedMemSize;
		binarySemaphore_Initialize(&(pxNewSharedMem->Semaphore));
		xReturn = pxNewSharedMem;
	}
	else
	{
		mtCOVERAGE_TEST_MARKER();
	}

	configASSERT( xReturn );

	return xReturn;
}


void xSharedMemSend( SharedMemHandle_t xSharedMem , uint32_t xMessage )
{

	SharedMem_t * pxSharedMem = ( SharedMem_t * ) xSharedMem;

	configASSERT( pxSharedMem );
//	uint32_t value = (uint32_t) pxSharedMem;
	/* waits for the shared memory to be available */
	binarySemaphore_Wait (&(pxSharedMem->Semaphore));
	
	Scheduler_sleepms(2000);

//	pxSharedMem = (SharedMem_t *)value;

	*(pxSharedMem->pcHead) = xMessage;





	binarySemaphore_Signal(&(pxSharedMem->Semaphore));

}

uint32_t xSharedMemReceive( SharedMemHandle_t xSharedMem )
{
	  SharedMem_t * const pxSharedMem = ( SharedMem_t * ) xSharedMem;

	  /* waits for the shared memory to be available */
	  binarySemaphore_Wait (&(pxSharedMem->Semaphore));

		uint32_t xReturn;
		xReturn = *(pxSharedMem->pcHead);

    /* signals the semaphore */
		binarySemaphore_Signal(&(pxSharedMem->Semaphore));

		return xReturn;
}

