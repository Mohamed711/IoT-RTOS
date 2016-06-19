
#include "SPI.h"
volatile uint8_t SPI_DATA;
 SPI_INITTypeDef spi =
 {
	 2000000UL,
	 u8MODE_1,
	 u8DOR_MSB
 };

/* SPI_HandleTypeDef SPIDATA =
 {
	 8,
	 7
 };*/
 
void main()
{
	/*1-With interrupt 
	HAL_SPI_InterruptInit(); and master'll be transmitting only HAL_SPI_Transmit(&SPIDATA)
		2- without Master transmit HAL_SPI_Transmit(&SPIDATA) slave HAL_SPI_Receive(&SPIDATA)
		for both to transmit and receive use HAL_SPI_Receive(&SPIDATA)
	*/
	SPI_HandleTypeDef SPIDATA ;
	DIO_InitPortDirection(PA,0xFF,0xFF);
	HAL_SPI_Init( &spi);
	//HAL_SPI_InterruptInit();
		//PORTA=SPIDATA.Rxdata;
	while(1)
	{
		SPIDATA.Txdata=8;
		PORTA=HAL_SPI_Receive(&SPIDATA);
		SPIDATA.Txdata=32;
		PORTA=HAL_SPI_Receive(&SPIDATA);
	//PORTA=SPI_DATA;
	}
}