/******************************************************************************
 *	OurOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *
 *  All rights reserved
 *
 *  VISIT http://www.OurRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *****************************************************************************/
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