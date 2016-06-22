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

#ifndef SPI_H_
#define SPI_H_

#include <avr/io.h>
#include "avr/interrupt.h"
#include "../DIO/DIO.h"
#include "SPI_Config.h"
#include "SPI_Lcfg.h"
#include "HAL_SPI_AVR.h"

void spiInitMaster(uint32_t u32MaxFreq, uint8_t u8Mode, uint8_t u8DataOrder);
void spiInitSlave(uint32_t u32MaxFreq, uint8_t u8Mode, uint8_t u8DataOrder);
void SPIInterruptInit();
void spiMasterTransmit(uint8_t data);	//for both with and without interrupt
//void SPI_SlaveTransmit(uint8_t data);	//with interrupt
uint8_t SPI_SlaveReceive();			//without interrupt
uint8_t spiTranceiver(uint8_t data);		//for Master and Slave with and without interrupt
extern volatile uint8_t SPI_DATA ;
#endif /* SPI_H_ */