/*
 * I2C.c
 *
 * Created: 2/4/2016 2:00:25 PM
 *  Author: sameh
 */ 


#include <avr/io.h>
#include "I2C.h"
#include <util/delay.h>
//#include "I2C_CONFIG.h"

/*WORKING BUT WITHOUT OPTIMIZATION IN ANYTHING*/
int main(void)
{
	DDRA = 0xFF; //define port A output
	i2c_init();
	i2c_start();
	i2c_write(0x40); //slave address
	while (1)
	{
		i2c_write(0x55);
		_delay_ms(1000);
		i2c_write(0x01);
		_delay_ms(1000);
	
	}
}