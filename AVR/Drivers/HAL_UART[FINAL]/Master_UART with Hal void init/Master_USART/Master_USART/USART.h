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

void uartInit(UART_Config* usart_init_config);
void uartSend(unsigned char x);
unsigned char uartReceive(void);

#endif /* USART_H_ */