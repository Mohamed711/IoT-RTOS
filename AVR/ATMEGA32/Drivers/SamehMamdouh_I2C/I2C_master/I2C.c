/*
 * I2C.c
 *
 * Created: 2/4/2016 2:00:25 PM
 *  Author: sameh
 */ 


#include <avr/io.h>
#include "I2C.h"
#include "I2C_Lcfg.h"

#define F_CPU   8000000UL

/*I2C Initialization*/
void i2c_init()
{
	//TWBR = 0x62;  // baud rate is set by calculating the TWBR (option)
	TWBR = ((F_CPU/I2C_initConfig.ubrr) - 16)/2;
	TWCR = (1<<TWEN); // Enable I2C
	TWSR = 0x00;  // prescaler set to 1 (option)
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

/* I2C write*/
void i2c_write(char x)
{
	TWDR = x;  //put value in I2C data reg
	TWCR = (1<<TWINT) | (1<<TWEN); //Enable I2C and clear interrupt
	while(!(TWCR & (1<<TWINT))); //write succeeded with TWDR empty
}

/*I2C Read*/
char i2c_read_NACK()
{
	TWCR = (1<<TWEN) | (1<<TWINT); // enable I2C and clear interrupt
	while(!(TWCR & (1<<TWINT))); //read succeeded with all data received
	return TWDR;
}
char i2c_read_ACK()
{
	TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA); // enable I2C and clear interrupt
	while(!(TWCR & (1<<TWINT))); //read succeeded with all data received
	return TWDR;
}

/*
uint8_t TWIGetStatus(void)
{
	uint8_t status;
	//mask status
	status = TWSR & 0xF8;
	return status;
}
*/