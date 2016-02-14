/*
 * SPI_Master.c
 *
 * Created: 2/13/2016 2:58:15 AM
 *  Author: ZIKO
 */ 
#include "SPI.h"

void main()
{
	SPI_Init();
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	while(1)
	{
		SPI_MasterTransmit(7);
		//SPI_MasterTransmit(8);
		//SPI_Tranceiver(7);
		//SPI_Tranceiver(16);
		//SPI_Tranceiver(3);
	}
}