/*
 * USART.c
 *
 * Created: 2/1/2016 1:53:09 AM
 *  Author: Mark
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#include <stdint.h>
#include <stdbool.h>
#include <avr/delay.h>
#include "USART_config.h"


/************************************************************************
*	Set the Baud Rate value.
*
*	Enable Uart by enabling receive bit(Rx) and transmit bit(Tx).
*
*	Set the number of data bits, stop bits, and parity bits.
*
*	Set the speed mode if Normal speed or Double speed.
*
*	Enable interrupts           
*
*	return	\none                                                         
************************************************************************/
void uartInit(UART_InitTypeDef* usart_init_config)
{
	uint16_t UBRR_VALUE;
	if(usart_init_config->U2X_State != 0)	/*if Double speed state is enabled*/
	{
		UBRR_VALUE = (uint16_t)((F_CPU + usart_init_config->Baud*4UL)/(usart_init_config->Baud*8UL) - 1UL);
	}
	else	/*if Normal speed state is enabled*/
	{
		UBRR_VALUE = (uint16_t)((F_CPU + usart_init_config->Baud*8UL)/(usart_init_config->Baud*16UL) - 1UL);
	}

	UCSRC_REG = UBRR_SELECT;	/*URSEL is set to zero to update UBRRH*/
	UBRRL_REG = UBRR_VALUE;	
	UBRRH_REG = UBRR_VALUE >> 8;
	
	uartEnable();
	
	UCSRC_REG = UCSRC_SELECT;	/*URSEL is set to one to update the UCSRC settings*/
	UCSRC_REG |= usart_init_config->DataBits | usart_init_config->StopBits | usart_init_config->Parity;
	
	UCSRA_REG |= usart_init_config->U2X_State;
	
	if(usart_init_config->EnableInterrupt)	/*if interrupt is enabled*/
	{
		cli();
		uartEnableInterruptRx();	/*enable receive interrupt*/
		sei();
	}		
}

/************************************************************************
*	 Put data into the UDR buffer to be sent        
*
*	\param	x	data needed to be sent
*
*	\return	none                                                          
************************************************************************/
void uartSend(unsigned char x)
{
	while (!(UCSRA_REG & UDR_ENABLE));	/*wait until the transmit buffer is empty and ready to be written*/
	UDR_REG = x;	/*put data into the buffer*/
}

/************************************************************************
*	Return data found in the UDR buffer     
*
*	return	received data                                                                
************************************************************************/
unsigned char uartReceive(void)
{
	while (!(UCSRA_REG & RXC_RECEIVE_COMPLETE));	/*wait until the receive is finished and the buffer is written*/
	return UDR;
}

/************************************************************************
*	if interrupt happens (byte is received), write data in UDR_REG on port C, delay 0.1 sec,
*	then send the same data again
************************************************************************/
 ISR(USART_RXC_vect)
{
	volatile unsigned char value;
	value = UDR_REG;
	_delay_ms(100);
	uartSend(value);	/*just echo the data received*/
}
