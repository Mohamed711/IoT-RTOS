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
#ifndef INITIALIZE_H_
#define INITIALIZE_H_
#include "realTimeClock.h"
#include "Process.h"
#include "queue.h"
void initializeOS(void);
extern struct procent proctab[NPROC];		  /* table of processes */
#ifdef AVR
#define portFLAGS_INT_ENABLED					( ( uint16_t ) 0x80 )
typedef void (*pdTASK_CODE)( void * ); // pointer to the task function
extern portSTACK_TYPE *InitialiseStack( portSTACK_TYPE *saddr, pdTASK_CODE pxCode);
extern volatile uint8_t* pxCurrentTCB_H;
extern volatile uint8_t* pxCurrentTCB_L;
#endif
#endif /* INITIALIZE_H_ */
