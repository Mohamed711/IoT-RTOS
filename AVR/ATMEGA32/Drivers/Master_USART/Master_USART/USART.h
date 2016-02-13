/*
 * USART.h
 *
 * Created: 2/1/2016 2:13:01 AM
 *  Author: Mark
 */ 


#ifndef USART_H_
#define USART_H_
#include <avr/io.h>
#include "StdTypes.h"

volatile u8 value;

void usart_init(void);
void usart_transmit(unsigned char x);
unsigned char usart_receive(void);

#endif /* USART_H_ */