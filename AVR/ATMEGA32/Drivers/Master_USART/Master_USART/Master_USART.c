/*
 * Master_USART.c
 *
 * Created: 2/1/2016 12:19:18 PM
 *  Author: Mark
 */ 

#include <avr/io.h>
#include "USART.h"
#include "USART_CFG.h"

int main(void)
{
	usart_init();
    while(1)
    {
		usart_transmit('A');
    }
}