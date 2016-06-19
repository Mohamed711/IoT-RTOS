

#include "SPI.h"
#include "GPIO.h"
#include "SPI_Lcfg.h"
#include "SPI_Config.h"
#include <avr/interrupt.h>


static volatile uint8_t u8LoopCount;
/* For SPI initialization whether it's Master or Slave*/
void spiInit(void)
{
	uint8_t u8LoopCount;
	#if (Master_Or_Slave == SPI_MASTER_EN)
		GPIO_InitPortDirection(PB,0xB0,0xF0);/* MOSI,MISO,SCK,SS Port direction*/
	
	#else
		/* Set MISO output, all others input */
		GPIO_InitPortDirection(PB,0x40,0xF0); 
	#endif
	
	/*Get the most suitable pre-scalar */
	for(u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(clk[u8LoopCount].u32TempFreq <= SPI_InitConfig.u32MaxFreq)
		{
			break;
		}
	}
	
	SPCR_REG = 0X00;
	SPCR_REG |=  SPI_EN | SPI_InitConfig.u8DataOrder |Master_Or_Slave| SPI_InitConfig.u8Mode|(clk[u8LoopCount].u8RegVal & 0x03);
	SPSR_REG = 0x00;
	SPSR_REG |= (clk[u8LoopCount].u8RegVal >> 2);
	
	/*with or without interrupt*/
	#if (ENABLE_INTERRUPT_OR_NOT == SPI_INT_EN)  /*enable interrupt*/
		#if ( Master_Or_Slave == SPI_MASTER_EN)  
		sei();
		GPIO_InitPortDirection(PD,0x00,0x08);	/*to set external INT1*/
		GICR_REG |=(INT_1); /*enable external interrupt of INT1*/
		MCUCR_REG &=~(ISC_10); /*DDRD=0x00, enable interrupt on negative edge of INT1*/
		MCUCR_REG |= (ISC_11) ;
		SPCR_REG &= ~(ENABLE_INTERRUPT_OR_NOT); /*to disable SPI interrupt*/
		#else 
		SPCR_REG |=  ENABLE_INTERRUPT_OR_NOT ;
		sei();
		GPIO_InitPortDirection(PC,0x01,0x01);	/*PORTC= 0x01,responsible for interrupt of INT1*/
		#endif
	#endif	
}

/*for both Master Transmission with and without interrupt*/
void spiMasterTransmit (uint8_t data)
{
	SPDR_REG=data;
	while(!(SPSR_REG & SPIF_0));
}

/*Interrupt service routine of Master receiving through external interrupt*/
ISR (INT1_vect)  
{
	SPDR_REG = 0xFF;/* put any data to be transmitted to get data from slave*/
	while(!(SPSR_REG & SPIF_0));
	SPI_DATA =SPDR_REG;
}

/*Slave transmit which produce external interrupt in the master, only available if interrupt of Master is enabled*/
void spiSlaveTransmit (uint8_t data)
{
	SPCR_REG &=~ ENABLE_INTERRUPT_OR_NOT;
	SPDR_REG=data;
	GPIO_WritePort(PC,0x00,0x01); /*PORTC= 0x00, reset bit0 in PORTC to make interrupt in master*/
	while(!(SPSR_REG & SPIF_0));
	GPIO_WritePort(PC,0x01,0x01); /*PORTC= 0x01, set bit0 in PORTC*/
	SPCR_REG |= ENABLE_INTERRUPT_OR_NOT;
}

/*Interrupt service routine for receiving of slave while interrupt enabled*/
ISR (SPI_STC_vect) 
{
	SPI_DATA=SPDR_REG;
}

/*function to transmit and receive at the same time used by both Master and Slave*/
uint8_t spiTranceiver(uint8_t data)
{
	SPDR_REG =data;
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}

/*function of Slave receiving without interrupt*/
uint8_t spiSlaveReceive()
{
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}