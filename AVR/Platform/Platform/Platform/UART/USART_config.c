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

void uart_disable()
{
	/*disable UART receiver and transmitter*/
	UCSRB_REG &= (0<<RXEN) | (0<<TXEN);	
}

void uart_disable_rx()
{
	/*disable UART receiver*/
	UCSRB_REG &= (0<<RXEN);	
}

void uart_disable_tx()
{
	/*disable UART transmitter*/
	UCSRB_REG &= (0<<TXEN);	
}

/*********************************/

void uart_enable()
{
	/*enable UART receiver and transmitter*/
	UCSRB_REG |= (1<<RXEN) | (1<<TXEN);	
}

void uart_enable_rx()
{
	/*enable UART receiver*/
	UCSRB_REG |= (1<<RXEN);	
}

void uart_enable_tx()
{
	/*enable UART transmitter*/
	UCSRB_REG |= (1<<TXEN);	
}

/**********************************/

void uart_disable_interrupt()
{
	/*disable UART interrupts*/
	UCSRB_REG &= (0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE);
}

void uart_enable_interrupt()
{
	/*enable UART interrupts*/
	UCSRB_REG |= (1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE);
}

void uart_enable_interrupt_rx()
{
	UCSRB_REG |= (1<<RXCIE);
}
/***********************************/

