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
#include "USART_CFG.h"
#include "USART_config.h"

/************************************************************************
*	disable UART receiver and transmitter     
*
*	\return	none                                                                
************************************************************************/
void uartDisable()
{
	UCSRB_REG &= (0<<RXEN) | (0<<TXEN);	
}

/************************************************************************
*	disable UART receiver    
*
*	\return	none                                                                 
************************************************************************/
void uartDisableRx()
{
	UCSRB_REG &= (0<<RXEN);	
}

/************************************************************************
*	disable UART transmitter        
*
*	\return	none                                                             
************************************************************************/
void uartDisableTx()
{
	UCSRB_REG &= (0<<TXEN);	
}

/************************************************************************
* enable UART receiver and transmitter  
*
*	\return	none                                                                   
************************************************************************/
void uartEnable()
{
	UCSRB_REG |= (1<<RXEN) | (1<<TXEN);	
}

/************************************************************************
*	enable UART receiver 
*
*	\return	noe                                                                    
************************************************************************/
void uartEnableRx()
{
	UCSRB_REG |= (1<<RXEN);	
}

/************************************************************************
*	enable UART transmitter   
*
*	\return	none                                                                  
************************************************************************/
void uartEnableTx()
{
	UCSRB_REG |= (1<<TXEN);	
}

/************************************************************************
*	disable UART interrupts   
*
*	\return	none                                                                  
************************************************************************/
void uartDisableInterrupt()
{
	UCSRB_REG &= (0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE);
}

/************************************************************************
*	enable UART interrupts           
*
*	\return	none                                                          
************************************************************************/
void uartEnableInterrupt()
{
	UCSRB_REG |= (1<<RXCIE) | (1<<TXCIE) | (1<<UDRIE);
}

/************************************************************************
*	enable UART receive interrupts      
*	
*	\return	none                                                               
************************************************************************/
void uartEnableInterruptRx()
{
	UCSRB_REG |= (1<<RXCIE);
}

