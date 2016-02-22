/*
 * SPI_SLAVE.c
 *
 * Created: 2/13/2016 2:47:31 AM
 *  Author: ZIKO
 */ 
#include "SPI.h"
//#include "HAL_SPI_AVR.h"
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
	 8,
	 7
 };
 
void main()
{
	//SPI_Init();
	GPIO_InitPortDirection(PA,0xFF,0xFF);
	//SPI_SlaveTransmit(7);
	//SPI_SlaveTransmit(8);
	//SPI_SlaveTransmit(7);
	HAL_SPI_Init( &spi);
	
	while(1)
	{
		SPIDATA.Txdata=8;
		PORTA=HAL_SPI_Receive(&SPIDATA);//SPI_Tranceiver(7);
		SPIDATA.Txdata=7;
		PORTA=HAL_SPI_Receive(&SPIDATA);
		//PORTA=//SPI_Tranceiver(8);
		//PORTA=SPI_SlaveReceive();
		//PORTA=SPI_SlaveReceive();
	//	PORTA=SPI_Tranceiver(5);
	//	PORTA=SPI_Tranceiver(8);
		//PORTA=SPI_SlaveReceive();
		
		//SPI_SlaveTransmit(7);
	//	PORTA=SPI_DATA;
	//PORTA=SPI_Tranceiver(2);
	
	//PORTA=SPI_Tranceiver(5);
	
//	PORTA=SPI_Tranceiver(7);
	//PORTA=SPI_Tranceiver(4);
	//SPI_SlaveTransmit(5);
	//SPI_SlaveTransmit(2);
	}
}