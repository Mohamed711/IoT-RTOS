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
#include "nullProcess.h"
#include "Process.h"
#include "queue.h"
#include "reSched.h"
#include "scheduler_test.h"
#include "../../board/ARM/tivaHAL.h"
#include "../../board/ARM/drivers/inc/hw_gpio.h"	/*temp include*/
#include "../../board/ARM/drivers/inc/hw_ints.h"
#include "../../board/ARM/drivers/uart/uart.h"
#include "../../board/ARM/drivers/inc/hw_memmap.h"
#include "../../board/ARM/drivers/inc/hw_types.h"
#include "../../board/ARM/drivers/inc/tm4c123gh6pge.h"

extern unsigned int lrReg;
extern pid32 currpid;
extern uint32_t prcount;
extern struct procent proctab[NPROC];
extern qid16 readylist;

/*
void LED1()
{
		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
	while(1)
	{
		//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
		HWREG(GPIO_PORTF_BASE + (GPIO_O_DATA + (GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3) << 2)) = 8;
	}
}

void LED2()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	SysCtlDelay(20000000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	processTerminate(2);
}

void LED3()
{
		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
		SysCtlDelay(20000000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		processTerminate(3);
}


Uart_HandleTypeDef * uart;
int x =0;

pid32 pidLED1;
pid32 pidLED2;
pid32 pidLED3;

void uartInterrupt(void)
{		
			uint32_t * const LrAddr = (void*)(get_MSP()+0x28); //el address 
			lrReg = *LrAddr;
	
		//	if (currpid!=0)
		//	{
		//		proctab[currpid].returnValue = lrReg;
		//	}
	
		uint32_t ui32Status;
		ui32Status = uartIntStatus(UART0_BASE, true); //get interrupt status
		uartIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts

		while(uartCharsAvail(UART0_BASE))
		{
			x  = uartCharGetNonBlocking(uart->init.BaseAddress);
			uart->Tx =x;
			uartCharPutNonBlocking(uart->init.BaseAddress, x);
			switch(uart->Tx) 
			{
				case 0x31:
				case 0xC8:
					if (proctab[1].prstate != PR_READY && proctab[1].prstate != PR_CURR)
					{
						prcount++;
						proctab[1].prstate = PR_SUSP;
						processSetReady(pidLED1);
					}
				break;
				case 0x32:
				case 0xD8:
				case 0xC9:
					if (proctab[2].prstate != PR_READY && proctab[2].prstate != PR_CURR)
					{
						prcount++;
						proctab[2].prstate = PR_SUSP;
						processSetReady(pidLED2);
					}
				break;
				case 0x33:
				case 0xD9:
					if (proctab[3].prstate != PR_READY && proctab[3].prstate != PR_CURR)
					{
						prcount++;
						proctab[3].prstate = PR_SUSP;
						processSetReady(pidLED3);
					}
				break;
				case 0x34:
					processTerminate(1);
				break;
			}
		}
		*LrAddr = (uint32_t)nullProc;
}

bool flag = false;

void nullProc(Uart_HandleTypeDef * transmit)
{
	if (!flag)
	{
		pidLED1 = processCreate(LED1, 100, 5, "P1");//blue
		pidLED2 = processCreate(LED2, 100, 10, "P2");//blue
		pidLED3 = processCreate(LED3, 100, 7, "P3");//blue
		
		uart = transmit;
		
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		IntMasterEnable(); //enable processor interrupts
		uartIntRegister(transmit->init.BaseAddress, uartInterrupt);
		IntEnable(INT_UART0); //enable the UART interrupt
		uartIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
		flag = true;
	}
	
	while (1)
		{
				if (prcount !=0 && !isempty(readylist))
				{
					if (currpid != 0)
					{
						insert(currpid, readylist, proctab[currpid].prprio);
					}
					currpid = 0;
						reSched();
				}
	}
}*/

void nullProc()
{
	
	while (1)
		{
				if (prcount !=0)
				{
					if (currpid != 0)
					{
						insert(currpid, readylist, proctab[currpid].prprio);
					}
					currpid = 0;
						reSched();
				}
	}
}
