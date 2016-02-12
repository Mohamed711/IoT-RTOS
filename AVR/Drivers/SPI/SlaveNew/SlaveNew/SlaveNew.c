/*
 * SlaveNew.c
 *
 * Created: 12/5/2015 1:22:34 AM
 *  Author: ZIKO
 */ 


/*
 * SlaveNew.c
 *
 * Created: 12/5/2015 1:22:34 AM
 *  Author: ZIKO
 */ 




#include "Slave.h"
extern volatile u8 data;
int main(void)
{
	// GPIO_InitPortDirection(PD,0xFF,0xFF); 	
	 //GPIO_InitPortDirection(PA,0xFF,0x00);
	int data=0x05;
	//PORTA= data;
	//DDRA= 0xFF;
	SPI_SlaveInit();
	//PORTA= 0x0f;
//	initInterrupt();
	while(1)
	{
		//GPIO_WritePort(PC,0xFF,data);
		
	// for(int i=0;i<10;i++){}
		//for(int i=0;i<10;i++){}
		SPI_SlaveTransmit(5);
		//PORTC= 0x01;
		SPI_SlaveTransmit(2);
		
		
	//	GPIO_WritePort(PC,0xFF,data);
	}
	
	/*while(1)
	{
		data=SPI_SlaveReceive();
		PORTD=data;
		SPI_SlaveTransmit(data);
		
	}*/
}

     