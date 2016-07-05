/*
 * USART.c
 *
 * Created: 2/1/2016 1:53:09 AM
 *  Author: Mark
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USART.h"
#include "USART_CFG.h"
#include "USART_config.h"
#include "HAL_UART.h"
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>
#include "return_Errors.h"

/************************************************************************
* Set the Baud Rate value.
*
* Enable Uart by enabling receive bit(Rx) and transmit bit(Tx).
*
* Set the number of data bits, stop bits, and parity bits.
*
* Set the speed mode if Normal speed or Double speed.
*
* Enable interrupts                                                                    
************************************************************************/
uint16_t comm_UART_Initialize(HAL_Comm_UART_ConfigStruct_t* usart_init_config)
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
	
	comm_UART_Enable();
	
	/*URSEL is set to one to update the UCSRC settings*/
	UCSRC_REG |= UCSRC_SELECT | usart_init_config->DataBits | usart_init_config->StopBits | usart_init_config->Parity;
	
	UCSRA_REG |= usart_init_config->U2X_State;
	
	if(usart_init_config->EnableInterrupt)	/*if interrupt is enabled*/
	{
		cli();
		comm_UART_EnableInterruptRx();	/*enable receive interrupt*/
		sei();
	}
	return SUCCESS;	
}

/************************************************************************
* Put data into the UDR buffer to be sent                                                                  
************************************************************************/
uint16_t comm_UART_Send(unsigned char x)
{
	while (!(UCSRA_REG & UDR_ENABLE));	/*wait until the transmit buffer is empty and ready to be written*/
	UDR_REG = x;	/*put data into the buffer*/
	return SUCCESS;
}

/************************************************************************
* Return data found in the UDR buffer                                                                     
************************************************************************/
uint16_t comm_UART_Receive(void *receiveChar)
{
	uint16_t dataReg;
	
	while (!(UCSRA_REG & RXC_RECEIVE_COMPLETE));	/*wait until the receive is finished and the buffer is written*/
	dataReg = UDR_REG;
	*(uint16_t *) receiveChar = dataReg;
	return SUCCESS;
}

/************************************************************************
* if interrupt happens (byte is received), write data in UDR_REG on port C, delay 0.1 sec,
* then send the same data again
************************************************************************/
 ISR(USART_RXC_vect)
{
	volatile unsigned char value;
	value = UDR_REG;
	_delay_ms(100);
	comm_UART_Send(value);	/*just echo the data received*/
}
