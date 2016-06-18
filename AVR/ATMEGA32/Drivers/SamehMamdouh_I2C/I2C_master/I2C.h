/*
 * I2C.h
 *
 * Created: 2/4/2016 2:04:55 PM
 *  Author: sameh
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>

//#define F_CPU   8000000UL

/*I2C Initialization*/
void i2c_init();

/* I2C start condition */
void i2c_start();
/*I2C Stop*/
void i2c_stop();

/*I2C Restart*/
void i2c_restart();

/* I2C write*/
void i2c_write(char x);

/*I2C Read*/
char i2c_read_NACK();
char i2c_read_ACK();

/*I2C Get Status*
/*uint8_t TWIGetStatus(void);*/

//end of header //


#endif /* I2C_H_ */