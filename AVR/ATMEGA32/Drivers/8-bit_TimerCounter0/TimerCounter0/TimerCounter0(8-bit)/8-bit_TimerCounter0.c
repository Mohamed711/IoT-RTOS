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




void TimerInit (void)
{		
	TCCR0 |= (((MODE.MODE_NORMAL_CTC & 0x02)>>1)<<WGM01) | ((MODE.MODE_NORMAL_CTC & 0x01)<<WGM00) | (COM00_VALUE<<COM00)|(COM01_VALUE<<COM01);
}

uint8_t timer0_Read()
{
	return TCNT0;
}

void delay1ms(u16 delay)
{
	u8 u8LoopCounter;
	u16 x;

	for(u8LoopCounter=0; u8LoopCounter< PRESCALAR_NUM ; u8LoopCounter++)
	{
		x = clk1ms[u8LoopCounter].TempFreq;
		
		if (x < 256)
		{
			TCCR0 |= ((clk1ms[u8LoopCounter].RegVal) &0x07);
			break;
		}
		
	}
	
	u16 i;
	for (i=0 ; i < delay ; i++)
	{
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


u8 timer0_readOVFFlag()
{
	return (TIFR&0x01);
	//return GETBIT(TIFR,TOV0);
}

u8 timer0_readCMPFlag()
{
	//return GETBIT(TIFR,OCF0);
	return (TIFR&0x02);
}

void setTCNT0 (u8 TCNT0_value)
{
	TCNT0 = TCNT0_value;
}

void setOCR0 (u8 OCR0_value)
{
	OCR0 = OCR0_value;
}

ISR(TIMER0_OVF_vect)
{
	
}

ISR(TIMER0_COMP_vect)
{
	
}