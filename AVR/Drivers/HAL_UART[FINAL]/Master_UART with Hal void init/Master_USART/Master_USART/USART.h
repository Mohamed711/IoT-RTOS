/*
 * USART.h
 *
 * Created: 2/1/2016 2:13:01 AM
 *  Author: Mark
 */ 


#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
#include <stdint.h>
#include "HAL_UART.h"

volatile uint8_t value;

uint16_t comm_UART_Initialize(HAL_Comm_UART_ConfigStruct_t* usart_init_config);
uint16_t comm_UART_Send(unsigned char x);
uint16_t comm_UART_Receive(void *receiveChar);

#endif /* USART_H_ */