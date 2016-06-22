
#include <stdint.h>
#include <stdbool.h>
#include "../inc/hw_memmap.h"
#include "../inc/hw_types.h"
#include "../gpio/gpio.h"
#include "../pin_map/pin_map.h"
#include "../sysctl/sysctl.h"
#include "../inc/hw_ints.h"
#include "../interrupt/interrupt.h"
#include "uart.h"

/******************************************************************************
*
*	The function's purpose is to initialize the i2c UART
*
*	\param baseAddress		 the base address of the needed uart
*
* 	\return none
*
*****************************************************************************/
void initialize (uint32_t ui32Base)
{
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

	if(ui32Base==UART0_BASE)
		{

		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
		GPIOPinConfigure(GPIO_PA0_U0RX);
		GPIOPinConfigure(GPIO_PA1_U0TX);
		GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
		}
	else if (ui32Base==UART1_BASE)
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
		GPIOPinConfigure(GPIO_PB0_U1RX);
		GPIOPinConfigure(GPIO_PB1_U1TX);
		GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	}
	else if(ui32Base==UART2_BASE)
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		GPIOPinConfigure(GPIO_PD6_U2RX );
		GPIOPinConfigure(GPIO_PD7_U2TX);
		GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
	}

	else if (ui32Base==UART3_BASE)
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART3);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
		GPIOPinConfigure(GPIO_PC6_U3RX );
		GPIOPinConfigure(GPIO_PC7_U3TX);
		GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_6 | GPIO_PIN_7);

	}

	else if (ui32Base==UART4_BASE)
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART4);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
		GPIOPinConfigure(GPIO_PC4_U4RX );
		GPIOPinConfigure(GPIO_PC5_U4TX);
		GPIOPinTypeUART(GPIO_PORTC_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	}

	else if (ui32Base==UART5_BASE)
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		GPIOPinConfigure(GPIO_PE4_U5RX );
		GPIOPinConfigure(GPIO_PE5_U5TX);
		GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	}
	else if (ui32Base==UART6_BASE)
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART6);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
		GPIOPinConfigure(GPIO_PD4_U6RX );
		GPIOPinConfigure(GPIO_PD5_U6TX);
		GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5);
	}
	else if (ui32Base==UART7_BASE)
	{
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART7);
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
		GPIOPinConfigure(GPIO_PE0_U7RX );
		GPIOPinConfigure(GPIO_PE1_U7TX);
		GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	}
}

/******************************************************************************
*
*	The function's purpose is to send a char using the uart
*
*	\param baseAddress			the base address of the needed uart
*	\param cData				the data needed to be sent
*
* 	\return none
*
*****************************************************************************/
void uartSend(uint32_t ui32Base, unsigned char ucData)
{
	uartCharPut( ui32Base , ucData);
}

/******************************************************************************
*
*	The function's purpose is to receive a char using the uart
*
*	\param baseAddress		the base address of the needed uart
*
* 	\return the received character
*
*****************************************************************************/
int32_t uartReceive(uint32_t ui32Base)
{
	return (uartCharGet( ui32Base));
}
