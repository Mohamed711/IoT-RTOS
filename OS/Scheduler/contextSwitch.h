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

#ifndef CONTEXTSWITCH_H_
#define CONTEXTSWITCH_H_

#include "Process.h"

/*
 * The function definition is in the board folder as its implementation
 * differ with the type of the microcontroller used
 */
void Scheduler_contextSwitch(struct procent *ptold, struct procent *ptnew);
void jumptoPC(uint32_t LR);

#endif /* CONTEXTSWITCH_H_ */
