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


#ifndef SEMA_H_
#define SEMA_H_

#include <stdint.h>

#include "queue.h"


 typedef struct {
	 volatile uint8_t count;
	 Queue *queue;
 } Semaphore;

 /******************************************************************************
  *
  *	Initializes semaphore with initial count
  *
  *	\param sema	is a pointer to a semaphore
  *	\param count is the value of the count
  *
  * \return None
  *
  *****************************************************************************/
void sema_init( Semaphore *sema, uint8_t count );

/******************************************************************************
  *
  *	Deletes a semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return None
  *
  *****************************************************************************/
void sema_delete( Semaphore *sema );

/******************************************************************************
  *
  *	Wait for a semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return None
  *
  *****************************************************************************/
void sema_wait( Semaphore *sema );

/******************************************************************************
  *
  *	Wait for a semaphore a certian amount of time
  *
  *	\param sema	is a pointer to a semaphore
  *	\param timeout is the time it waits
  *
  * \return None
  *
  *****************************************************************************/
void sema_wait_timed( Semaphore *sema , uint32_t timeout );

/******************************************************************************
  *
  *	Release a semaphore
  *
  *	\param sema	is a pointer to a semaphore
  *
  * \return None
  *
  *****************************************************************************/
void sema_signal( Semaphore *sema );

#endif /* SEMA_H_ */
