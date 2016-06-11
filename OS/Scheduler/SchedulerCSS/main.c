/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "drivers/inc/hw_memmap.h"
#include "drivers/inc/hw_types.h"
#include "drivers/sysctl/sysctl.h"
#include "drivers/gpio/gpio.h"

#include "headers.h"

void LED1()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
	SysCtlDelay(200000000);

	//processResumeAll();
	processTerminate(1);
}

void LED2()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 2);
	SysCtlDelay(200000000);

	processTerminate(2);
}

void LED3()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 7);
	SysCtlDelay(200000000);

	processTerminate(3);

}

int main(void) {
	readylist = newqueue();
	suspendedlist = newqueue();

	pid32 pidLED1 = processCreate(LED1, 100, 1, "lala");
	pid32 pidLED2 = processCreate(LED2, 100, 5, "ssaa");
	pid32 pidLED3 = processCreate(LED3, 100, 2, "ddda");
	//insert(pidLED1, readylist, proctab[pidLED1].prprio);
	//insert(pidLED2, readylist, proctab[pidLED2].prprio);
	//insert(pidLED3, readylist, proctab[pidLED3].prprio);

	//proctab[pidLED1].prstkptr = 0x080;
	//proctab[pidLED2].prstkptr = 0x100;
	processSetReady(pidLED1);
	//processSetReady(pidLED2);
	processSetReady(pidLED3);


	void(*pf)(void);

	clkinit();
	proctab[pidLED2].prstate = PR_SLEEP;
	//proctab[pidLED3].prstate = PR_SLEEP;
	insertd(pidLED2, sleepq ,200);
	//insertd(pidLED3, sleepq, 500);
	while(1)
	{
		//reSched();
		pf = proctab[currpid].processFunction;
		pf();
	}
	//return 0;
}
/*
int main(void) {

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

		 /*Timer_InitTypeDef timerInit;

		 Timer_HandleTypeDef  timerHandle1;
		 timerHandle1.timeInMillis=1000;
		 timerHandle1.timeoutFn = LED1;

		 Timer_HandleTypeDef  timerHandle2;
		 timerHandle2.timeInMillis=2000;
		 timerHandle2.timeoutFn = LED2;

		 Timer_HandleTypeDef  timerHandle3;
		 timerHandle3.timeInMillis=3000;
		 timerHandle3.timeoutFn = LED3;

		 HAL_Timer_Init(&timerInit);

		 HAL_Timer_Start(&timerHandle1);
		 HAL_Timer_Start(&timerHandle2);
		 HAL_Timer_Start(&timerHandle3);



	return 0;
}
*/
