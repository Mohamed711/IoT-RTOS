/*
 * _8_bit_TimerCounter0.c
 *
 * Created: 1/31/2016 4:29:30 PM
 *  Author: Dell Ultrabook
 */ 

#include "8-bit_TimerCounter0.h"
#include "GPIO.h"
#include "8-bit_TimerCounter0_LCFG.h"
#include "8-bit_TimerCounter0_CFG.h"
#include "avr/interrupt.h"



void TimerCounter0_Init (void)
{		
	TCCR0 |= (((MODE.MODE_NORMAL_CTC & 0x02)>>1)<<WGM01) | ((MODE.MODE_NORMAL_CTC & 0x01)<<WGM00);
	//TCCR0 = 0x03;
	TCCR0 |= (COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
	
	//TCCR0 = (COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
	//TCCR0 = (MODE.MODE_NORMAL_CTC & 0b10)<<3 | (MODE.MODE_NORMAL_CTC & 0b01)<<6; 
	//TCCR0 = (CS00_VALUE<<CS00)|(CS01_VALUE<<CS01)|(CS02_VALUE<<CS02)|(WGM01_VALUE<<WGM01)|(WGM00_VALUE<<WGM00)|(COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
	//if((WGM01_VALUE==0) && (WGM00_VALUE==0)) //NORMAL
	//{
		//TCNT0 &= 0x00;//0x83;		
	//}
	//else if ((WGM01_VALUE==1) && (WGM00_VALUE==0)) //CTC
	//{
		//TCNT0 &=0x00;
		//OCR0 = 0xFF;
		////OCR0 = 0x3E;	
	//}
	//
	//GPIO_InitPortDirection(PB, 0xFF,0xFF);
}

uint8_t TimerCounter0_Read()
{
	return TCNT0;
}

void delay_ms (uint16_t delay)
{	
	//TimerCounter0_Init();
	TCCR0 |= (CS00_VALUE<<CS00)|(CS01_VALUE<<CS01)|(CS02_VALUE<<CS02)|(WGM01_VALUE<<WGM01)|(WGM00_VALUE<<WGM00)|(COM00_VALUE<<COM00)|(COM01_VALUE<<COM01); 
	uint16_t i;
	for (i=0 ; i < (4 * delay) ; i++)
	{
		TCNT0=0;
		//TimerCounter0_Init();
		//while((TIFR&0x01)==0)
		//for(uint16_t x=0 ; x<4 ; x++)
		
			//TCNT0=0x00;
			while(TCNT0 <= 250)
			;//{GPIO_WritePort(PB, TCNT0, 0xFF);}
		//TCCR0=0;
		//TIFR = 0x01;
		//TCNT0=0x00;
				
	}
	//TCCR0=0x00;
	
}

void delay1ms(uint16_t delay)
{
	TimerCounter0_Init();
	u8 u8LoopCounter;
	u32 x;
	//double y;
	for(u8LoopCounter=0; u8LoopCounter< PRESCALAR_NUM ; u8LoopCounter++)
	{
		//y = 1/(clk[u8LoopCounter].u32TempFreq);
		//x = (0.001/y);
		x = 0.001*(clk[u8LoopCounter].u32TempFreq);
		//x = (clk[u8LoopCounter].u32TempFreq)/1000;
		if (x < 256)
		{
			TCCR0 |= ((clk[u8LoopCounter].u8RegVal) &0x07);
			break;
		}
		
	}
	//GPIO_InitPortDirection(PB, 0xFF,0xFF);
	//GPIO_WritePort(PB, x, 0xFF);
	u16 i;
	for (i=0 ; i < delay ; i++)
	{
		//TCNT0 = 0x00;
		//while(TCNT0 <= (x)); //clk[u8LoopCounter].u32TempFreq);
		if(MODE.MODE_NORMAL_CTC == u8_MODE_NORMAL)
		{
			TCNT0 = 256 - x;
			while ((TIFR&0x01)==0);
			TIFR = 0x01;
		}		
		else if (MODE.MODE_NORMAL_CTC == u8_MODE_CTC)
		{ 
			 TCNT0 = 0;
			 OCR0 = x-1;
			 while ((TIFR&0x02)==0);
			 TIFR = 0x02;
		}
	}
}