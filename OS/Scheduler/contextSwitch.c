
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

#if 0	// this file is related to the board so its location must be changed to the board folder

extern void contextSwitch(char *oldStackPointer, char *newStackPointer)
{


	asm volatile (  "	push	{r0-r12, lr}		\n\t"		/* Push regs 0 - 12 and lr	*/
					"	push	{lr}				\n\t"			/* Push return address		*/
					"	mrs	r2, IAPSR	            \n\t"		/* Obtain status from coprocess, it must be psr but we can't access it*/
					"	push	{r2}				\n\t"			/*   and push onto stack	*/
				   "	str	sp, [r0]				\n\t"		/* Save old process's SP	*/
					"	ldr	sp, [r1]				\n\t"		/* Pick up new process's SP	*/
					"	pop	{r0}					\n\t"			/* Use status as argument and	*/
					"   msr IAPSR, r0               \n\t" /*it must be psr instead */
					"	pop	{lr}					\n\t"			/* Pick up the return address	*/
					"	pop	{r0-r12}				\n\t"		/* Restore other registers	*/
					"	mov	pc, lr 		     		\n\t"			/* Return to the new process	*/
			);

}


#endif





