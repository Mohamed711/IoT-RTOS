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
 * 
 * 	This version is a modified and enhanced version of the queue module
 * 	in the freeRTOS distribution.
 *****************************************************************************/

#include <stdint.h>

#include "../RTOS.h"
#include "ipc.h"

void ipc_test()
 {
	
	uint8_t uxLength, uxItemSize, xVal, debugValue;
	QueueHandle_t queue;
	uxLength = 2;
	uxItemSize = 4;

	queue = IPC_xQueueCreate(uxLength, uxItemSize);

	xVal = IPC_xQueueIsQueueFullFromISR(queue);
	if ( xVal == pdFALSE )
	{
		debugValue = 10;
	}

	xVal = IPC_xQueueIsQueueEmptyFromISR(queue);
	if ( xVal == pdTRUE )
		{
			debugValue = 20;
		}

	xVal = IPC_uxQueueMessagesWaitingFromISR(queue);
	if ( xVal == 0x00 )
		{
			debugValue = 30;
		}

	xVal = IPC_uxQueueSpacesAvailable(queue);

	debugValue = xVal;

	debugValue += 1;


	int z = 100, q = 200;
	IPC_xQueueSendToFront(queue,&z,0);
	IPC_xQueueSendToFront(queue,&q,0);

	int val1,val2;
	IPC_xQueueGenericReceive(queue,&val1,0,pdFALSE);
	IPC_xQueueGenericReceive(queue,&val2,0,pdFALSE);

	z = 100, q = 200;
	IPC_xQueueSendToBack(queue,&z,0);
	IPC_xQueueSendToBack(queue,&q,0);

	IPC_xQueueGenericReceive(queue,&val1,0,pdTRUE);
	IPC_xQueueGenericReceive(queue,&val2,0,pdFALSE);

}

