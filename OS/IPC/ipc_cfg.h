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

#define IPC_CFG_H

/* the basetype must be defined some where */
 typedef int8_t BaseType_t ;
 typedef uint8_t TickType_t ;
 typedef uint8_t UBaseType_t ;


#define configASSERT(x)
#define taskENTER_CRITICAL()
#define taskEXIT_CRITICAL()
#define pdTRUE
#define pdFALSE
#define mtCOVERAGE_TEST_MARKER()
#define PRIVILEGED_FUNCTION

/*
 #define SUCCESSFUL
 #define QUEUE_IS_EMPTY
 #define QUEUE_IS_FULL
*/
