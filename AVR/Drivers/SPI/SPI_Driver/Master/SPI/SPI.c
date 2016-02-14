/*
 * SPI.c
 *
 * Created: 2/7/2016 1:45:26 AM
 *  Author: ZIKO
 */ 


#include "SPI.h"
#include "GPIO.h"
#include "SPI_Lcfg.h"
#include "SPI_Config.h"
#include <avr/interrupt.h>


static volatile u8 u8LoopCount;

void SPI_Init(void)
{
	u8 u8LoopCount;
	#if (Master_Or_Slave == SPI_MASTER_EN)
		GPIO_InitPortDirection(PB,0xB0,0xF0);// MOSI,MISO,SCK,SS Port direction
		GPIO_InitPortDirection(PA,0xFF,0xFF);	//for displaying op
	#else
		/* Set MISO output, all others input */
		GPIO_InitPortDirection(PB,0x40,0xF0); //only MISO configured as op , others conf as ip
		GPIO_InitPortDirection(PA,0xFF,0xFF);  //for displaying op
			
	#endif
	
	/*Get the most suitable pre-scalar */
	for(u8LoopCount = 0; u8LoopCount < PRESCALAR_NUM ;u8LoopCount++)
	{
		if(clk[u8LoopCount].u32TempFreq < SPI_InitConfig.u32MaxFreq)
		{
			break;
		}
	}
	
	SPCR_REG = 0X00;
	SPCR_REG |=  SPI_EN | SPI_InitConfig.u8DataOrder |Master_Or_Slave| SPI_InitConfig.u8Mode|(clk[u8LoopCount].u8RegVal & 0x03);
	SPSR_REG = 0x00;
	SPSR_REG |= (clk[u8LoopCount].u8RegVal >> 2);
	
	//with or without interrupt
	#if (ENABLE_INTERRUPT_OR_NOT == SPI_INT_EN)  //enable interrupt
		#if ( Master_Or_Slave == SPI_MASTER_EN) 
		//GPIO_InitPortDirection(PC,0xFF,0x01); //for INT1 
		sei();
		GPIO_InitPortDirection(PD,0x00,0x08);	//for INT1
		//DDRD=0x00;
		GICR_REG |=(INT_1); //enable external interrupt of INT1
		MCUCR_REG &=~(ISC_10); // enable interrupt on negative edge of INT1
		MCUCR_REG |= (ISC_11) ;
		//SPCR_REG &= ~(ENABLE_INTERRUPT_OR_NOT); //to disable spi interrupt
		#else 
		SPCR_REG |=  ENABLE_INTERRUPT_OR_NOT ;
		sei();
		GPIO_InitPortDirection(PC,0x01,0x01);	//responsible for interrupt of INT1
		//DDRC=0x01;
		
		#endif
	#endif
}

void SPI_MasterTransmit (u8 data)
{
	SPDR_REG=data;
	while(!(SPSR_REG & SPIF_0));
}


ISR (INT1_vect)  //receive of Master with interrupt
{
	SPDR_REG = 0xFF;//garbage
	while(!(SPSR_REG & SPIF_0));
	PORTA =SPDR_REG;
}

void SPI_SlaveTransmit (u8 data)
{
	SPCR_REG &=~ ENABLE_INTERRUPT_OR_NOT;
	PORTC= 0x00;
	SPDR_REG=data;
	while(!(SPSR_REG & SPIF_0));
	//data_available =0;
	PORTC= 0x01;
	PORTA =SPDR_REG;
	SPCR_REG |= ENABLE_INTERRUPT_OR_NOT;
}


ISR (SPI_STC_vect)//receive for slave 
{
	PORTA =SPDR_REG;
}


u8 SPI_Tranceiver(u8 data)
{
	SPDR_REG =data;
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}
u8 SPI_SlaveReceive()
{
	while(!(SPSR_REG & SPIF_0));
	return SPDR_REG;
}