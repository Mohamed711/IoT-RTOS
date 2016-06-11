
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

#include "headers.h"


#define ARM_Context()


void contextSwitch(char *oldStackPointer, char *newStackPointer)
{
#ifdef ARM
	asm volatile (  "	push	{r0-r11, lr}		\n\t"		/* Push regs 0 - 11 and lr	*/
					"	push	{lr}				\n\t"			/* Push return address		*/
					//"	mrs	r2, cpac				\n\t"		/* Obtain status from coprocess.*/
					"	push	{r2}				\n\t"			/*   and push onto stack	*/
					"	str	sp, [r0]				\n\t"		/* Save old process's SP	*/
					"	ldr	sp, [r1]				\n\t"		/* Pick up new process's SP	*/
					"	pop	{r0}					\n\t"			/* Use status as argument and	*/
					//"	bl	newStackPointer			\n\t"			/*   call restore to restore it	*/
					"	pop	{lr}					\n\t"			/* Pick up the return address	*/
					"	pop	{r0-r12}				\n\t"		/* Restore other registers	*/
					"	mov	pc, r12					\n\t"			/* Return to the new process	*/
			);
#else
	asm volatile (	"lds	r26, oldStackPointer		\n\t"	\
					"lds	r27, oldStackPointer + 1	\n\t"	\
					"ld		r28, x+						\n\t"	\
					"out	__SP_L__, r28				\n\t"	\
					"ld		r29, x+						\n\t"	\
					"out	__SP_H__, r29				\n\t"	\
					"pop	r31							\n\t"	\
					"pop	r30							\n\t"	\
					"pop	r29							\n\t"	\
					"pop	r28							\n\t"	\
					"pop	r27							\n\t"	\
					"pop	r26							\n\t"	\
					"pop	r25							\n\t"	\
					"pop	r24							\n\t"	\
					"pop	r23							\n\t"	\
					"pop	r22							\n\t"	\
					"pop	r21							\n\t"	\
					"pop	r20							\n\t"	\
					"pop	r19							\n\t"	\
					"pop	r18							\n\t"	\
					"pop	r17							\n\t"	\
					"pop	r16							\n\t"	\
					"pop	r15							\n\t"	\
					"pop	r14							\n\t"	\
					"pop	r13							\n\t"	\
					"pop	r12							\n\t"	\
					"pop	r11							\n\t"	\
					"pop	r10							\n\t"	\
					"pop	r9							\n\t"	\
					"pop	r8							\n\t"	\
					"pop	r7							\n\t"	\
					"pop	r6							\n\t"	\
					"pop	r5							\n\t"	\
					"pop	r4							\n\t"	\
					"pop	r3							\n\t"	\
					"pop	r2							\n\t"	\
					"pop	r1							\n\t"	\
					"pop	r0							\n\t"	\
					"out	__SREG__, r0				\n\t"	\
					"pop	r0							\n\t"	\
				);
#endif
}
