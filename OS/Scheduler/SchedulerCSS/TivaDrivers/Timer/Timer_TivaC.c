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

volatile uint32_t millis=0;
volatile uint32_t max_millis;
volatile FnPtr function;
volatile bool delayFlag=false;

void ISR(void)
{
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	millis++;
	if(delayFlag==false)
	{
		if(millis==max_millis)
		{
			function();
			millis = 0;
		}
	}
}


/******************************************************************************
  *
  *	Initializes the timer
  *
  *	\takes no parameters
  *
  *	You have to call this function before using the timer
  *
  * \return none
  *
  *****************************************************************************/
void timerInit()
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

/******************************************************************************
  *
  *	Start the timer
  *
  *	\param timeInMillis is the time in miliseconds
  *	\param timeoutFn is the timeout function that executes when the time is out
  *
  *	This function takes a time in milliseconds and after this time is out it starts
  *	executing the function that timeoutFn points to
  *
  * \return none
  *
  *****************************************************************************/
void timerStart(uint32_t timeInMillis, FnPtr timeoutFn)
{
	delayFlag=false;
	millis=0;
	function = timeoutFn;
	max_millis=timeInMillis;
	TimerEnable(TIMER0_BASE, TIMER_A);
}

/******************************************************************************
  *
  *	Makes a delay
  *
  *	\param timeInMillis is the time in miliseconds
  *
  * \return none
  *
  *****************************************************************************/
void timerDelay(uint32_t timeInMillis)
{
	delayFlag=true;
	millis=0;
	max_millis=timeInMillis;
	TimerEnable(TIMER0_BASE, TIMER_A);
	while(millis<max_millis);
}

/******************************************************************************
  *
  *	Stops the timer
  *
  *	takes no parameters
  *
  * \return none
  *
  *****************************************************************************/
void timerStop()
{
	TimerDisable(TIMER0_BASE, TIMER_A);
}

