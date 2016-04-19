/*
 * SPI_Master.c
 *
 * Created: 2/13/2016 2:58:15 AM
 *  Author: ZIKO
 */ 
#include "SPI.h"
volatile u8 SPI_DATA;
void main()
{
	SPI_Init();
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	
	while(1)
	{
		
		GPIO_WritePort(PA,SPI_Tranceiver(7),0xFF);
		GPIO_WritePort(PA,SPI_Tranceiver(16),0xFF);
		
		//PORTA=SPI_DATA;
	//	PORTA=SPI_Tranceiver(7);
		//SPI_MasterTransmit(16);
	//	SPI_MasterTransmit(7);
	//	PORTA=SPI_Tranceiver(2);
	//	PORTA=SPI_Tranceiver(8);
		//SPI_Tranceiver(7);
		//SPI_Tranceiver(16);
		//SPI_Tranceiver(3);
	}
}