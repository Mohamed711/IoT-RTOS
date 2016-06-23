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
	uxLength = 5;
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

}

