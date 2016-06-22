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
#ifndef HAL_SPI_TIVAC_H_
#define HAL_SPI_TIVAC_H_

#include <stdint.h>
#include <stdbool.h>
#include "ssi.h"

typedef struct {
	uint32_t ui32Base;
	uint32_t ui32SSIClk;
	uint32_t ui32Protocol;
	uint32_t ui32BitRate;
	uint32_t ui32DataWidth;
	void (*pfnHandler)(void);
    uint32_t ui32IntFlags;
} SPI_InitTypeDef;

typedef struct {
	SPI_InitTypeDef instance;
	uint32_t TxData;
} SPI_HandleTypeDef;

void spimasterinit(SPI_InitTypeDef *spi);
void spislaveinit(SPI_InitTypeDef *spi);
void spiinterruptenable(SPI_InitTypeDef *spi);
void spimastersend(SPI_HandleTypeDef *spi);
uint32_t spireceive(SPI_HandleTypeDef *spi);

#endif /* HAL_SPI_TIVAC_H_ */
