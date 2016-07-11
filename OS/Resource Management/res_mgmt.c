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
#include "Resource_Management.h"
#include "../Scheduler/Process.h"
#include "../Scheduler/queue.h"
#include "../Scheduler/realTimeClock.h"
#include "../Scheduler/Initialize.h"
#include "../Scheduler/nullProcess.h"
#include "res_mgmt.h"

#ifdef ARM

extern uint32_t prcount;


volatile binarySemaphoreStruct_t Binary_struct_test;

void res_task1()
{
	
		
		//binarySemaphore_Wait(&Binary_struct_test);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
		SysCtlDelay(50000000);
	//	binarySemaphore_Signal(&Binary_struct_test);
		
	
}

void res_task2()
{
	
	//	binarySemaphore_Wait(&Binary_struct_test);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
		SysCtlDelay(20000000);
	//	binarySemaphore_Signal(&Binary_struct_test);
		
	
}


uint16_t RES_test()
 {

	binarySemaphore_Initialize(&Binary_struct_test);	
	 
	pid id1= Scheduler_processCreate(res_task1, 700, 20, "P1");	
	pid id2= Scheduler_processCreate(res_task2, 700, 25, "P2");	

	Scheduler_processSetReady(id2);
	Scheduler_processSetReady(id1);

	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);

	 
	 // code here
	 
	 

	
	return SUCCESS; 

}


#endif