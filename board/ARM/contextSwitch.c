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

#include "../../OS/Scheduler/contextSwitch.h"
#include "../../OS/Scheduler/process.h"

void Scheduler_contextSwitch(struct procent *ptold, struct procent *ptnew)
{
	//ptold->returnValue = lrReg;
	jumptoPC(ptnew->returnValue);
}

__asm void jumptoPC(uint32_t LR)
{

	MOV PC, r0

}


__asm void saveContext(char* oldSP)
{
	mrs r0, psp
	stmdb  r0!,{r4-r11}
	msr psp, r0
	bx lr
}

__asm void loadContext(char* newSP)
{
	mrs r0, psp
	ldmfd  r0!, {r4-r11} 
	msr psp, r0
	bx lr
}





