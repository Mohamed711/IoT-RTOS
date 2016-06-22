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

#ifndef IPC_CFG_H_
#define IPC_CFG_H_

#include <stdint.h>
#include "../RTOS.h"
#include "ipc_trace.h"

typedef uint8_t TimeOut_t;
typedef uint8_t TickType_t ;	// ticktype is a structure for the tick

#define errQUEUE_FULL	0x00	// error value indicates that the queue is full
#define errQUEUE_EMPTY 	0x00	// error the queue is empty
#define configUSE_QUEUE_LOCKS 1	// configure the locks

#endif
