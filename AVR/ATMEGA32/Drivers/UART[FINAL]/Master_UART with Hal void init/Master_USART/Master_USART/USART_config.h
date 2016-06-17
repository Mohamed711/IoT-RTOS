/*
 * USART_config.h
 *
 * Created: 2/4/2016 2:49:13 PM
 *  Author: Mark
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#include <stdint.h>

#define F_CPU 8000000ul

typedef struct
{
	uint32_t Baud;
	uint8_t DataBits;
	uint8_t StopBits;
	uint8_t Parity;
	uint8_t EnableInterrupt;
	uint8_t U2X_State;
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