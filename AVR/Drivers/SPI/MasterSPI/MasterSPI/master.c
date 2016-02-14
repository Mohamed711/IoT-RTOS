 
#include "Master.h"
#include "GPIO.h"
//extern volatile u8 data;

void SPI_MasterInit(void)
{
	GPIO_InitPortDirection(PB,0xFF,0xB0);
	SPCR|=(1<<6)|(1<<5)|(1<<4)|(0x01); //interrupt enable DORD MSTR
	GPIO_InitPortDirection(PC,0xFF,0x01);
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	//DDRA=0xFF;
}
void initInterrupt()
{
	sei();
	GPIO_InitPortDirection(PD,0x00,0x00);	//for INT1
	GICR |=(1<<7); //enable external interrupt of INT1
	MCUCR &= ~(1<<2); // enable interrupt on low levelof INT1 
	MCUCR |= (1<<3);
	//PORTC=0xFF;
//	DDRC &= ~(1); //pin responsible of interrupt
//	PORTC &=~(0);
}

void SPI_MasterTransmit (u8 data)
{
	//PORTB &=~(1<<4);
	SPDR=data;
	//PORTB = SPDR; for receiving
	while(!(SPSR &(1<<7)));
	//PORTB |=(1<<4);
}

/*void SPI_MasterReceive ()
{
	while(!(SPSR &(1<<7)));
	PORTA =SPDR;
	//GPIO_WritePort(PA,0xFF,SPDR);
}*/

/*ISR(INT1_vect)
{
	PORTA =SPDR;
	//SPI_MasterReceive();
}
*/

ISR (INT1_vect)
{
	//PORTA = SPDR;
	SPDR = 0xFF;//garbage
	while(!(SPSR &(1<<7)));
	PORTA =SPDR;
	//SPI_MasterTransmit(data);
//PORTA = SPDR;
}
