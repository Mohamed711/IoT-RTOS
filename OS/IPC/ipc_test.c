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

#include "../RTOS.h"
#include "ipc.h"

void ipc_test()
 {
	
	uint8_t uxLength, uxItemSize, xVal, debugValue;
	QueueHandle_t queue;
	uxLength = 2;
	uxItemSize = 4;

	queue = xQueueCreate(uxLength, uxItemSize);

	xVal = xQueueIsQueueFullFromISR(queue);
	if ( xVal == pdFALSE )
	{
		debugValue = 10;
	}

	xVal = xQueueIsQueueEmptyFromISR(queue);
	if ( xVal == pdTRUE )
		{
			debugValue = 20;
		}

	xVal = uxQueueMessagesWaitingFromISR(queue);
	if ( xVal == 0x00 )
		{
			debugValue = 30;
		}

	xVal = uxQueueSpacesAvailable(queue);

	debugValue = xVal;

	debugValue += 1;


	int z = 100, q = 200;
	xQueueSendToFront(queue,&z,0);
	xQueueSendToFront(queue,&q,0);

	int val1,val2;
	xQueueGenericReceive(queue,&val1,0,pdFALSE);
	xQueueGenericReceive(queue,&val2,0,pdFALSE);

	z = 100, q = 200;
	xQueueSendToBack(queue,&z,0);
	xQueueSendToBack(queue,&q,0);

	xQueueGenericReceive(queue,&val1,0,pdTRUE);
	xQueueGenericReceive(queue,&val2,0,pdFALSE);

}

