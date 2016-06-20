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

