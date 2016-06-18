/*
 * I2C.h
 *
 * Created: 2/4/2016 2:04:55 PM
 *  Author: sameh
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
//#include "I2C_CONFIG.h"

#define F_CPU   8000000UL

/*I2C Initialization*/
void i2c_init()
{
	TWBR = 0x62;  // baud rate is set by calculating the TWBR
	TWCR = (1<<TWEN); // Enable I2C
	TWSR = 0x00;  // prescaler set to 1
}

/* I2C start condition */
void i2c_start()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA); //start condition
	while(!(TWCR & (1<<TWINT)));  //check start condition
	
}

/*I2C Stop*/
void i2c_stop()
{
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}

/*I2C Restart*/
void i2c_restart()
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));  //check start condition
}

/*check for error*/
//if((TWCR & (1<<TWINT)))
//ERROR(); //error function

/* I2C write*/
void i2c_write(char x)
{
	TWDR = x;  //put value in I2C data reg
	TWCR = (1<<TWINT) | (1<<TWEN); //Enable I2C and clear interrupt
	while(!(TWCR & (1<<TWINT))); //write succeeded with TWDR empty
}

/*I2C Read*/
char i2c_read()
{
	TWCR = (1<<TWEN) | (1<<TWINT); // enable I2C and clear interrupt
	while(!(TWCR & (1<<TWINT))); //read succeeded with all data received
	return TWDR;
}

//end of header //


#endif /* I2C_H_ */