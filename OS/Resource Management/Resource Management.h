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


#ifndef CSEMA_H_
#define CSEMA_H_

#include <stdint.h>

#include "../Scheduler/queue.h"


 typedef struct {
	 volatile uint8_t count;
	 int16_t queue;
 } Csema;



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
 int8_t Csema_init( Csema *sema, int8_t count );

/******************************************************************************
  *
  *	Deletes a counting semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 int8_t Csema_delete( Csema *sema );

/******************************************************************************
  *
  *	Wait for a counting semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 int8_t Csema_wait( Csema *sema );

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
 int8_t Csema_wait_timed( Csema *sema , uint32_t timeout );

/******************************************************************************
  *
  *	Release a counting semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return SYSERR(-1) if an error occurs or OK (1) if it succeeds
  *
  *****************************************************************************/
 int8_t Csema_signal( Csema *sema );



/*********************************************************************************************************************************/


/*************************	BINARY SEMAPHORE	***************************/

typedef struct
{
	qid Bsem_queue ;
	//Queue *Bsem_queue = createQueue(10);
	int8_t count;	
}Bsem_t;

/***********************************************************************************************
*
*	This function initializes the semaphore
*
*	Parameters:		
*				p_Bsem: a pointer to a semaphore struct
*
************************************************************************************************/

static inline void vid_Binary_semp_Bsem_init(Bsem_t *p_Bsem)
{
	// need to check
	p_Bsem->Bsem_queue = newqueue();
	p_Bsem->count=1;
		
}


/***********************************************************************************************
*
*	This function waits for a binary semaphore to be available 
*
*	Parameters:
*				p_Bsem: a pointer to a semaphore struct
*
************************************************************************************************/

void vid_Binary_semp_Bsem_wait (Bsem_t *S);


/***********************************************************************************************
*
*	This function releases a binary semaphore
*
*	Parameters:
*				p_Bsem: a pointer to a semaphore struct
*
************************************************************************************************/

void vid_Binary_semp_Bsem_signal(Bsem_t *S);

#endif /* CSEMA_H_ */
