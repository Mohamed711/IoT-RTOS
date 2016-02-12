/*
 * Slave.c
 *
 * Created: 2/1/2016 7:41:40 AM
 *  Author: ZIKO
 */ 
#include "Slave.h"
#include "GPIO.h"
//extern volatile u8 data;
u8 data_available=0;
void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	GPIO_InitPortDirection(PB,0xFF,0x40); //only MISO configured as op , others conf as ip
	PORTB |=(1<<4);
	GPIO_InitPortDirection(PC,0xFF,0x01);
	PORTC=0X01;
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	/* Enable SPI */
	SPCR = (1<<SPE)|(1<<DORD)|(1<<SPIE);//interrupt enable DORD
	sei();
	
//	DDRB &= ~(1<<7);
//	PORTD &=~(1<<7);
	//DDRA=0xFF;
}
/*void SPI_SlaveReceive(void)
{
	// Wait for reception complete 
	while(!(SPSR & (1<<SPIF)));
	PORTA=SPDR;
	// Return data register 
	//return SPDR;
}*/
/*void initInterrupt()
{ 
	sei();
	GPIO_InitPortDirection(PD,0xFF,0x08);	//for INT1
	GICR |=(1<<7); //enable external interrupt of INT1
	MCUCR &=~((0<<3) & (0<<2)); // enable interrupt on low levelof INT1 and th
	
	//GPIO_WritePort(PC,0xFF,0x00);
}
*/
void SPI_SlaveTransmit (u8 data)
{
	SPCR &=~ (1<<7);
	PORTC= 0x00;
	SPDR=data;
	while(!(SPSR &(1<<7)));
	//while (data_available !=1);
	data_available =0;
	PORTC= 0x01;
	PORTA =SPDR;
	//PORTA =SPDR;
	SPCR |= (1<<7);
}


ISR (SPI_STC_vect)//receive
{
	data_available =1;
	PORTA =SPDR;
//	PORTC= 0x01;
}