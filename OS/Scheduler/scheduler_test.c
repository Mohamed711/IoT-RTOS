
#include "TM4C123GH6PM.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef ARM
#include "E:/Keil/ARM/CMSIS/Include/core_cmFunc.h"
#endif 


#include "Process.h"
#include "queue.h"
#include "realTimeClock.h"
#include "Initialize.h"
#include "nullProcess.h"
#include "scheduler_test.h"
#include "../RTOS.h"

	extern uint32_t prcount;
	extern qid16 readylist;
	extern qid16 suspendedlist;
	extern qid16 sleepq;
	extern struct procent proctab[NPROC];	
	
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
	Scheduler_processTerminate(2);
}


void LED3()
{
		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 7);
		SysCtlDelay(20000000);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		Scheduler_processTerminate(3);
}*/
	
uint32_t getControl()
{
	return __get_CONTROL();
}
void setControl(uint32_t x)
{
	__set_CONTROL(x);
}
void set_MSP(uint32_t x)
{
	__set_MSP(x);
}

uint32_t get_MSP()
{
	return __get_MSP();
}
void set_PSP(uint32_t x)
{
	__set_PSP(x);
}
uint32_t get_PSP()
{
	return __get_PSP();
}

	/*
void SchedulerTest()
	{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	
	Uart_InitTypeDef initConf;	
	initializeUART(&initConf,UART0_BASE);
	
	Uart_HandleTypeDef transmit;
	transmit.init = initConf;

	prcount=0;
	readylist = newqueue();
	suspendedlist = newqueue();
	sleepq = newqueue();
	
	Scheduler_initializenullProcess();
	
	pid32 pidLED1= Scheduler_processCreate(LED1, 100, 5, "P1");//blue
	pid32 pidLED2= Scheduler_processCreate(LED2, 100, 10, "P2");	//red
	pid32 pidLED3= Scheduler_processCreate(LED3, 100, 7, "P3");	//purple

	Scheduler_insertd(pidLED1, sleepq, 50);
	Scheduler_insertd(pidLED2, sleepq, 2500);
	Scheduler_processSetReady(pidLED3);
	insert(0, readylist, 0);
	//Timer_New(clkhandler, 500);
	Scheduler_nullProc ();
}

*/