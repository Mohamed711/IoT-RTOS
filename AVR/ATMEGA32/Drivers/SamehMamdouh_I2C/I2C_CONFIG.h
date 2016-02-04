/*
 * I2C_CONFIG.h
 *
 * Created: 2/4/2016 3:11:10 PM
 *  Author: sameh
 */ 


#ifndef I2C_CONFIG_H_
#define I2C_CONFIG_H_

#include <avr/io.h>

#define F_CPU  8000000UL

//i2c initialization
/*
void i2c_init()
{
	TWBR = 0x62;  // baud rate is set by calculating the TWBR
	TWCR = (1<<TWEN) // Enable I2C
	TWSR = 0x00;  // prescaler set to 1
}
*/
/*
typedef struct
{
	TWBR;
	TWSR;
} I2C_CONFIG;

extern const I2C_CONFIG I2C_initConfig;
*/
#endif /* I2C_CONFIG_H_ */