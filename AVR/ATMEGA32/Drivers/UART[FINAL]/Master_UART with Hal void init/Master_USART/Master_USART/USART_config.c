/*
 * USART_config.c
 *
 * Created: 2/4/2016 3:05:37 AM
 *  Author: Mark
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART_CFG.h"
#include "USART_config.h"

/************************************************************************
* Set the Baud Rate, number of data bits, number of stop bits,
* parity state, Interrupt state, speed state if normal or double speed                                                                      
************************************************************************/
const USART_CONFIG usart_init_config =
{
	9600,
	DATA_BIT_8,
	STOP_BIT_1,
	PARITY_DISABLE,
	1,
	U2X_DISABLE
};

/************************************************************************
* disable UART receiver and transmitter                                                                     
************************************************************************/
void uartDisable()
{
	UCSRB_REG &= (0<<RXEN) | (0<<TXEN);	
}

/************************************************************************
* disable UART receiver                                                                     
************************************************************************/
void uartDisableRx()
{
	UCSRB_REG &= (0<<RXEN);	
}

/************************************************************************
* disable UART transmitter                                                                     
************************************************************************/
void uartDisableTx()
{
	UCSRB_REG &= (0<<TXEN);	
}

/************************************************************************
* enable UART receiver and transmitter                                                                     
************************************************************************/
void uartEnable()
{
	UCSRB_REG |= (1<<RXEN) | (1<<TXEN);	
}

/************************************************************************
* enable UART receiver                                                                     
************************************************************************/
void uartEnableRx()
{
	UCSRB_REG |= (1<<RXEN);	
}

/************************************************************************
* enable UART transmitter                                                                     
************************************************************************/
void uartEnableTx()
{
	UCSRB_REG |= (1<<TXEN);	
}

/************************************************************************
* disable UART interrupts                                                                     
************************************************************************/
void uartDisableInterrupt()
{
	UCSRB_REG &= (0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE);
}

/************************************************************************
* enable UART interrupts                                                                     
************************************************************************/
void uartEnableInterrupt()
{
	UCSRB_REG |= (1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE);
}

/************************************************************************
* enable UART receive interrupts                                                                     
************************************************************************/
void uartEnableInterruptRx()
{
	UCSRB_REG |= (1<<RXCIE);
}

