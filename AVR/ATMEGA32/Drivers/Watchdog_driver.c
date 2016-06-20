/*
 * Watchdog_driver.c
 *
 * Created: 18/6/2016 1:07:17 PM
 *  Author: Karen-pc
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "GPIO.h"
#include "Watchdog.h"
#include "HAL_Watchdog_AVR.h"
#include "Watchdog_cfg.h"
int main(void)
{
	/* Initially reset watchdog */ 
	HAL_Watchdog_Init();
	HAL_Watchdog_Reset();
	
	/****************************
	 Initialize Port B 
	 ****************************/ 
	GPIO_InitPortDirection(PB,0xF0,0xF0);
	GPIO_WritePort(PB, 0xF0,0x00);
	
	HAL_Watchdog_Enable(WDT_130MS);
	/* delay to detect reset */
	_delay_ms(20);	
	while(1)
	{
		GPIO_WritePort(PB,0xFF,0xF0);
		_delay_ms(9000);
		GPIO_WritePort(PB, 0x00,0xF0);
		_delay_ms(9000);
		HAL_Watchdog_Reset();
	}
}

