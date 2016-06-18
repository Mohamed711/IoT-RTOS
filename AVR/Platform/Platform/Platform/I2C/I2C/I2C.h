/*
 * I2C.h
 *
 * Created: 2/4/2016 2:04:55 PM
 *  Author: sameh
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <stdint.h>
#include "I2C_cfg.h"

void masterInit(uint16_t ClockRate);/*Master Initialization*/
void masterTransmit(char x,char y);/*Master Transmit*/
char masterReceive();/*Master Read*/

void slaveInit(uint8_t address);/*Slave Initialization*/
char slaveReceive(void);/*Slave Read*/
void slaveTransmit(char write_data);/*Slave Transmit*/


#endif /* I2C_H_ */