/*
 * SPI_SLAVE.c
 *
 * Created: 2/13/2016 2:47:31 AM
 *  Author: ZIKO
 */ 
#include "SPI.h"

void main()
{
	SPI_Init();
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	while(1)
	{
	//SPI_SlaveTransmit(7);
	//	SPI_SlaveTransmit(8);
	//PORTA=SPI_SlaveReceive();
	
	//PORTA=SPI_Tranceiver(4);
	//PORTA=SPI_Tranceiver(4);
	//SPI_SlaveTransmit(5);
	//SPI_SlaveTransmit(2);
	}
}