#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "../../board/ARM/drivers/inc/hw_memmap.h"
#include "../../board/ARM/drivers/inc/hw_types.h"
#include "../../board/ARM/drivers/sysctl/sysctl.h"
#include "../../board/ARM/drivers/gpio/gpio.h"
#include "Process.h"
#include "../RTOS.h"
extern pid32 currpid;
extern struct procent proctab[NPROC];		  /* table of processes */
extern qid16 readylist;
extern qid16 suspendedlist;


void LED1()
{

	
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
	SysCtlDelay(40000000);
	processTerminate(1);

}

void LED2()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	SysCtlDelay(40000000);
	processTerminate(2);
	
}

void LED3()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 7);
	SysCtlDelay(40000000);
	processTerminate(3);
	
}
void nullProc()
{
	//just testing that it will be the first process to start and the last process to end in the scheduler.
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	SysCtlDelay(40000000);
	
}


void scheduler_test() {

	readylist = newqueue();
	suspendedlist = newqueue();
	proctab[0].processFunction = nullProc;
	proctab[0].prstate = PR_CURR;
	proctab[0].prprio = 0;
	strncpy(proctab[0].prname, "prnull", 7);
	proctab[0].prstkbase = pvPortMalloc(100);  
	proctab[0].prstklen = NULLSTK;
	proctab[0].prstkptr = 0;
	currpid = NULLPROC;
	
	pid32 pidLED1= processCreate(LED1, 100, 10, "P1");//blue
	pid32 pidLED2= processCreate(LED2, 100, 5, "P2");	//red
	pid32 pidLED3= processCreate(LED3, 100, 2, "P3");	//purple

	insert(pidLED1, readylist, proctab[pidLED1].prprio);
	insert(pidLED2, readylist, proctab[pidLED2].prprio);
	insert(pidLED3, readylist, proctab[pidLED3].prprio);
	clkinit();
	while(1)
	{
		//keep calling current process function.
		void(*pf)(void);
		pf = proctab[currpid].processFunction;
		pf();
	}
}
