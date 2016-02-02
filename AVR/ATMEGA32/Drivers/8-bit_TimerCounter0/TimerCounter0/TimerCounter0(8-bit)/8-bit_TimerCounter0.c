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

uint8_t time;

void TimerCounter0_Init (void)
{			
	if((WGM01_VALUE==0) && (WGM00_VALUE==0)) //NORMAL
	{
		TCNT0 &= 0x83;		
	}
	else if ((WGM01_VALUE==1) && (WGM00_VALUE==0)) //CTC
	{
		TCNT0 &=0x00;
		OCR0 = 0x3E;	
	}
	TCCR0 = (CS00_VALUE<<CS00)|(CS01_VALUE<<CS01)|(CS02_VALUE<<CS02)|(WGM01_VALUE<<WGM01)|(WGM00_VALUE<<WGM00)|(COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
	GPIO_InitPortDirection(PB, 0xFF,0xFF);
}

uint8_t TimerCounter0_Read()
{
	return TCNT0;
}

void delay_NORMAL_milli (int t)
{	
	TimerCounter0_Init();
	for (int i=0 ; i<t ; i++)
	{
		TCNT0=0x83;
		//TimerCounter0_Init();
		while((TIFR&0x01)==0)
			{GPIO_WritePort(PB, TCNT0, 0xFF);}
		//TCCR0=0;
		//TCNT0=0x00;
		TIFR = 0x01;
	}
	TCCR0=0x00;
	
}

void delay_CTC_milli (int t)
{
	TimerCounter0_Init();
	for (int i=0 ; i<t ; i++)
	{
		TCNT0=0x00;
		while((TIFR&0x02)==0)
			{GPIO_WritePort(PB, TCNT0, 0xFF);}
		//TCCR0=0;
		//TCNT0=0x00;
		TIFR = 0x02;
	}
	TCCR0=0x00;
	
}