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
#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <stdint.h>
#include <stdbool.h>

#define ARM 1

#define NSEM 10 //semaphore dummy
#define preemptive 0
#define NPROC 5
#define	QUANTUM	2
#define	MAXSECONDS	2147483		/* Max seconds per 32-bit msec	*/

#endif
