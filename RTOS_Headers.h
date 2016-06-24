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

#ifndef IOT_RTOS_RTOS_HEADERS_H_
#define IOT_RTOS_RTOS_HEADERS_H_

#include "User_Config.h"

#ifdef ARM
	#include "board/ARM/tivaHAL.h"
#endif

#ifdef AVR
	#include "board/AVR/atmegaHAL.h"
#endif

#include "OS/RTOS.h"
#include "OS/IPC/ipc.h"
#include "OS/MMU/mmu.h"
#include "OS/Resource Management/Resource Management.h"
#include "OS/Scheduler/*.h"


#endif /* IOT_RTOS_RTOS_HEADERS_H_ */
