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

#define NO_TEST									0
#define ARMScheduler_TEST 			1
#define IPC_TEST								2
#define AVR_ADC_TEST						3
#define AVR_TIMER_TEST					4
#define AVR_SPI_TEST						5
#define AVR_I2C_TEST						6
#define AVR_UART_TEST						7
#define AVR_WATCHDOG_TEST				8


#define TEST_USED							IPC_TEST

int main(void) 
{
	uint16_t ReturnValue;
	#if  (TEST_USED == ARMScheduler_TEST )
		SchedulerTest();
	#elif (TEST_USED == IPC_TEST)
		if ( IPC_test() == SUCCESS )
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
	#elif (TEST_USED == AVR_WATCHDOG_TEST)
		
	#endif
	
	return 0;
}
