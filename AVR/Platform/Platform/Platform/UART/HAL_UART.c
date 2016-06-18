/*
 * HAL_UART.c
 *
 * Created: 2/20/2016 3:09:12 PM
 *  Author: Mark
 */ 

#include "HAL_UART.h"
#include "USART.h"

void HAL_UART_Init(USART_CONFIG* HAL_usart_init_config)
{
	usart_init(HAL_usart_init_config);
}

void HAL_UART_Transmit(UART_HandleTypeDef* HAL_transmit_char)
{
	usart_transmit(HAL_transmit_char->transmit_char);
}

HAL_DataType HAL_UART_Receive()
{
	return usart_receive();
}