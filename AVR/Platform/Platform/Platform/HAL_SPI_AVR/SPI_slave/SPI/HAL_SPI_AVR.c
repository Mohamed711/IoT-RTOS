/*
 * SPI_Struct.c
 *
 * Created: 2/20/2016 3:14:24 PM
 *  Author: ZIKO
 */ 
#include "HAL_SPI_AVR.h"
#include "SPI_Config.h"
#include "SPI.h"


const CLK_Rate clk[7] =
{
	{F_CPU/2,4},
	{F_CPU/4,0},
	{F_CPU/8,5},
	{F_CPU/16,1},
	{F_CPU/32,6},
	{F_CPU/64,2},
	{F_CPU/128,3}
};

void HAL_SPI_Init(SPI_INITTypeDef * spi)
{
	SPI_Init(spi->u32MaxFreq, spi->u8Mode, spi->u8DataOrder);
}

void HAL_SPI_InterruptInit()
{
	 SPI_InterruptInit();
}

void HAL_SPI_Transmit(SPI_HandleTypeDef * SPIDATA)
{
	SPI_Transmit(SPIDATA->Txdata);
}

u8 HAL_SPI_Receive(SPI_HandleTypeDef * SPIDATA)
{
	return SPI_Tranceiver(SPIDATA->Txdata);
}
