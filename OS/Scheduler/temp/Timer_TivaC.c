#include "../../RTOS.h"
#include "../../../board/ARM/drivers/timer/timer.h"
#include "../../../board/ARM/drivers/interrupt/interrupt.h"
#include "../../../board/ARM/drivers/sysctl/sysctl.h"
#include "../../../board/ARM/drivers/gpio/gpio.h"
#include "../../../board/ARM/drivers/inc/hw_types.h"
#include "../../../board/ARM/drivers/inc/hw_memmap.h"
#include "../../../board/ARM/drivers/inc/tm4c123gh6pge.h"


#include "../realTimeClock.h"
#include "../Process.h"
#include "../nullProcess.h"
#include "../scheduler_test.h"

volatile uint32_t millis=0;
volatile uint32_t max_millis;
volatile FnPtr function;
volatile bool delayFlag=false;
volatile uint32_t timeInMillis;

extern unsigned int lrReg;
extern pid32 currpid;
extern struct procent proctab[NPROC];

void ISR(void)
{
	uint32_t * const LrAddr = (void*)(get_MSP()+0x20); //el address 
	lrReg = *LrAddr;
	
	if (currpid!=0)
	{
		proctab[currpid].returnValue = lrReg;
	}
	
	TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
	function();
	
	//uint32_t getback = (uint32_t) nullProc;
		*LrAddr = (uint32_t)Scheduler_nullProc;
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

void Timer_New(FnPtr timeoutFn, uint32_t time)
{
		uint32_t ui32Period;
		function = timeoutFn;

		SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

		SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
		TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

	//	ui32Period = time * (SysCtlClockGet() / 10)/2 ;    //time in milliseconds

	ui32Period = time * 80000;
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
