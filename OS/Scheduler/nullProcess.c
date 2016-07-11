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
#include "../RTOS.h"
#include "initialize.h"
	
 


extern unsigned int lrReg;
extern pid currpid;
extern uint32_t prcount;
extern struct procent proctab[NPROC];
extern qid readyList;


void LED1()
{	
		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
		while (1)
		{
			HWREG(GPIO_PORTF_BASE + (GPIO_O_DATA + (GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3) << 2)) = 4;
	//	SysCtlDelay(20000000);
		//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	}
}

void LED2()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	SysCtlDelay(10000000);
	Scheduler_sleepms(2000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 8);
	SysCtlDelay(10000000);

}

void LED3()
{
		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
		SysCtlDelay(20000000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 14);
		SysCtlDelay(20000000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
}


Uart_HandleTypeDef * uart;
int x =0;

pid pidLED1;
pid pidLED2;
pid pidLED3;

bool flag = true;
bool wakefromSleep = true;	
#define THREAD_RETURN 0xFFFFFFFD //Tells the handler to return using the PSP

void UART0_Handler(void)
{		
		if (proctab[currpid].prstate != PR_FREE)
		{
			saveContext(proctab[currpid].prstkptr);
			proctab[currpid].prstkptr = (void*)get_PSP();
		}
		uint32_t* mainStk = (void*)get_MSP();
		
		uint32_t ui32Status;
		ui32Status = uartIntStatus(UART0_BASE, true); //get interrupt status
		uartIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts

		while(uartCharsAvail(UART0_BASE))
		{
			//x  = uartCharGetNonBlocking(uart->init.BaseAddress);
			x  = uartCharGetNonBlocking(UART0_BASE);
			//uart->Tx =x;
			//uartCharPutNonBlocking(uart->init.BaseAddress, x);
			uartCharPutNonBlocking(UART0_BASE, x);
			//switch(uart->Tx) 
			switch(x) 
			{
				case 0x31:
				case 0xC8:
				case 0xE8:
				case 0xF2:
					if (proctab[1].prstate != PR_READY && proctab[1].prstate != PR_CURR)
					{
						//prcount++;
						//proctab[1].prstate = PR_SUSP;
						pidLED1 = Scheduler_processCreate(LED1, 100, 5, "P1");
						Scheduler_processSetReady(pidLED1);
						//wakefromSleep = false ;
						//IntTrigger(INT_TIMER0A);
					}
				break;
				case 0x32:
				case 0xD8:
				case 0xC9:
				case 0xE9:
					if (proctab[2].prstate != PR_READY && proctab[2].prstate != PR_CURR)
					{
						//prcount++;
						//proctab[2].prstate = PR_SUSP;
						pidLED2 = Scheduler_processCreate(LED2, 100, 10, "P2");
						Scheduler_processSetReady(pidLED2);
						//wakefromSleep = false ;
					  //IntTrigger(INT_TIMER0A);
					}
				break;
				case 0x33:
				case 0xD9:
				case 0xEA:
				case 0xFB:
				case 0xED:
					if (proctab[3].prstate != PR_READY && proctab[3].prstate != PR_CURR)
					{
						//prcount++;
						//proctab[3].prstate = PR_SUSP;
						pidLED3 = Scheduler_processCreate(LED3, 100, 7, "P3");
						Scheduler_processSetReady(pidLED3);
						//wakefromSleep = false ;
						//IntTrigger(INT_TIMER0A);
					}
				break;
				}
			pid nwPiD = Scheduler_reSchedule();
	
			*((uint32_t*)mainStk) = THREAD_RETURN;
			set_PSP((uint32_t)proctab[nwPiD].prstkptr);
			loadContext(proctab[nwPiD].prstkptr);
		}
}



void Scheduler_nullProc(Uart_HandleTypeDef *transmit)
{
	if (flag)
	{
		set_PSP((uint32_t)proctab[0].prstkptr);
		loadContext(proctab[0].prstkptr);
		//pidLED1 = Scheduler_processCreate(LED1, 100, 5, "P1");//blue
		//pidLED2 = Scheduler_processCreate(LED2, 100, 10, "P2");//red
		//pidLED3 = Scheduler_processCreate(LED3, 100, 7, "P3");//purple
		
		uart = transmit;
		
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		IntMasterEnable(); //enable processor interrupts
		//uartIntRegister(transmit->init.BaseAddress, uartInterrupt);
		IntEnable(INT_UART0); //enable the UART interrupt
		uartIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
		flag = false;
	}
	while (1)
		{
				if (prcount !=0)
				{
					if (!isEmpty(readyList))
						{
							wakefromSleep = false ;
							IntTrigger(INT_TIMER0A);
						}
				}
	}
}


void Scheduler_Start()
{
	__set_PSP(__get_MSP()); // copy current stack pointer value into PSP
  __set_CONTROL(0x00000002); // switch to "process" stack pointer PSP
	
	Scheduler_nullProc(&transmit);
	
}


