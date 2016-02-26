/*
 * SPI.c
 *
 * Created: 2/7/2016 1:45:26 AM
 *  Author: ZIKO
 */ 


#include "SPI.h"
//#include "DIO.h"
//#include "SPI_Lcfg.h"
//#include "SPI_Config.h"
//#include "HAL_SPI_AVR.h"
//#include <avr/interrupt.h>


static volatile u8 u8LoopCount;
 volatile u8 SPI_DATA;
void SPI_Init(u32 u32MaxFreq, u8 u8Mode, u8 u8DataOrder)
{
	u8 u8LoopCount;
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

void SPI_InterruptInit()
{
		//with or without interrupt
		#if (ENABLE_INTERRUPT_OR_NOT == SPI_INT_EN)  //enable interrupt
		#if ( Master_Or_Slave == SPI_MASTER_EN)
		//DIO_InitPortDirection(PC,0xFF,0x01); //for INT1
		sei();
		DIO_InitPortDirection(PD,0x00,0x08);	//for INT1
		//DDRD=0x00;
		GICR_REG |=(INT_1); //enable external interrupt of INT1
		MCUCR_REG &=~(ISC_10); // enable interrupt on negative edge of INT1
		MCUCR_REG |= (ISC_11) ;
		SPCR_REG &= ~(ENABLE_INTERRUPT_OR_NOT); //to disable spi interrupt
		#else
		SPCR_REG |=  ENABLE_INTERRUPT_OR_NOT ;
		sei();
		DIO_InitPortDirection(PC,0x01,0x01);	//responsible for interrupt of INT1
		//PORTC= 0x01;
		#endif
		#endif
}

void SPI_Transmit(u8 data)
{
	#if (Master_Or_Slave == SPI_MASTER_EN) //transmit for master
	SPDR_REG=data;
	while(!(SPSR_REG & SPIF_0));
	#endif
	
	#if (Master_Or_Slave == SPI_SLAVE_EN && ENABLE_INTERRUPT_OR_NOT == SPI_INT_EN)
	SPCR_REG &=~ ENABLE_INTERRUPT_OR_NOT;
	SPDR_REG=data;
	//PORTC= 0x00;
	DIO_InitPortDirection(PC,0x00,0x01);
	while(!(SPSR_REG & SPIF_0));
	//data_available =0;
	//PORTC= 0x01;
	DIO_InitPortDirection(PC,0x01,0x01);
	SPCR_REG |= ENABLE_INTERRUPT_OR_NOT;
	#endif
}
/*void SPI_MasterTransmit (u8 data)
{
	SPDR_REG=data;
	while(!(SPSR_REG & SPIF_0));
}
*/

ISR (INT1_vect)  //receive of Master with interrupt
{
	SPDR_REG = 0xFF;//garbage
	while(!(SPSR_REG & SPIF_0));
	SPI_DATA =SPDR_REG;
}

/*void SPI_SlaveTransmit (u8 data)
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


u8 SPI_Tranceiver(u8 data)
{
	SPDR_REG =data;
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}
/*
u8 SPI_SlaveReceive()
{
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}*/