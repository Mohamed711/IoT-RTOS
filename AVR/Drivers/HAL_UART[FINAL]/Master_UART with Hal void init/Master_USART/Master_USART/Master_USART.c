/*
 * Master_USART.c
 *
 * Created: 2/1/2016 12:19:18 PM
 *  Author: Mark
 */ 

#include <avr/io.h>
#include "HAL_UART.h"

HAL_Comm_UART_ConfigStruct_t uart_init_config;
HAL_Comm_UART_HandleTypeDefStruct_t uart_handle;

int main(void)
{
	uart_init_config.Baud = 9600;
	uart_init_config.DataBits = DATA_BIT_8;
	uart_init_config.StopBits = STOP_BIT_1;
	uart_init_config.Parity = PARITY_DISABLE;
	uart_init_config.EnableInterrupt = 0;
	uart_init_config.U2X_State = U2X_DISABLE;
	
	HAL_comm_UART_Initialize(&uart_init_config);
    while(1)
    {
		unsigned char x;
		HAL_comm_UART_Receive(&x);
		if (x == 'v')
		{
			uart_handle.transmit_char = 'T';
			HAL_comm_UART_Send(&uart_handle);	
		}
		else
		{
			uart_handle.transmit_char = 'F';
			HAL_comm_UART_Send(&uart_handle);
		}
	}
}