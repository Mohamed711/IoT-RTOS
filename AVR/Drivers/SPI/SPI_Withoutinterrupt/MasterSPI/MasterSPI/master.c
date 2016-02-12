 
#include "Master.h"
#include "GPIO.h"
//extern volatile u8 data;

void SPI_MasterInit(void)
{
	GPIO_InitPortDirection(PB,0xFF,0xB0);
	SPCR|=(1<<6)|(1<<5)|(1<<4)|(0x01); //interrupt enable DORD MSTR
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	
}

void SPI_MasterTransmit (u8 data)
{
	SPDR=data;
	while(!(SPSR &(1<<7)));
}

void SPI_MasterTranceiver(u8 data)
{
	SPDR =data;
	while(!(SPSR &(1<<7)));
	PORTA =SPDR;
	//GPIO_WritePort(PA,0xFF,SPDR);
}
/*
ISR (INT1_vect)
{
	//PORTA = SPDR;
	SPDR = 0xFF;//garbage
	while(!(SPSR &(1<<7)));
	PORTA =SPDR;
}
*/