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
static uint16_t task1_return;
static uint16_t task2_return;
static uint16_t mode_of_operation = 0;
QueueHandle_t queueTest;

void task1()
{
	uint32_t val1;
	IPC_xQueueGenericReceive(queueTest,&val1,IPC_NO_SLEEP,IPC_RECEIVE_WITH_CONSUMING);

}

void task2()
{
		uint32_t val1 , val2 = 20;
		IPC_xQueueSendToBack(queueTest,&val2,IPC_NO_SLEEP);
		IPC_xQueueSendToBack(queueTest,&val2,IPC_NO_SLEEP);
		IPC_xQueueSendToBack(queueTest,&val2,IPC_WAIT_FOREVER);
		IPC_xQueueGenericReceive(queueTest,&val1,IPC_NO_SLEEP,IPC_RECEIVE_WITH_CONSUMING);
	
		if (val1 == 20) 
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 7);
			task2_return = SUCCESS;
		}
		else
		{
			GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
			task2_return = IPC_QUEUE_SYNC_RECV_FAIL;
		}

}


uint16_t try_it()
 {	 	
	
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	 
	queueTest = IPC_xQueueCreate(2,4);
	pid id1= Scheduler_processCreate(task1, 700, 20, "P2");	
	pid id2= Scheduler_processCreate(task2, 700, 25, "P3");	

	Scheduler_processSetReady(id2);
	Scheduler_processSetReady(id1);
	QueueHandle_t queue;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	if ( pxQueue->uxItemSize != uxItemSize || 
			 pxQueue->uxLength != uxLength ||
			 pxQueue->uxMessagesWaiting != 0x00 || 
	     pxQueue->xTasksWaitingToReceive != (pxQueue->xTasksWaitingToSend+2) ||
			 pxQueue->pcReadFrom !=  pxQueue->pcTail - pxQueue->uxItemSize || 
			 pxQueue->pcWriteTo != pxQueue->pcHead )
		return IPC_QUEUE_CREATE_FAIL;
	
	
		return SUCCESS;

	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);


	
	__set_PSP(__get_MSP()); // copy current stack pointer value into PSP
  __set_CONTROL(0x00000002); // switch to "process" stack pointer PSP
	
	Scheduler_nullProc();
	
	return SUCCESS; 

}



 uint16_t IPC_test()
{
	uint16_t u16Return;
	u16Return=IPC_ModulerTest();
		if ( u16Return != SUCCESS )
		return u16Return;
	u16Return=IPC_DiffScenariosTest();
		if ( u16Return != SUCCESS )
		return u16Return;
		
		return SUCCESS;
}


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
		
		return SUCCESS;

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
		
		return SUCCESS;

}
 
 /* FUNCTION TESTS */
 uint16_t IPC_u16QueueCreate_test()
{
	QueueHandle_t queue;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	if ( pxQueue->uxItemSize != uxItemSize || 
			 pxQueue->uxLength != uxLength ||
			 pxQueue->uxMessagesWaiting != 0x00 || 
	     pxQueue->xTasksWaitingToReceive != (pxQueue->xTasksWaitingToSend+2) ||
			 pxQueue->pcReadFrom !=  pxQueue->pcTail - pxQueue->uxItemSize || 
			 pxQueue->pcWriteTo != pxQueue->pcHead )
		return IPC_QUEUE_CREATE_FAIL;
	
	
		return SUCCESS;

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
	
	return SUCCESS;

}


 uint16_t IPC_u16QueueFull_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	uint32_t val1 = 20;
	uint32_t val2 = 30;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	IPC_xQueueSendToBack(queue, &val1, IPC_NO_SLEEP);
	IPC_xQueueSendToBack(queue, &val2, IPC_NO_SLEEP);
	
	u16Return = IPC_xQueueIsQueueFullFromISR(queue);
	if ( u16Return != pdTRUE )
			return IPC_QUEUE_FULL_FAIL;
	
			return SUCCESS;

}


 uint16_t IPC_u16QueueSendToFront_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	uint32_t value = 20;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	IPC_xQueueSendToFront(pxQueue, &value, IPC_NO_SLEEP );
	if (*(pxQueue->pcReadFrom + pxQueue->uxItemSize) != 20 )
		return IPC_QUEUE_SEND_FRONT_FAIL;
	
			return SUCCESS;

}


 uint16_t IPC_u16QueueSendToBack_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	uint32_t value = 20;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	IPC_xQueueSendToBack(pxQueue, &value, IPC_NO_SLEEP );
	if (*(pxQueue->pcReadFrom - pxQueue->uxItemSize) != 20 )
		return IPC_QUEUE_SEND_BACK_FAIL;
	
			return SUCCESS;

}


 uint16_t IPC_u16QueueOverwrite_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 1;
	uxItemSize = 4;
	uint32_t value = 20;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	IPC_xQueueOverwrite(pxQueue, &value);
	if (*(pxQueue->pcWriteTo) != 20 )
		return IPC_QUEUE_OVERWRITE_FAIL;
	
			return SUCCESS;

}


 uint16_t IPC_u16QueueGetPeek_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 1;
	uxItemSize = 4;
	uint32_t value = 20;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	IPC_xQueueSendToBack(pxQueue, &value, IPC_NO_SLEEP);
	if (*(pxQueue->pcReadFrom) != 20 )
		return IPC_QUEUE_GETPEEK_FAIL;
	
			return SUCCESS;

}


 uint16_t IPC_u16QueueReceive_test()
{
	QueueHandle_t queue;
	uint8_t uxLength, uxItemSize;
	uxLength = 2;
	uxItemSize = 4;
	uint32_t value1 = 20,value2 = 30 , temp;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	IPC_xQueueSendToBack(queue, &value1, IPC_NO_SLEEP);
	IPC_xQueueSendToBack(queue, &value2, IPC_NO_SLEEP);
	IPC_xQueueReceive(queue, &temp, IPC_NO_SLEEP);
	if ( temp != 20 )
		return IPC_QUEUE_RECEIVE_FAIL;
	
	IPC_xQueueReceive(queue, &temp, IPC_NO_SLEEP);
	if ( temp != 30 )
		return IPC_QUEUE_RECEIVE_FAIL;
	
			return SUCCESS;

}


 uint16_t IPC_u16QueueReset_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 1;
	uxItemSize = 4;
	uint32_t value = 20;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	IPC_xQueueSendToBack(pxQueue, &value, IPC_NO_SLEEP);
	IPC_xQueueReset(queue);
	u16Return = IPC_xQueueReceive(pxQueue, &value, IPC_NO_SLEEP);
	if ( u16Return != errQUEUE_EMPTY)
		return IPC_QUEUE_RESET_FAIL;
	
	return SUCCESS;
}


 uint16_t IPC_u16QueueMsgWaiting_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 3;
	uxItemSize = 4;
	uint32_t val1 = 20;
	uint32_t val2 = 30;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	IPC_xQueueSendToBack(queue, &val1, IPC_NO_SLEEP);
	IPC_xQueueSendToBack(queue, &val2, IPC_NO_SLEEP);
	
	u16Return = IPC_uxQueueMessagesWaiting(queue);
	if ( u16Return != 2 )
			return IPC_QUEUE_MSG_WAITING_FAIL;
	
	return SUCCESS;
}


 uint16_t IPC_u16QueueSpacesAvailable_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 3;
	uxItemSize = 4;
	uint32_t val1 = 20;
	uint32_t val2 = 30;
	
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	u16Return = IPC_uxQueueSpacesAvailable(queue);
	if ( u16Return != 3 )
			return IPC_QUEUE_SPACE_AVAIL_FAIL;
	
	IPC_xQueueSendToBack(queue, &val1, IPC_NO_SLEEP);
	IPC_xQueueSendToBack(queue, &val2, IPC_NO_SLEEP);
	
	u16Return = IPC_uxQueueSpacesAvailable(queue);
	if ( u16Return != 1 )
			return IPC_QUEUE_SPACE_AVAIL_FAIL;
	
	return SUCCESS;
}


 
 
 /* MODULE TEST */
 uint16_t IPC_u16Queue_Async_Send_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 1;
	uxItemSize = 4;
	uint32_t value = 20;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	Queue_t *const pxQueue = (Queue_t * ) queue;
	IPC_xQueueSendToBack(pxQueue, &value, IPC_NO_SLEEP);
	u16Return = IPC_xQueueSendToBack(pxQueue, &value, IPC_NO_SLEEP);
	if ( u16Return != errQUEUE_FULL)
		return IPC_QUEUE_ASYNC_SEND_FAIL;
	
	return SUCCESS;
}


 uint16_t IPC_u16Queue_Async_Recv_test()
{
	QueueHandle_t queue;
	uint16_t u16Return;
	uint8_t uxLength, uxItemSize;
	uxLength = 1;
	uxItemSize = 4;
	uint32_t value = 20;
	queue = IPC_xQueueCreate(uxLength, uxItemSize);
	u16Return = IPC_xQueueReceive(queue, &value, IPC_NO_SLEEP);
	if ( u16Return != errQUEUE_EMPTY)
		return IPC_QUEUE_ASYNC_RECV_FAIL;
	
	return SUCCESS;
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