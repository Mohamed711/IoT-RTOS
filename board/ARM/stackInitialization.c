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

#include "../../OS/Scheduler/process.h"


#define INITIAL_XPSR                (0x01000000)
#define STACK_MARKER                (0x77777777)

char * Scheduler_stackInitialization(char* stackpointer, void *func(), uint32_t ssize)
{

	/*to go to the stack's top*/
	 uint32_t *stk ;
	 stk = (uint32_t *)((uintptr_t)stackpointer + ssize);

	    /* adjust to 32 bit boundary by clearing the last two bits in the address */
	    stk = (uint32_t *)(((uint32_t)stk) & ~((uint32_t)0x3));

	    /* stack start marker */
	    stk--;
	    *stk = STACK_MARKER;
	    /* make sure the stack is double word aligned (8 bytes) */
	     /* This is required in order to conform with Procedure Call Standard for the
	      * ARM® Architecture (AAPCS) */
	     /* http://infocenter.arm.com/help/topic/com.arm.doc.ihi0042e/IHI0042E_aapcs.pdf */
	     if (((uint32_t) stk & 0x7) != 0) {
	         /* add a single word padding */
	         --stk;
	         *stk = ~((uint32_t)STACK_MARKER);
	     }

	     /* xPSR - initial status register */
	         stk--;
	         *stk = (uint32_t)INITIAL_XPSR;
	         /* pc - initial program counter value := thread entry function */
	         stk--;
	         *stk = (uint32_t)func;
	         /* lr - contains the return address when the thread exits */
	         stk--;
	         *stk = (uint32_t)Scheduler_processKill;
	         /* r12 */
	         stk--;
	         *stk = 0;
	         /* r3 - r1 */
	         uint32_t i;
	         for ( i = 3; i >= 1; i--) {
	             stk--;
	             *stk = i;
	         }
	         /* r0 - contains the thread function parameter */
	        stk--;
	         *stk = 0;

	         /* r11 - r4 */
	         for (i = 11; i >= 4; i--) {
	             stk--;
	             *stk = i;
	         }
	             return (char*) stk;

}



