/*
 * HAL_UART.c
 *
 * Created: 2/20/2016 3:09:12 PM
 *  Author: Mark
 */ 

#include "HAL_UART.h"
#include "USART.h"

void HAL_UART_Init()
{
	usart_init();
}

void HAL_UART_Transmit(HAL_DataType transmit_char)
{
	usart_transmit(transmit_char);
}

HAL_DataType HAL_UART_Receive()
{
	return usart_receive();
}