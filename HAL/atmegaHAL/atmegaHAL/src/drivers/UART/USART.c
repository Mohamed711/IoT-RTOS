/******************************************************************************
 *	OurOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *
 *  All rights reserved
 *
 *  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *****************************************************************************/
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
void uartInit(uint32_t Baud, uint8_t DataBits, uint8_t StopBits, uint8_t Parity, uint8_t EnableInterrupt, uint8_t U2X_State)
{
	uint16_t UBRR_VALUE;
	if(U2X_State != 0)	/*if Double speed state is enabled*/
	{
		UBRR_VALUE = (uint16_t)((F_CPU + Baud*4UL)/(Baud*8UL) - 1UL);
	}
	else	/*if Normal speed state is enabled*/
	{
		UBRR_VALUE = (uint16_t)((F_CPU + Baud*8UL)/(Baud*16UL) - 1UL);
	}

	UCSRC_REG = UBRR_SELECT;	/*URSEL is set to zero to update UBRRH*/
	UBRRL_REG = UBRR_VALUE;	
	UBRRH_REG = UBRR_VALUE >> 8;
	
	uartEnable();
	
	UCSRC_REG = UCSRC_SELECT;	/*URSEL is set to one to update the UCSRC settings*/
	UCSRC_REG |= DataBits | StopBits | Parity;
	
	UCSRA_REG |= U2X_State;
	
	if(EnableInterrupt)	/*if interrupt is enabled*/
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
