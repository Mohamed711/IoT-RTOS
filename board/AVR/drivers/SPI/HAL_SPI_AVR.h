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

#ifndef HAL_SPI_AVR_H_
#define HAL_SPI_AVR_H_

#include "../DIO/DIO.h"
#include <stdint.h>
#include <stdbool.h>
#include "SPI_Config.h"
#include "SPI.h"


#ifndef F_CPU
#define F_CPU 8000000ul
#endif

typedef struct {
	uint32_t u32MaxFreq;
	uint8_t u8Mode;
	uint8_t u8DataOrder;
}SPI_InitTypeDef;

typedef struct{
	uint8_t Txdata;
	uint8_t Rxdata;	
	}SPI_HandleTypeDef;

#define spimasterinit(x) spiInitMaster((*x).u32MaxFreq, (*x).u8Mode, (*x).u8DataOrder)
#define spislaveinit(x) spiInitMaster((*x).u32MaxFreq, (*x).u8Mode, (*x).u8DataOrder)
#define spiinterruptenable()  SPIInterruptInit()
#define spimastersend(x) spiMasterTransmit((*x).Txdata)
#define spireceive(x) spiTranceiver((*x).Txdata)

void HAL_SPI_InterruptInit();
void HAL_SPI_Transmit(SPI_HandleTypeDef * SPIDATA);
uint8_t HAL_SPI_Receive(SPI_HandleTypeDef * SPIDATA);

#endif /* HAL_SPI_AVR_H_ */