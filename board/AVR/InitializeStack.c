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
#include "../../RTOS_Headers.h"
char * Scheduler_stackInitialization(char* stackpointer, void *func(), uint32_t ssize)
{
	/* Place a few bytes of known values on the bottom of the stack. 
	This is just useful for debugging. */
	*stackpointer = 0x11;
	stackpointer--;
	*stackpointer = 0x22;
	stackpointer--;
	*stackpointer = 0x33;
	stackpointer--;
	/* Next simulate the stack as if after a call to portSAVE_CONTEXT().  
	portSAVE_CONTEXT places the flags on the stack immediately after r0
	to ensure the interrupts get disabled as soon as possible, and so ensuring
	the stack use is minimal should a context switch interrupt occur. */
	*stackpointer = ( uint8_t ) 0x00;	/* R0 */
	stackpointer--;
	*stackpointer = 0x80; /* SREG with global interrupt enable*/
	stackpointer--;


	/* Now the remaining registers.   The compiler expects R1 to be 0. */
	*stackpointer = ( uint8_t ) 0x00;	/* R1 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x02;	/* R2 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x03;	/* R3 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x04;	/* R4 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x05;	/* R5 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x06;	/* R6 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x07;	/* R7 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x08;	/* R8 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x09;	/* R9 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x10;	/* R10 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x11;	/* R11 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x12;	/* R12 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x13;	/* R13 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x14;	/* R14 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x15;	/* R15 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x16;	/* R16 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x17;	/* R17 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x18;	/* R18 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x19;	/* R19 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x20;	/* R20 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x21;	/* R21 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x22;	/* R22 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x23;	/* R23 */
	stackpointer--;

	*stackpointer = ( uint8_t ) 0x24;	/* R24 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x25;	/* R25 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x26;	/* R26 X */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x27;	/* R27 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x28;	/* R28 Y */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x29;	/* R29 */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x30;	/* R30 Z */
	stackpointer--;
	*stackpointer = ( uint8_t ) 0x031;	/* R31 */
	stackpointer--;
	return stackpointer;
}