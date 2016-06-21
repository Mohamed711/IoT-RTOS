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

void uartInit(uint32_t Baud, uint8_t DataBits, uint8_t StopBits, uint8_t Parity, uint8_t EnableInterrupt, uint8_t U2X_State);
void uartSend(unsigned char x);
unsigned char uartReceive(void);

#endif /* USART_H_ */