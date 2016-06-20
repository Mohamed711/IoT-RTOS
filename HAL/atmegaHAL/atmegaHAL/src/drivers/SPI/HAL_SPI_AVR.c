
#include "HAL_SPI_AVR.h"

void HAL_SPI_Init(SPI_InitTypeDef * spi)
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
