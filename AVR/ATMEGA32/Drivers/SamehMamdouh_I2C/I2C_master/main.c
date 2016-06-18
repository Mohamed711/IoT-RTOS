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
#include "I2C_Lcfg.h"

/*WORKING BUT WITHOUT OPTIMIZATION IN ANYTHING*/
int main(void)
{
	//DDRA = 0xFF; //define port A output
	DIO_InitPortDirection(0x00,0xFF,0xFF); //define port A output
	i2c_init();
	i2c_start();
	//i2c_write(0x40); //slave address write to slave
	i2c_write(0x41); //slave address read from slave
	while (1)
	{
		//i2c_start();
		//i2c_write(0x40);
		//i2c_write(0x55);
		//PORTB=i2c_read_ACK();
		//_delay_ms(1000);
		//PORTA=i2c_read_ACK();
		//i2c_write(0x01);
		//PORTB=i2c_read_ACK();
		//_delay_ms(1000);
		//i2c_write(0x01);
		//i2c_stop();		
		//i2c_restart();
		//i2c_write(0x40);
		//_delay_ms(1000);
		PORTA=i2c_read_NACK();
		_delay_ms(1000);
		//i2c_stop();
		//PORTB=i2c_read_ACK();
		
	}
}