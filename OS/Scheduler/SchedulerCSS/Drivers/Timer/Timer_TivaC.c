#include <stdint.h>
#include <stdbool.h>
#include "../inc/tm4c123gh6pge.h"
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../sysctl/sysctl.h"
#include "../interrupt/interrupt.h"
#include "../gpio/gpio.h"
#include "timer.h"
#include "Timer_TivaC.h"



/*static const uint32_t basePeriphMap[][2] =
{
    { TIMER0_BASE, SYSCTL_PERIPH_TIMER0 },
    { TIMER1_BASE, SYSCTL_PERIPH_TIMER1 },
    { TIMER2_BASE, SYSCTL_PERIPH_TIMER2 },
    { TIMER3_BASE, SYSCTL_PERIPH_TIMER3 },
    { TIMER4_BASE, SYSCTL_PERIPH_TIMER4 },
    { TIMER5_BASE, SYSCTL_PERIPH_TIMER5 },
    { WTIMER0_BASE, SYSCTL_PERIPH_WTIMER0 },
    { WTIMER1_BASE, SYSCTL_PERIPH_WTIMER1 },
    { WTIMER2_BASE, SYSCTL_PERIPH_WTIMER2 },
    { WTIMER3_BASE, SYSCTL_PERIPH_WTIMER3 },
    { WTIMER4_BASE, SYSCTL_PERIPH_WTIMER4 },
    { WTIMER5_BASE, SYSCTL_PERIPH_WTIMER5 },
};

static const uint_fast8_t basePeriphMapRows =
    sizeof(basePeriphMap) / sizeof(basePeriphMap[0]);  */

volatile uint32_t millis=0;
volatile uint32_t max_millis;
volatile FnPtr function;
volatile bool delayFlag=false;
volatile uint32_t timeInMillis;
void ISR(void)
{
	// Clear the timer interrupt
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	function();

	/*millis++;
	if(millis==max_millis)
		{
		Timer0IntHandler();
			//Timer_Start(timeInMillis, function);

		}*/
	//timer=TimerValueGet(TIMER1_BASE,TIMER_A);

	    // Reset the counter value to 10000
	//TimerLoadSet(TIMER0_BASE, TIMER_A,10000);
	//TimerLoadSet(TIMER0_BASE, TIMER_A, 10000);
	//Timer_Start(timeInMillis, function);

}

void Timer_Init()
{

	uint32_t period=40000;
	SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
	TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
	TimerLoadSet(TIMER0_BASE, TIMER_A, period-1);
	TimerIntRegister(TIMER0_BASE, TIMER_A, ISR);
	IntEnable(INT_TIMER0A);
	TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	IntMasterEnable();

}

void Timer_Start(uint32_t timeInMillis, FnPtr timeoutFn)
{
	delayFlag=false;
	millis=0;
	function = timeoutFn;
	max_millis=timeInMillis;
	TimerEnable(TIMER0_BASE, TIMER_A);
	//while(millis<max_millis);
}
void Timer_Delay(uint32_t timeInMillis)
{
	delayFlag=true;
	millis=0;
	max_millis=timeInMillis;
	TimerEnable(TIMER0_BASE, TIMER_A);
	while(millis<max_millis);
}

void Timer_Stop()
{
	TimerDisable(TIMER0_BASE, TIMER_A);
}

void Timer_New(FnPtr timeoutFn)
{
		uint32_t ui32Period;
		function = timeoutFn;

		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
		TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

		ui32Period = (SysCtlClockGet() / 10)/2;    //100 milliseconds

		TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);
		TimerIntRegister(TIMER0_BASE, TIMER_A, ISR);
		IntEnable(INT_TIMER0A);
		TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
		IntMasterEnable();
		TimerEnable(TIMER0_BASE, TIMER_A);

}

void Timer0IntHandler(void)
	{

		// Read the current state of the GPIO pin and
		// write back the opposite state
		if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
		{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
		}
		else
		{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 4);
		}
	}
