/*
 * USART_config.h
 *
 * Created: 2/4/2016 2:49:13 PM
 *  Author: Mark
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#include "StdTypes.h"

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