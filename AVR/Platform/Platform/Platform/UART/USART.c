/*
 * USART.c
 *
 * Created: 2/1/2016 1:53:09 AM
 *  Author: Mark
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "StdTypes.h"
#include "USART_CFG.h"
#include "USART_config.h"
#include "DIO.h"
#include "HAL_UART.h"
#include <util/delay.h>

//#define USART_BAUDRATE 115200
//#define UBRR_VALUE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void usart_init(USART_CONFIG* usart_init_config)
{
	/*Baud Rate*/
	//u16 UBRR_VALUE = ((F_CPU)/(Baud*16UL)-1);
	u16 UBRR_VALUE;
	if(usart_init_config->U2X_State != 0)
	{
		UBRR_VALUE = (u16)((F_CPU + usart_init_config->Baud*4UL)/(usart_init_config->Baud*8UL) - 1UL);
	}
	else
	{
		UBRR_VALUE = (u16)((F_CPU + usart_init_config->Baud*8UL)/(usart_init_config->Baud*16UL) - 1UL);
	}
	
	UCSRC_REG = UBRR_SELECT;
	UBRRL_REG = UBRR_VALUE;	
	UBRRH_REG = UBRR_VALUE >> 8;
	
	uart_enable();
	
	UCSRC_REG = UCSRC_SELECT;
	UCSRC_REG |= usart_init_config->DataBits | usart_init_config->StopBits | usart_init_config->Parity;
	
	UCSRA_REG |= usart_init_config->U2X_State;
	
	if(usart_init_config->EnableInterrupt)
	{
		cli();
		uart_enable_interrupt_rx();
		sei();
	}		
}

void usart_transmit(unsigned char x)
{
	while (!(UCSRA_REG & UDR_ENABLE));	/*wait until the transmit buffer is empty and ready to be written*/
	UDR_REG = x;	//put data into the buffer
}

unsigned char usart_receive(void)
{
	while (!(UCSRA_REG & RXC_RECEIVE_COMPLETE));
	return UDR;
}

 ISR(USART_RXC_vect)
{
	volatile unsigned char value;
	value = UDR_REG;
	DIO_WritePort(PC, value, 0xFF);
	_delay_ms(100);
	usart_transmit(value);
}
