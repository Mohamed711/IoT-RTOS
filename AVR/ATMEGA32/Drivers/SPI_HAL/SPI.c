
#include "SPI.h"

static volatile uint8_t u8LoopCount;
 volatile uint8_t SPI_DATA;
void spiInit(uint32_t u32MaxFreq, uint8_t u8Mode, uint8_t u8DataOrder)
{
	uint8_t u8LoopCount;
	#if (Master_Or_Slave == SPI_MASTER_EN)
		DIO_InitPortDirection(PB,0xB0,0xF0);// MOSI,MISO,SCK,SS Port direction
	
	#else
		/* Set MISO output, all others input */
		DIO_InitPortDirection(PB,0x40,0xF0); //only MISO configured as op , others conf as ip
	
	#endif
	
	/*Get the most suitable pre-scalar */
	for(u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(clk[u8LoopCount].u32TempFreq <= u32MaxFreq)
		{
			break;
		}
	}
	
	SPCR_REG = 0X00;
	SPCR_REG |=  SPI_EN | u8DataOrder |Master_Or_Slave| u8Mode|(clk[u8LoopCount].u8RegVal & 0x03);
	SPSR_REG = 0x00;
	SPSR_REG |= (clk[u8LoopCount].u8RegVal >> 2);
	
}

void SPIInterruptInit()
{
		//with or without interrupt
		#if (ENABLE_INTERRUPT_OR_NOT == SPI_INT_EN)  //enable interrupt
		
		SPCR_REG |=  ENABLE_INTERRUPT_OR_NOT ;
		sei();
		
		#endif
		
}

void spiMasterTransmit(uint8_t data)
{
	#if (Master_Or_Slave == SPI_MASTER_EN) //transmit for master
	SPDR_REG=data;
	while(!(SPSR_REG & SPIF_0));
	#endif
	
}

/*
ISR (INT1_vect)  //receive of Master with interrupt
{
	SPDR_REG = 0xFF;//garbage
	while(!(SPSR_REG & SPIF_0));
	SPI_DATA =SPDR_REG;
}
*/
/*void SPI_SlaveTransmit (uint8_t data)
{
	SPCR_REG &=~ ENABLE_INTERRUPT_OR_NOT;
	SPDR_REG=data;
	PORTC= 0x00;
	while(!(SPSR_REG & SPIF_0));
	//data_available =0;
	PORTC= 0x01;
	SPCR_REG |= ENABLE_INTERRUPT_OR_NOT;
}*/


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
/*
uint8_t SPI_SlaveReceive()
{
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}*/