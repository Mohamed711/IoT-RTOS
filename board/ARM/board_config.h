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

#ifndef IOT_RTOS_BOARD_ARM_BOARD_CONFIG_H_
#define IOT_RTOS_BOARD_ARM_BOARD_CONFIG_H_

#define configTOTAL_HEAP_SIZE 30000
#define portBYTE_ALIGNMENT  	8 //till we know if it's automatically or not
#define EnterCriticalSection()
#define ExitCriticalSection()

#endif /* IOT_RTOS_BOARD_ARM_BOARD_CONFIG_H_ */
