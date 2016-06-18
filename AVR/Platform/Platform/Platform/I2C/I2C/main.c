/*
 * main.c
 *
 * Created: 2/5/2016 12:34:33 PM
 *  Author: sameh
 */

#include <avr/io.h>
#include "I2C.h"
#include "DIO.h"
#include <util/delay.h>
//#include "I2C_Lcfg.h"
#include "HAL_i2c_AVR.h"

int main(void)
{
	DIO_InitPortDirection(0x00,0xFF,0xFF); /* define port A output */

	I2C_InitTypeDef init;
	init.clock=9600; /* setting clock rate */
	init.SlaveAddress=0x40; /* write to slave */
	init.type=0;
	
	I2C_HandleTypeDef handle;
	handle.slaveAddress=0x40;
	handle.Txdata=0x55;
	
	HAL_I2C_Init(&init);

	while (1)
	{
		HAL_I2C_Master_Transmit(&handle);
		_delay_ms(1000);
	}
}