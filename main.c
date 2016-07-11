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
#include "OS/Scheduler/Initialize.h"
#include "tests.h"
#include "OS/IPC/ipc_test.h"
#include "OS/IPC/Shared_Memory.h"


int main(void) 
{
	
	uint16_t ReturnValue;
	Scheduler_initialize();
	
	#if  (TEST_USED == ARMScheduler_TEST )
		SchedulerTest();
	
	#elif (TEST_USED == IPC_MODULAR_TEST)
	
		if ( IPC_ModulerTest() == SUCCESS )
		{
			ReturnValue = SUCCESS;
		}
		else
		{
			ReturnValue = 0xFF;
		}
		
	#elif (TEST_USED == IPC_ASYNC_TEST)
	
		if ( IPC_Async_test() == SUCCESS )
		{
			ReturnValue = SUCCESS;
		}
		else
		{
			ReturnValue = 0xFF;
		}
		
	#elif (TEST_USED == IPC_SYNC_SEND_TEST)	
		IPC_u16Queue_Scenario_test();
		
	#elif (TEST_USED == IPC_SYNC_RECV_TEST)
		IPC_u16Queue_Scenario_test();
		
	#elif (TEST_USED == IPC_PAR_SEND_TEST)
	
		if ( IPC_u16Queue_Par_Send_test() == SUCCESS )
		{
			ReturnValue = SUCCESS;
		}
		else
		{
			ReturnValue = 0xFF;
		}
		
	#elif (TEST_USED == IPC_PAR_RECV_TEST)
	
		if ( IPC_u16Queue_Par_Recv_test() == SUCCESS )
		{
			ReturnValue = SUCCESS;
		}
		else
		{
			ReturnValue = 0xFF;
		}
	#elif (TEST_USED == AVR_ADC_TEST)
		adc_avr_test(void);
	#elif (TEST_USED == AVR_TIMER_TEST)
		timer_avr_test(void);
	#elif (TEST_USED == AVR_SPI_TEST)
		spi_avr_test();
	#elif (TEST_USED == AVR_I2C_TEST)
		i2c_avr_test(void);
	#elif (TEST_USED == AVR_UART_TEST)
		uart_avr_test(void);
		
	#elif (TEST_USED == SHARED_MEM_TEST)	
		SharedMem_test();
	#endif
		
		
		
	Scheduler_Start();
	
	return 0;
}
