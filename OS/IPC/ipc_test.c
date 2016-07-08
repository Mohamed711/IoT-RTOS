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
#include "ipc.h"
#include "../Scheduler/Process.h"
#include "../Scheduler/queue.h"
#include "../Scheduler/realTimeClock.h"
#include "../Scheduler/Initialize.h"
#include "../Scheduler/nullProcess.h"
#include "ipc_test.h"

#ifdef ARM

extern uint32_t prcount;

QueueHandle_t pxQueue;
uint8_t mode = 0;

void task1()
{
	
	uint32_t z =10;
	IPC_xQueueSendToFront(pxQueue,&z,IPC_NO_SLEEP);
	
}

void task2()
{
	int val1;
	IPC_xQueueGenericReceive(pxQueue,&val1,IPC_WAIT_FOREVER,IPC_RECEIVE_WITH_CONSUMING);
	
	if (val1 == 20) 
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 7);
	}
	else
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
	}
}


uint16_t IPC_test()
 {
	prcount=0;
	readyList = newqueue();
	suspendedList = newqueue();
	sleepingList = newSleepingQueue();
	Scheduler_initializenullProcess();
	Timer_New(Scheduler_clkhandler, 50000000);
	 	
	uint8_t uxLength, uxItemSize, xVal;
	QueueHandle_t queue;
	uxLength = 2;
	uxItemSize = 4;

	/* Test the creation of the queue */
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	 pxQueue = IPC_xQueueCreate(uxLength, uxItemSize);
	 
	 SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	 
	pid id1= Scheduler_processCreate(task1, 700, 20, "P2");	
	pid id2= Scheduler_processCreate(task2, 700, 25, "P3");	

	Scheduler_processSetReady(id2);
	Scheduler_processSetReady(id1);

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);

	/* Test the full queue value */ 
	xVal = IPC_xQueueIsQueueFullFromISR(queue);
	if ( xVal == pdTRUE )
	{
		 return 0xFFFF;
	}

	/* Checks if the queue is empty */
	xVal = IPC_xQueueIsQueueEmptyFromISR(queue);
	if ( xVal == pdFALSE )
		{
			return 0xFF;
		}
		
  /* Checks the number of waiting messages */
	xVal = IPC_uxQueueMessagesWaitingFromISR(queue);
	if ( xVal != 0x00 )
		{
			return 0xFF;
		}

	/* Checks the spaces available in teh queeu */
	xVal = IPC_uxQueueSpacesAvailable(queue);

		
	int z = 100, q = 200;
	IPC_xQueueSendToFront(queue,&z,IPC_NO_SLEEP);
	IPC_xQueueSendToFront(queue,&q,IPC_NO_SLEEP);

	int val1,val2;
	IPC_xQueueGenericReceive(queue,&val1,IPC_NO_SLEEP,IPC_RECEIVE_WITH_CONSUMING);
	IPC_xQueueGenericReceive(queue,&val2,IPC_NO_SLEEP,IPC_RECEIVE_WITH_CONSUMING);
		
	if (val1 != 200 || val2 != 100)
	{
		return 0xFF;
	}
		
	z = 100, q = 200;
	IPC_xQueueSendToBack(queue,&z,IPC_NO_SLEEP);
	IPC_xQueueSendToBack(queue,&q,IPC_NO_SLEEP);

	IPC_xQueueGenericReceive(queue,&val1,IPC_NO_SLEEP,IPC_RECEIVE_WITHOUT_CONSUMING);
	IPC_xQueueGenericReceive(queue,&val2,IPC_NO_SLEEP,IPC_RECEIVE_WITH_CONSUMING);
	
	if ( z != 100 && q != 100 ) 
	{
		return 0xFF;
	}
	
	__set_PSP(__get_MSP()); // copy current stack pointer value into PSP
  __set_CONTROL(0x00000002); // switch to "process" stack pointer PSP
	
	Scheduler_nullProc();
	
	return SUCCESS; 

}


/*
 uint16_t IPC_test()
{
	uint16_t u16Return;
	u16Return=IPC_ModulerTest();
		if ( u16Return != SUCCESS )
		return u16Return;
	u16Return=IPC_DiffScenariosTest();
		if ( u16Return != SUCCESS )
		return u16Return;
}

*/
 uint16_t IPC_ModulerTest()
{
	uint16_t u16Return;
	u16Return=IPC_u16QueueCreate_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueEmpty_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueFull_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueSendToFront_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueSendToBack_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueOverwrite_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueGetPeek_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueReceive_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueReset_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueMsgWaiting_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16QueueSpacesAvailable_test();
		if ( u16Return != SUCCESS )
		return u16Return;
}


 uint16_t IPC_DiffScenariosTest()
{
	uint16_t u16Return;
	u16Return = IPC_u16Queue_Async_Send_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16Queue_Async_Recv_test();
		if ( u16Return != SUCCESS )
		return u16Return;
 	u16Return=IPC_u16Queue_Sync_Send_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16Queue_Sync_Recv_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16Queue_Partial_Send_test();
		if ( u16Return != SUCCESS )
		return u16Return;
  u16Return=IPC_u16Queue_Partial_Recv_test();
		if ( u16Return != SUCCESS )
		return u16Return;
}
 
 /* FUNCTION TESTS */
 uint16_t IPC_u16QueueCreate_test()
{
	QueueHandle_t queue;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	
}


 uint16_t IPC_u16QueueEmpty_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	u16Return = IPC_xQueueIsQueueEmptyFromISR(queue);
	if ( u16Return != pdTRUE )
			return IPC_QUEUE_EMPTY_FAIL;
	
}


 uint16_t IPC_u16QueueFull_test()
{
}


 uint16_t IPC_u16QueueSendToFront_test()
{
}


 uint16_t IPC_u16QueueSendToBack_test()
{
}


 uint16_t IPC_u16QueueOverwrite_test()
{
}


 uint16_t IPC_u16QueueGetPeek_test()
{
}


 uint16_t IPC_u16QueueReceive_test()
{
}


 uint16_t IPC_u16QueueReset_test()
{
}


 uint16_t IPC_u16QueueMsgWaiting_test()
{
}


 uint16_t IPC_u16QueueSpacesAvailable_test()
{
}


 
 
 /* MODULE TEST */
 uint16_t IPC_u16Queue_Async_Send_test()
{
}


 uint16_t IPC_u16Queue_Async_Recv_test()
{
}


 uint16_t	IPC_u16Queue_Sync_Send_test()
{
}


 uint16_t IPC_u16Queue_Sync_Recv_test()
{
}


 uint16_t IPC_u16Queue_Partial_Send_test()
{
}


 uint16_t IPC_u16Queue_Partial_Recv_test()
{
}




#endif