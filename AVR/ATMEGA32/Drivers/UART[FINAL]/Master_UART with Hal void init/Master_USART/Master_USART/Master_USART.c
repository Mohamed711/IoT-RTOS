/*
 * Master_USART.c
 *
 * Created: 2/1/2016 12:19:18 PM
 *  Author: Mark
 */ 

#include <avr/io.h>
#include "HAL_UART.h"

int main(void)
{
	HAL_UART_Init();
    while(1)
    {
		unsigned char x;
		x = HAL_UART_Receive();
		if (x == 'v')
		{
			HAL_UART_Send('T');	
		}
		else
		{
			HAL_UART_Send('F');
		}
	}
}