/*
 * I2C.h
 *
 * Created: 2/4/2016 2:04:55 PM
 *  Author: sameh
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <avr/io.h>
#include "I2C_cfg.h"

void master_init(uint16_t ClockRate);/*Master Initialization*/
void master_transmit(char x,char y);/*Master Transmit*/
char master_receive();/*Master Read*/

void slave_init(uint8_t address);/*Slave Initialization*/
char slave_receive(void);/*slave read*/
void slave_transmit(char write_data);/*Slave transmit*/




/*I2C Get Status*
/*uint8_t TWIGetStatus(void);*/
/*
void i2c_start();
void i2c_stop();
void i2c_restart();
void i2c_write(char x);
char i2c_read_ACK();
//void i2c_init_old();
//void i2c_init();
void TWI_match_read_slave(void);//debug Salve read

void TWI_match_write_slave(void);//debug slave write
*/
//end of header //


#endif /* I2C_H_ */