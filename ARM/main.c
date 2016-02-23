/*
 * main.c
 */

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/watchdog.h"
#include "inc/hw_memmap.h"

#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGCWD_R         (*((volatile unsigned long *)0x400FE600))


typedef enum {
	GPIO_TEST,
	TIMER_TEST,
	I2C_TEST,
	SPI_TEST,
	UART_TEST,
	ADC_TEST,
	AC_TEST,
	HIBERNATION_Module,
	WIFI_TEST,
	WATCHDOG_TIMER_TEST
}tests;

void PortF_Init(void);
void static delay(uint32_t x);

int main(void) {

	// Enable the buttons and the RGB Led
	PortF_Init();

	tests currentTest = GPIO_TEST ;
	uint32_t SW1,SW2;
	uint8_t firstEntryFlag = 0;

	while(1){
	    SW1 = GPIO_PORTF_DATA_R&0x10;     // read PF4 into SW1
	    SW2 = GPIO_PORTF_DATA_R&0x01;     // read PF0 into SW2

		///////////// GPIO TEST ////////////
		if (currentTest == GPIO_TEST)
		{
			if (SW1 == 0x00)
			{
				currentTest = TIMER_TEST;
			}
			else if (SW2 == 0x00)
			{
			      if  ((GPIO_PORTF_DATA_R&0x0E) == 0x00)
				  	  GPIO_PORTF_DATA_R = 0x04;       // LED is blue
			      else
			    	  GPIO_PORTF_DATA_R = 0x00;       // LED is blue
			}
		}
		///////////// timer test //////////////

		else if (currentTest == TIMER_TEST)
		{
			GPIO_PORTF_DATA_R = 0x02;
			// Make the led change its state each one second
			if (SW1 == 0x00)
			{
				currentTest = I2C_TEST;
			}
			else if (SW2 == 0x00)
			{
				// if this button is pushed
				// add one second to the time
			}
		}

		////////////// I2C Test /////////////////
		else if (currentTest == I2C_TEST)
		{
			GPIO_PORTF_DATA_R = 0x04;
			if (SW1 == 0x00)
			{
				currentTest = SPI_TEST;
			}
			// receive a character from the user
			// add one to the received character
			// send it again
		}

		//////////// SPI Test  ////////////////
		else if (currentTest == SPI_TEST)
		{
			GPIO_PORTF_DATA_R = 0x08;
			if (SW1 == 0x00)
			{
				currentTest = UART_TEST;
			}
			SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_0,
								SSI_MODE_SLAVE, 2000000, 8);
						SSIEnable(SSI0_BASE);
						// receive a character from the user
						uint32_t data;
						uint32_t *RxData;
						SSIDataGet(SSI0_BASE, RxData);

						// add one to the received character
						data = *RxData;
						data+=1;
						// send it again
						SSIDataPut(SSI0_BASE, data);
		}

		/////////// UART Test ////////////////
		else if (currentTest == UART_TEST)
		{
			GPIO_PORTF_DATA_R = 0x0A;
			if (SW1 == 0x00)
			{
				currentTest = ADC_TEST;
			}
			// receive a character from the user
			// add one to the received character
			// send it again
		}

		////////// ADC TEST  /////////////////
		else if (currentTest == ADC_TEST)
		{
			GPIO_PORTF_DATA_R = 0x0C;
			if (SW1 == 0x00)
			{
				currentTest = AC_TEST;
				continue;
			}
			float number;
			// read the value of the adc and send it with UART
		}
		/////////// AC Test   //////////////
		else if (currentTest == AC_TEST)
		{
			GPIO_PORTF_DATA_R = 0x0E;
			if (SW1 == 0x00)
			{
				currentTest = HIBERNATION_Module;
				continue;
			}
			float number;
			// read the value of the Analog comparator and send
			// it with UART

		}
		////////// hibernation test ////////
		else if (currentTest == HIBERNATION_Module)
		{
			GPIO_PORTF_DATA_R = 0x06;
			if (SW1 == 0x00)
			{
				currentTest = WIFI_TEST;
			}
			// shofy 7testeh ezay :D mtnsesh tshely el comment :D
		}
		//////////  Wifi TEST //////////////
		else if (currentTest == WIFI_TEST)
		{
			GPIO_PORTF_DATA_R = 0x02;

			if (SW1 == 0x00)
			{
				currentTest = WATCHDOG_TIMER_TEST;
			}
		}
		/////////  watchdog test ////////////
		else if (currentTest == WATCHDOG_TIMER_TEST)
		{
			GPIO_PORTF_DATA_R = 0x04;

			// delay then reset the Microcontroller
			if (firstEntryFlag == 0)
			{
				SYSCTL_RCGCWD_R |= 0x01;
				WatchdogReloadSet(WATCHDOG0_BASE,0x01000000);
				WatchdogResetEnable(WATCHDOG0_BASE);
				WatchdogEnable(WATCHDOG0_BASE);
				firstEntryFlag = 1;
			}
		}
		delay(300);
	 }

	return 0;
}

void PortF_Init(void){ volatile unsigned long delay;
  SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  delay = SYSCTL_RCGC2_R;           // delay
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0
}

void static delay(uint32_t x)
{
	uint32_t i,j;
	for (i = 0 ; i < x ; i++)
	{
		for (j = 0; j < 1000 ; j++)
		{
		}
	}
}
