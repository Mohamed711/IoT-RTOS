
#include "SPI.h"

static volatile uint8_t u8LoopCount;
 volatile uint8_t SPI_DATA;
 
void spiInitMaster(uint32_t u32MaxFreq, uint8_t u8Mode, uint8_t u8DataOrder)
{
	uint8_t u8LoopCount;
	
		DIO_InitPortDirection(PB,0xB0,0xF0);// MOSI,MISO,SCK,SS Port direction

	/*Get the most suitable pre-scalar */
	for(u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(spi_clk[u8LoopCount].u32TempFreq <= u32MaxFreq)
		{
			break;
		}
	}
	
	SPCR_REG = 0X00;
	SPCR_REG |=  SPI_EN | u8DataOrder |Master_Or_Slave| u8Mode|(spi_clk[u8LoopCount].u8RegVal & 0x03);
	SPSR_REG = 0x00;
	SPSR_REG |= (spi_clk[u8LoopCount].u8RegVal >> 2);
	
}


void spiInitSlave(uint32_t u32MaxFreq, uint8_t u8Mode, uint8_t u8DataOrder)
{
	uint8_t u8LoopCount;

	/* Set MISO output, all others input */
	DIO_InitPortDirection(PB,0x40,0xF0); //only MISO configured as op , others conf as ip
	
	/*Get the most suitable pre-scalar */
	for(u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(spi_clk[u8LoopCount].u32TempFreq <= u32MaxFreq)
		{
			break;
		}
	}
	
	SPCR_REG = 0X00;
	SPCR_REG |=  SPI_EN | u8DataOrder |Master_Or_Slave| u8Mode|(spi_clk[u8LoopCount].u8RegVal & 0x03);
	SPSR_REG = 0x00;
	SPSR_REG |= (spi_clk[u8LoopCount].u8RegVal >> 2);
	
}

void SPIInterruptInit()
{
		SPCR_REG |=  ENABLE_INTERRUPT_OR_NOT ;
		sei();	
}

void spiMasterTransmit(uint8_t data)
{
	SPDR_REG=data;
	while(!(SPSR_REG & SPIF_0));
}

ISR (SPI_STC_vect)//receive for slave 
{
	SPI_DATA=SPDR_REG;
}


uint8_t spiTranceiver(uint8_t data)
{
	SPDR_REG =data;
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}