/*
 * SPI_Master.c
 *
 * Created: 2/13/2016 2:58:15 AM
 *  Author: ZIKO
 */ 
#include "SPI.h"
volatile u8 SPI_DATA;
 SPI_INITTypeDef spi =
 {
	 //5,
	 2000000UL,
	 u8MODE_1,
	 u8DOR_MSB
 };

 SPI_HandleTypeDef SPIDATA =
 {
	 7,
	 8
 };
 
void main()
{
	
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	HAL_SPI_Init( &spi);
	while(1)
	{
		
		SPIDATA.Txdata=2;
		PORTA=HAL_SPI_Receive(&SPIDATA);//SPI_Tranceiver(7);
		SPIDATA.Txdata=5;
		PORTA=HAL_SPI_Receive(&SPIDATA);
	}
}