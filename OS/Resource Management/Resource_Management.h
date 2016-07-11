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


#ifndef RESOURCE_MANAGEMENT_H_
#define RESOURCE_MANAGEMENT_H_

#include <stdint.h>

#include "../Scheduler/queue.h"

 typedef struct {
	 volatile uint8_t count;
	 qid queue;
 } countingSemaphoreStruct_t;


 extern uint8_t semaphore_array_index;
 extern countingSemaphoreStruct_t *semaphore_array[];



 /******************************************************************************
  *
  *	Initializes counting semaphore with initial count
  *
  *	\param sema	is a pointer to a semaphore
  *	\param count is the value of the count
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 uint16_t countingSemaphore_Initialize( countingSemaphoreStruct_t *sema, int8_t count );

/******************************************************************************
  *
  *	Deletes a counting semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 uint16_t countinSemaphore_Delete( countingSemaphoreStruct_t *sema );

/******************************************************************************
  *
  *	Wait for a counting semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 uint16_t countingSemaphore_Wait( countingSemaphoreStruct_t *sema );

/******************************************************************************
  *
  *	Wait for a counting semaphore a certian amount of time
  *
  *	\param sema	is a pointer to a semaphore
  *	\param timeout is the time it waits
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 uint16_t countingSemaphore_WaitTimed( countingSemaphoreStruct_t *sema , uint32_t timeout );

/******************************************************************************
  *
  *	Release a counting semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 uint16_t countingSemaphore_Signal( countingSemaphoreStruct_t *sema );
 
 /*************************	BINARY SEMAPHORE	***************************/

typedef struct
{
	qid Bsemaphore_queue ;
	//Queue *Bsem_queue = createQueue(10);
	int8_t  Bsemaphore_count;	
}binarySemaphoreStruct_t;

/***********************************************************************************************
*
*	This function initializes the semaphore
*
*	Parameters:		
*				p_Bsem: a pointer to a semaphore struct
*
************************************************************************************************/

uint16_t binarySemaphore_Initialize(binarySemaphoreStruct_t *p_Bsemaphore);


/***********************************************************************************************
*
*	This function waits for a binary semaphore to be available 
*
*	Parameters:
*				p_Bsem: a pointer to a semaphore struct
*
************************************************************************************************/

uint16_t binarySemaphore_Wait (binarySemaphoreStruct_t *p_Bsemaphore);


/***********************************************************************************************
*
*	This function releases a binary semaphore
*
*	Parameters:
*				p_Bsem: a pointer to a semaphore struct
*
************************************************************************************************/

uint16_t binarySemaphore_Signal(binarySemaphoreStruct_t *pBsemaphore);



uint16_t binarySemaphore_Delete (binarySemaphoreStruct_t *pBsemaphore );

#endif /* RESOURCE_MANAGEMENT_H_ */
