/******************************************************************************
 *	RTOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *  
 *  All rights reserved
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the redistributions of the
 *  source code must retain the above copyright notice, and this condition.
 *****************************************************************************/


#include <stdint.h>

#ifdef ARM
//#include "C:/Keil_v5/ARM/CMSIS/Include/core_cmFunc.h"
#endif 


#include "../RTOS.h"
#include "Shared_Memory.h"
#include "SharedMem_test.h"
#include "../Scheduler/Process.h"
#include "../Scheduler/queue.h"
#include "../Scheduler/realTimeClock.h"
#include "../Scheduler/Initialize.h"
#include "../Scheduler/nullProcess.h"


#ifdef ARM

extern uint32_t prcount;

SharedMemHandle_t pxSharedMem;
uint32_t message = 1200;


void shared_memTask1()
{
	pxSharedMem = xSharedMemCreate( );
	xSharedMemSend( pxSharedMem , message );
		
}

void shared_memTask2()
{
	uint32_t received;
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	received = xSharedMemReceive( pxSharedMem );
	if (received == 1200) 
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 7);
	}
}


uint16_t SharedMem_test()
 {

	pid id1= Scheduler_processCreate(shared_memTask1, 700, 25, "P2");	
	pid id2= Scheduler_processCreate(shared_memTask2, 700, 20, "P3");	

	Scheduler_processSetReady(id2);
	Scheduler_processSetReady(id1);
	
	return SUCCESS; 
}

#endif