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
#include "ssi.h"
#include "SPI_HAL_TivaC.h"

/******************************************************************************
*
*	The function's purpose is to initialize the spi as a master
*
*	\param spi		pointer to structure that contains all the data needed
*					to initialize the spi as a master
*
* 	\return none
*
*****************************************************************************/
void spimasterinit(SPI_InitTypeDef *spi)
{
	SSIConfigSetExpClk (spi->ui32Base, spi->ui32SSIClk,
	                   spi->ui32Protocol, SSI_MODE_MASTER,
	                   spi->ui32BitRate, spi->ui32DataWidth);
	SSIEnable(spi->ui32Base);

}
/******************************************************************************
*
*	The function's purpose is to initialize the i2c as a slave
*
*	\param spi		pointer to structure that contains all the data needed
*					to initialize the spi as a master
*
* 	\return none
*
*****************************************************************************/
void spislaveinit(SPI_InitTypeDef *spi)
{
	SSIConfigSetExpClk (spi->ui32Base, spi->ui32SSIClk,
	                   spi->ui32Protocol, SSI_MODE_SLAVE,
	                   spi->ui32BitRate, spi->ui32DataWidth);
	SSIEnable(spi->ui32Base);

}

/******************************************************************************
*
*	The function's purpose is to enable the slave's interrupt
*
*	\param spi		pointer to structure that contains all the data needed
*					to enable the interrupt for the slave
*
* 	\return none
*
*****************************************************************************/
void spiinterruptenable(SPI_InitTypeDef *spi)
{
	SSIIntRegister(spi->ui32Base, spi->pfnHandler);
		SSIIntEnable(spi->ui32Base, spi->ui32IntFlags);
}

/******************************************************************************
*
*	The function's purpose is to send a data using the spi as a master
*
*	\param spi		pointer to structure that contains an instance of the
*					initialization struction in addition to the data needed
*					to be send using the spi
*
* 	\return none
*
*****************************************************************************/
void spimastersend(SPI_HandleTypeDef *spi)
{
	SSIDataPut(spi->instance.ui32Base, spi->TxData);
}
/******************************************************************************
*
*	The function's purpose is to receive some data using the spi
*
*	\param spi		pointer to structure that contains an instance of the
*					initialization struction
*
* 	\return received data
*
*****************************************************************************/
uint32_t spireceieve(SPI_HandleTypeDef *spi)
{
	uint32_t *Received;
	SSIDataGet(spi->instance.ui32Base, Received);
	return *Received;
}
