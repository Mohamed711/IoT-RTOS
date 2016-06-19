
#include "HAL_SPI_AVR.h"


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
	spiInit(spi->u32MaxFreq, spi->u8Mode, spi->u8DataOrder);
}

void HAL_SPI_InterruptInit()
{
	 SPIInterruptInit();
}

void HAL_SPI_Transmit(SPI_HandleTypeDef * SPIDATA)
{
	spiMasterTransmit(SPIDATA->Txdata);
}

uint8_t HAL_SPI_Receive(SPI_HandleTypeDef * SPIDATA)
{
	return spiTranceiver(SPIDATA->Txdata);
}
