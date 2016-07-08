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

#include <stdint.h>
#include <stdbool.h>

#include "tivaHAL.h"
#include "arm_drivers_test.h"

void i2c_arm_test()
{
	I2C_InitTypeDef in;
	in.baseAddress = I2C0_BASE;

	I2C_HandleTypeDef handle;
	handle.instance = in;
	handle.slaveAddress = 4;
	handle.Txdata = 'a';

	i2cmasterinit(&in);
	i2cmastersend(&handle);
}

void spi_arm_test()
{
	char *pcChars = "SSI Master send data.";


	SPI_InitTypeDef init;
	SPI_HandleTypeDef handle;

	init.ui32Base = SSI0_BASE;
	init.ui32SSIClk = SysCtlClockGet();
	init.ui32Protocol = SSI_FRF_MOTO_MODE_0;
	init.ui32BitRate = 2000000;
	init.ui32DataWidth = 8;

	handle.TxData = 0;
	spimasterinit(&init);

	char *str = "hello";
	int32_t i = 0;
	while(str[i])
	{
		handle.TxData = str[i];
		spimastersend(&handle);
		i++;
	}
}


void uart_arm_test()
{
	Uart_InitTypeDef initConf;
	initConf.BaudRate=115200;
	initConf.Parity= UART_CONFIG_PAR_NONE;
	initConf.Wlen=UART_CONFIG_WLEN_8;
	initConf.stopBit=UART_CONFIG_STOP_ONE;
	initConf.BaseAddress=UART0_BASE;
	initConf.clock=SysCtlClockGet();

	uartinit(&initConf);

	initConf.BaseAddress=UART0_BASE;

	Uart_HandleTypeDef transmit;
	transmit.init = initConf;
	transmit.Tx='A';
	uartsend(&transmit);
}

//WATCHDOG TIMER TEST

void watchdog_arm_test()
{
	WDT_InitTypeDef handle;
	handle.watchdogBaseAddress = WATCHDOG0_BASE;
	handle.reloadValue = 0x01000000;
	handle.resetEnable = 1;
	handle.lock = 0;
	handle.stallEnable = 1;

	WDT_Init(&handle);
}

//ADC TEST

void adc_arm_test()
{
	ADC_InitTypeDef handle;

	handle.ADCn = SYSCTL_PERIPH_ADC0;
	handle.seq = 1;
//	handle.ADC_TRIGGER = ADC_TRIGGER_PROCESSOR;
	handle.prio = 0;
	handle.src = 0;
	ADC_Init(&handle);
	ADC_Read(&handle);
}


//TIMER TEST

void IntFn()
{
	if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
	{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	}
	else
	{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
	}
}


void timer_arm_test(void) {

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	 Timer_InitTypeDef timerInit;

	 Timer_HandleTypeDef  timerHandle;
	 timerHandle.timeInMillis=1000;
	 timerHandle.timeoutFn = IntFn;

	 timerinit(&timerInit);
	 //turns a led purple after 5 ms
	 timerstart(&timerHandle);

	while(1);
}


uint32_t j =0;
void firstFunction(void)
{

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
}
uint32_t i;

/*
void IntFn(void)
{
	i = 0x8;

}
*/
void timer_2_main_test(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

		 Timer_InitTypeDef timerInit;

		 	 Timer_HandleTypeDef  timerHandle;
		 	 timerHandle.timeInMillis=3000;
		 	 timerHandle.timeoutFn = IntFn;

		 	 timerinit(&timerInit);
		 	 //turns a led purple after 5 ms
		 	// HAL_TIMER_Start(&timerHandle);

	i = 0x0;
	void(*pf)(void);
	while (1)
	{
		((void(*)(void))firstFunction)();
	}

}

