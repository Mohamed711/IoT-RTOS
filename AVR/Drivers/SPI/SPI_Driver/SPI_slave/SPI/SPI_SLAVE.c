/*
 * SPI_SLAVE.c
 *
 * Created: 2/13/2016 2:47:31 AM
 *  Author: ZIKO
 */ 
#include "SPI.h"
volatile u8 SPI_DATA;
void main()
{
	SPI_Init();
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	//SPI_SlaveTransmit(7);
	//SPI_SlaveTransmit(8);
	//SPI_SlaveTransmit(7);
	
	
	while(1)
	{
		
		//PORTA=SPI_Tranceiver(7);
		GPIO_WritePort(PA,SPI_Tranceiver(7),0xFF);
		GPIO_WritePort(PA,SPI_Tranceiver(8),0xFF);
		
	}
}