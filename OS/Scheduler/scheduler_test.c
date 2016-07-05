

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "TM4C123GH6PM.h"

#ifdef ARM
#include "C:/Keil_v5/ARM/CMSIS/Include/core_cmFunc.h"
#endif 


#include "Process.h"
#include "queue.h"
#include "realTimeClock.h"
#include "Initialize.h"
#include "nullProcess.h"
#include "scheduler_test.h"
#include "../RTOS.h"

	extern uint32_t prcount;
	
void LED1()
{
		while(1)
	{
		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
	}
}

void LED2()
{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	SysCtlDelay(20000000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	Scheduler_unsleep(2);
}

void LED3()
{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 7);
	SysCtlDelay(20000000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	Scheduler_sleep(10);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 10);
	SysCtlDelay(20000000);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
}
	
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
	readyList = newqueue();
	suspendedList = newqueue();
	sleepingList = newqueue();
	
	Scheduler_initializenullProcess();
	
	Timer_New(Scheduler_clkhandler, 50000000);
	
	//pid32 pidLED1= Scheduler_processCreate(LED1, 400, 5, "P1");	//blue
	pid pidLED2= Scheduler_processCreate(LED2, 400, 10, "P2");	//red
	pid pidLED3= Scheduler_processCreate(LED3, 400, 15, "P3");	//purple

	//Scheduler_insertd(pidLED1, sleepq, 300);
	Scheduler_insertd(pidLED2, sleepingList, 1000);
	//processSetReady(pidLED2);
	Scheduler_processSetReady(pidLED3);
	//insert(0, readyList, 0);

	__set_PSP(__get_MSP()); // copy current stack pointer value into PSP
    __set_CONTROL(0x00000002); // switch to "process" stack pointer PSP
	
	Scheduler_nullProc();
}

