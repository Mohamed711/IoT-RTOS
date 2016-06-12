/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
/*
#include "TivaDrivers/inc/hw_memmap.h"
#include "TivaDrivers/inc/hw_types.h"
#include "TivaDrivers/sysctl/sysctl.h"
#include "TivaDrivers/gpio/gpio.h"*/

#include "headers.h"
#include <avr/io.h>
#include <util/delay.h>
#include "AvrDrivers/Timer/HAL_Timer_AVR.h"
extern reSched();

/*void LED1()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 4);
	SysCtlDelay(40000000);

	//processResumeAll();
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

void LED4()
{
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	SysCtlDelay(40000000);

	processTerminate(4);

}*/

void LED1()
{
	DDRA = 0xFF;
	PORTA = 0xFF;
	_delay_ms(10000);
	PORTA = 0x00;
	processTerminate(1);
}

void LED2()
{
	DDRB = 0xFF;
	PORTB = 0xFF;
	_delay_ms(10000);
	PORTB = 0x00;
	processTerminate(2);
}

void LED3()
{
	DDRC = 0xFF;
	PORTC = 0xFF;
	_delay_ms(10000);
	PORTC = 0x00;
	processTerminate(3);
}



int main(void) {
	readylist = newqueue();
	suspendedlist = newqueue();

	pid32 pidLED1 = processCreate(LED1, 100, 1, "A");//blue
	pid32 pidLED2 = processCreate(LED2, 100, 5, "ssaa");	//red
	pid32 pidLED3 = processCreate(LED3, 100, 2, "ddda");	//purple
	//pid32 pidLED4 = processCreate(LED4, 100, 10, "fafa");	//no color

	//insert(pidLED1, readylist, proctab[pidLED1].prprio);
	//insert(pidLED2, readylist, proctab[pidLED2].prprio);
	//insert(pidLED3, readylist, proctab[pidLED3].prprio);

	//proctab[pidLED1].prstkptr = 0x080;
	//proctab[pidLED2].prstkptr = 0x100;

	processSetReady(pidLED1);
	//processSetReady(pidLED2);
	//processSetReady(pidLED3);
	//processSetReady(pidLED4);

	void(*pf)(void);

	clkinit();
	proctab[pidLED2].prstate = PR_SLEEP;
	proctab[pidLED3].prstate = PR_SLEEP;
	insertd(pidLED2, sleepq ,10);
	insertd(pidLED3, sleepq, 15);
	while(1)
	{
		//reSched();
		pf = proctab[currpid].processFunction;
		pf();
		//processTerminate(currpid);
	}
	return 0;
}