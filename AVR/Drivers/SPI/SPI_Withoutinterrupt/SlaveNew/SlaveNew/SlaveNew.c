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
	SPI_SlaveInit();
	while(1)
	{
		SPI_SlaveReceive();
		SPI_SlaveTranceiver(2);
		SPI_SlaveTranceiver(5);
	
	}
	
}

     