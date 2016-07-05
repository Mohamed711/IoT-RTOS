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
#include "return_Errors.h"

/************************************************************************
* disable UART receiver and transmitter
************************************************************************/
uint16_t comm_UART_Disable()
{
	UCSRB_REG &= (0<<RXEN) | (0<<TXEN);
	return SUCCESS;
}

/************************************************************************
* disable UART receiver
************************************************************************/
uint16_t comm_UART_DisableRx()
{
	UCSRB_REG &= (0<<RXEN);
	return SUCCESS;
}

/************************************************************************
* disable UART transmitter
************************************************************************/
uint16_t comm_UART_DisableTx()
{
	UCSRB_REG &= (0<<TXEN);
	return SUCCESS;
}

/************************************************************************
* enable UART receiver and transmitter
************************************************************************/
uint16_t comm_UART_Enable()
{
	UCSRB_REG |= (1<<RXEN) | (1<<TXEN);
	return SUCCESS;
}

/************************************************************************
* enable UART receiver
************************************************************************/
uint16_t comm_UART_EnableRx()
{
	UCSRB_REG |= (1<<RXEN);
	return SUCCESS;
}

/************************************************************************
* enable UART transmitter
************************************************************************/
uint16_t comm_UART_EnableTx()
{
	UCSRB_REG |= (1<<TXEN);
	return SUCCESS;
}

/************************************************************************
* disable UART interrupts
************************************************************************/
uint16_t comm_UART_DisableInterrupt()
{
	UCSRB_REG &= (0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE);
	return SUCCESS;
}

/************************************************************************
* enable UART interrupts
************************************************************************/
uint16_t comm_UART_EnableInterrupt()
{
	UCSRB_REG |= (1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE);
	return SUCCESS;
}

/************************************************************************
* enable UART receive interrupts
************************************************************************/
uint16_t comm_UART_EnableInterruptRx()
{
	UCSRB_REG |= (1<<RXCIE);
	return SUCCESS;
}

