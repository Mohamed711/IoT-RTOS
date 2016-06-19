
#include "SPI.h"
volatile uint8_t SPI_DATA;
SPI_INITTypeDef spi =
{
	2000000UL,
	u8MODE_1,
	u8DOR_MSB
};
/*
SPI_HandleTypeDef SPIDATA =
{
	8,
	7
};
*/
void main()
{
	DIO_InitPortDirection(PA,0xFF,0xFF);
	SPI_HandleTypeDef SPIDATA ;
	//SPIDATA.Txdata=16;
	//SPIDATA.Rxdata=7;
	HAL_SPI_Init( &spi);
//	SPIDATA.Txdata=16;

//	HAL_SPI_Transmit(&SPIDATA);
	while(1)
	{
		//SPIDATA.Txdata=8;
		PORTA=HAL_SPI_Receive(&SPIDATA);
		SPIDATA.Txdata=7;
		PORTA=HAL_SPI_Receive(&SPIDATA);
	//	SPIDATA.Txdata=7;
	//	HAL_SPI_Transmit(&SPIDATA);
		///*
		SPIDATA.Txdata=16;
		
		//PORTA=HAL_SPI_Receive(&SPIDATA);
	//	SPIDATA.Txdata=7;
		//HAL_SPI_Transmit(&SPIDATA);;
		//PORTA=HAL_SPI_Receive(&SPIDATA);
		//*/
	/*	SPIDATA.Txdata=8;
		PORTA=HAL_SPI_Receive(&SPIDATA);
		SPIDATA.Txdata=7;
		PORTA=HAL_SPI_Receive(&SPIDATA);
		*/
	}
}