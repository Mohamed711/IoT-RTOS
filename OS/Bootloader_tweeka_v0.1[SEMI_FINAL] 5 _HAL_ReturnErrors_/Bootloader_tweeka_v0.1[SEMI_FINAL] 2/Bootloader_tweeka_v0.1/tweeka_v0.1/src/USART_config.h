/*
 * USART_config.h
 *
 * Created: 2/4/2016 2:49:13 PM
 *  Author: Mark
 */ 


#ifndef USART_CONFIG_H_
#define USART_CONFIG_H_

#include <stdint.h>

uint16_t comm_UART_Disable();
uint16_t comm_UART_DisableRx();
uint16_t comm_UART_DisableTx();
uint16_t comm_UART_Enable();
uint16_t comm_UART_EnableRx();
uint16_t comm_UART_EnableTx();
uint16_t comm_UART_DisableInterrupt();
uint16_t comm_UART_EnableInterrupt();
uint16_t comm_UART_EnableInterruptRx();

#endif /* USART_CONFIG_H_ */