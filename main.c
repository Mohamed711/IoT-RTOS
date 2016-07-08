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
#include "RTOS_Headers.h"
#include "OS/Scheduler/scheduler_test.h"
#include "OS/IPC/ipc_test.h"

#define ARMScheduler_TEST 	1
#define IPC_TEST			2
#define TEST_USED			0

int main(void) 
{
	uint16_t ReturnValue;
	#if  (TEST_USED == ARMScheduler_TEST )
		SchedulerTest();
	#elif (TEST_USED == IPC_TEST)
		if (IPC_test() == SUCCESS )
		{
			ReturnValue = SUCCESS;
		}
		else
		{
			ReturnValue = 0xFF;
		}
	#endif
	return 0;
}
