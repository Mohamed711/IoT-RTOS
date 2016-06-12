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

#ifndef HEADERS_H_
#define HEADERS_H_



#include "std.h"
#include "Process.h"
#include "queue.h"
#include "std.h"
#include "Configuration.h"
#include "Initialize.h"
#include "delay.h"
//#include "contextSwitch.h"
#include "realTimeClock.h"

#if ARM
#include "TivaDrivers/Timer/HAL_Timer_TivaC.h"
#else
#include "AvrDrivers/Timer/HAL_Timer_AVR.h"
#endif


#endif /* HEADERS_H_ */
