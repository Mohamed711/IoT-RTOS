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
#ifndef SPI_LCFG_H_
#define SPI_LCFG_H_

#include "SPI_Config.h"


#define F_CPU 8000000UL

typedef struct
{
	uint32_t u32TempFreq;
	uint8_t u8RegVal;
}SPI_CLK_Rate;

extern const SPI_CLK_Rate spi_clk[PRESCALAR_NUM];



#endif /* SPI_LCFG_H_ */