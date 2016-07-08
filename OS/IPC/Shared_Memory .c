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
#include "../Resource Management/Resource Management.h"
//*****************************************************************************
//
//! Shared Memory data structure
//!
//! \param pcHead is a pointer to the beginning of the shared memory storage area.
//! \param SizeInBytes is the number of bytes allocated for the shared memory storage area.
//! \param Semaphore is a binary semaphore data structure used for synchronization and to avoid readers-writers� problems.
//!
//*****************************************************************************

typedef struct {
	uint8_t * pcHead;
	uint8_t SizeInBytes;
	Bsem_t Semaphore;
} SharedMem_t;

SharedMemHandle_t xSharedMemGenericCreate( const UBaseType_t uxSharedMemSize )
{
	SharedMem_t *pxNewSharedMem;
	size_t xSharedMemSizeInBytes;
	SharedMemHandle_t xReturn = NULL;

	configASSERT( ( uxSharedMemSize > ( UBaseType_t ) 0 ) );

	/* The shared memory is one byte longer than asked for to make wrap checking
	easier/faster. */
	xSharedMemSizeInBytes = ( size_t ) uxSharedMemSize  + ( size_t ) 1;


	/* Allocate the new shared memory structure and storage area. */


	pxNewSharedMem = (SharedMem_t * ) malloc( sizeof ( SharedMem_t ) + xSharedMemSizeInBytes );

	if( pxNewSharedMem != NULL )
	{

		/* Jump past the shared memory structure to find the location of the shared memory
		storage area. */
		pxNewSharedMem->pcHead = ( ( int8_t * ) pxNewSharedMem ) + sizeof( SharedMem_t );


		/* Initialise the shared memory members as described above where the shared memory type
		is defined. */
		pxNewSharedMem->SizeInBytes = uxSharedMemSize;
		vid_Binary_semp_Bsem_init(&(pxNewSharedMem->Semaphore));
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


	SharedMem_t * const pxSharedMem = ( SharedMem_t * ) xSharedMem;

			configASSERT( pxSharedMem );


			/* waits for the shared memory to be available */
				vid_Binary_semp_Bsem_wait (&(pxSharedMem->Semaphore));

				*(pxSharedMem->pcHead) = xMessage;

				/* signals the semaphore */
				vid_Binary_semp_Bsem_signal(&(pxSharedMem->Semaphore));

}
/*-----------------------------------------------------------*/

uint32_t xSharedMemReceive( SharedMemHandle_t xSharedMem )
{

	                SharedMem_t * const pxSharedMem = ( SharedMem_t * ) xSharedMem;

	                  /* waits for the shared memory to be available */
	                vid_Binary_semp_Bsem_wait (&(pxSharedMem->Semaphore));

					uint32_t xReturn;
					xReturn = *(pxSharedMem->pcHead);

                     /* signals the semaphore */
					vid_Binary_semp_Bsem_signal(&(pxSharedMem->Semaphore));

					return xReturn;
}
