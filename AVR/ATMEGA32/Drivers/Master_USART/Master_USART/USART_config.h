/*
 * USART_config.h
 *
 * Created: 2/4/2016 2:49:13 PM
 *  Author: Mark
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#include "StdTypes.h"

typedef struct
{
	u32 Baud;
	u8 DataBits;
	u8 StopBits;
	u8 Parity;
	u8 EnableInterrupt;
	u8 U2X_State;
} USART_CONFIG;

extern const USART_CONFIG usart_init_config;

void uart_disable();
void uart_disable_rx();
void uart_disable_tx();
void uart_enable();
void uart_enable_rx();
void uart_enable_tx();
void uart_disable_interrupt();
void uart_enable_interrupt();
void uart_enable_interrupt_rx();

#endif /* USART_CONFIG_H_ */