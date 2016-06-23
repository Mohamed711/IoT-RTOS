#include <stdint.h>
#include <stdbool.h>

#include "tivaHAL.h"
/*
int main()
{
	char *pcChars = "SSI Master send data.";


	SPI_InitTypeDef init;
	SPI_HandleTypeDef handle;

	init.ui32Base = SSI0_BASE;
	init.ui32SSIClk = SysCtlClockGet();
	init.ui32Protocol = SSI_FRF_MOTO_MODE_0;
	init.ui32BitRate = 2000000;
	init.ui32DataWidth = 8;

	handle.TxData = 0;
	spimasterinit(&init);

	char *str = "hello";
	int32_t i = 0;
	while(str[i])
	{
		handle.TxData = str[i];
		spimastersend(&handle);
		i++;
	}
}
*/
/*
int main()
{
	Uart_InitTypeDef initConf;
	initConf.BaudRate=115200;
	initConf.Parity= UART_CONFIG_PAR_NONE;
	initConf.Wlen=UART_CONFIG_WLEN_8;
	initConf.stopBit=UART_CONFIG_STOP_ONE;
	initConf.BaseAddress=UART0_BASE;
	initConf.clock=SysCtlClockGet();

	HAL_UART_Init(&initConf);

	initConf.BaseAddress=UART0_BASE;

	Uart_HandleTypeDef transmit;
	transmit.init = initConf;
	transmit.Tx='A';
	HAL_UART_Send(&transmit);
}
*/
//WATCHDOG TIMER TEST
/*
int main()
{
	WDT_HandleTypeDef handle;
	handle.watchdogBaseAddress = WATCHDOG0_BASE;
	handle.reloadValue = 0x01000000;
	handle.resetEnable = 1;
	handle.lock = 0;
	handle.stallEnable = 1;

	WDT_Init(&handle);
}*/

//ADC TEST
/*
int main()
{
	ADC_InitTypeDef handle;

	handle.ADCn = SYSCTL_PERIPH_ADC0;
	handle.seq = 1;
	handle.ADC_TRIGGER = ADC_TRIGGER_PROCESSOR;
	handle.prio = 0;
	handle.src = 0;
	HAL_ADC_Init(&handle);
	HAL_ADC_read(&handle);
}
*/

//TIMER TEST
/*
void IntFn()
{
	if(GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_2))
	{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
	}
	else
	{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
	}
}

/*
int main(void) {

	 SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

	 Timer_InitTypeDef timerInit;

	 Timer_HandleTypeDef  timerHandle;
	 timerHandle.timeInMillis=1000;
	 timerHandle.timeoutFn = IntFn;

	 timerinit(&timerInit);
	 //turns a led purple after 5 ms
	 timerstart(&timerHandle);

	while(1);
}
*/
/*
uint32_t j =0;
void firstFunction(void)
{

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 6);
}
uint32_t i;

void IntFn(void)
{
	i = 0x8;

}

int main(void)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		 GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

		 Timer_InitTypeDef timerInit;

		 	 Timer_HandleTypeDef  timerHandle;
		 	 timerHandle.timeInMillis=3000;
		 	 timerHandle.timeoutFn = IntFn;

		 	 HAL_TIMER_Init(&timerInit);
		 	 //turns a led purple after 5 ms
		 	// HAL_TIMER_Start(&timerHandle);

	i = 0x0;
	void(*pf)(void);
	while (1)
	{
		((void(*)(void))firstFunction)();
	}


	return 0;
}
*/
