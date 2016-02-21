
#include "LCD.h"
#include "LCD_Cfg.h"
#include "LCD_Lcfg.h"
#include "../DIO/DIO.h"

#define F_CPU 8000000UL
#include <util/delay.h>

#define HIGH_NIBBLE(hVar,var) hVar= (var & 0xf0)  // hVar will hold value of high nibble of var
#define LOW_NIBBLE(lVar,var) lVar= (var<<4) // lVar will hold the value of low nibble of var

static void lcd_sendCommand(uint8_t cmd,uint8_t LcdID);


/////////////////////////////////////////////////////////////////////
//	lcd enable triggering function to make lcd aware about command or
//   data changes.
////////////////////////////////////////////////////////////////////

void enableTrigger(uint8_t LcdID)
{
	DIO_WritePort(LCD_ConfigData[LcdID].EnablePort,0x00,LCD_ConfigData[LcdID].EnableMask);
	_delay_us(500);
	DIO_WritePort(LCD_ConfigData[LcdID].EnablePort,0xFF,LCD_ConfigData[LcdID].EnableMask);
	_delay_us(1500);
}

///////////////////////////////////////////////////////////////////////////////////////
// LCD initialization API : set portB from pinB.4 to pinB.7 as o/p for data and commands
//							 and pinB.0 to pinB.2 o/p for control pins
//////////////////////////////////////////////////////////////////////////////////////
void lcd_Init(void)
{
	uint8_t LoopIndex;
	for (LoopIndex = 0 ; LoopIndex < MAX_LCD_NUM;LoopIndex++)
	{
		DIO_InitPortDirection(LCD_ConfigData[LoopIndex].RegisterSelectPort,0xFF,LCD_ConfigData[LoopIndex].RegisterSelectMask);
		DIO_InitPortDirection(LCD_ConfigData[LoopIndex].ReadWriteControlPort,0xFF,LCD_ConfigData[LoopIndex].ReadWriteControlMask);
		DIO_InitPortDirection(LCD_ConfigData[LoopIndex].EnablePort,0xFF,LCD_ConfigData[LoopIndex].EnableMask);
		DIO_InitPortDirection(LCD_ConfigData[LoopIndex].DataPort,0xFF,LCD_ConfigData[LoopIndex].DataMask);
		
		DIO_WritePort(LCD_ConfigData[LoopIndex].EnablePort,0xFF,LCD_ConfigData[LoopIndex].EnableMask);
		DIO_WritePort(LCD_ConfigData[LoopIndex].RegisterSelectPort,0x00,LCD_ConfigData[LoopIndex].RegisterSelectMask);
		DIO_WritePort(LCD_ConfigData[LoopIndex].ReadWriteControlPort,0x00,LCD_ConfigData[LoopIndex].ReadWriteControlMask);
		DIO_WritePort(LCD_ConfigData[LoopIndex].DataPort,0x00,LCD_ConfigData[LoopIndex].DataMask);
		
		lcd_sendCommand(0x33,LoopIndex); // 4-bit mode
		lcd_sendCommand (0x32,LoopIndex);
		lcd_sendCommand (0x28,LoopIndex);

		lcd_sendCommand(0x0c,LoopIndex); // turn on lcd
	}
}


static void lcd_sendCommand(uint8_t cmd,uint8_t LcdID)
{

	uint8_t high_nibble , low_nibble ;
	
	HIGH_NIBBLE(high_nibble,cmd);
	LOW_NIBBLE(low_nibble,cmd);

	DIO_WritePort(LCD_ConfigData[LcdID].RegisterSelectPort,0x00,LCD_ConfigData[LcdID].RegisterSelectMask);
	DIO_WritePort(LCD_ConfigData[LcdID].ReadWriteControlPort,0x00,LCD_ConfigData[LcdID].ReadWriteControlMask);
	
	DIO_WritePort(LCD_ConfigData[LcdID].DataPort,high_nibble,LCD_ConfigData[LcdID].DataMask);
	enableTrigger(LcdID); // triggre lcd enable

	DIO_WritePort(LCD_ConfigData[LcdID].DataPort,low_nibble,LCD_ConfigData[LcdID].DataMask);
	enableTrigger(LcdID);

}

void lcd_displayChar (uint8_t data,uint8_t LcdID)
{

	uint8_t high_nibble , low_nibble ;

	DIO_WritePort(LCD_ConfigData[LcdID].RegisterSelectPort,0xFF,LCD_ConfigData[LcdID].RegisterSelectMask);
	DIO_WritePort(LCD_ConfigData[LcdID].ReadWriteControlPort,0x00,LCD_ConfigData[LcdID].ReadWriteControlMask);
	
	HIGH_NIBBLE(high_nibble,data); // get high nibble data
	LOW_NIBBLE(low_nibble,data); // get low nibble data
	
	DIO_WritePort(LCD_ConfigData[LcdID].DataPort,high_nibble,LCD_ConfigData[LcdID].DataMask);
	enableTrigger(LcdID); // triggre lcd enable
	
	DIO_WritePort(LCD_ConfigData[LcdID].DataPort,low_nibble,LCD_ConfigData[LcdID].DataMask);
	enableTrigger(LcdID);
	
}


void lcd_gotoxy(uint8_t y,uint8_t x,uint8_t LcdID)
{
	uint8_t position = 0x80;
	
	switch(y)
	{
		case 0:
			position=position+x;
			break;
		case 1:
			position=0xc0;
			position=position+x;
			break;
		case 2:
			position=position+x;
			break;
		case 3:
			position=position+x;
			break;
	}
	lcd_sendCommand(position,LcdID);
}


void lcd_clrScreen(uint8_t LcdID)
{
	lcd_sendCommand(0x01,LcdID);
}


void lcd_dispString( uint8_t * ptr,uint8_t LcdID)
{

	while(* ptr!= '\0')
	{
		lcd_displayChar(* ptr,LcdID);
		ptr++;
		
	}

}

void lcd_disp_string_xy(uint8_t * ptr , uint8_t y , uint8_t x, uint8_t LcdID)
{
	lcd_gotoxy(y,x,LcdID);
	lcd_dispString(ptr,LcdID);
}

void lcd_disp_int(uint8_t num,uint8_t LcdID)
{
	uint8_t dispNum[16];
	uint8_t LoopIndex = 0;
	uint8_t ArrayIndex;
	
	if (num == 0)
	{
		lcd_displayChar(48,LcdID);
	}
	else 
	{
		while (num != 0)
		{
			dispNum[LoopIndex++] = num%10 + 48;
			num /= 10;
		}
		
		for (ArrayIndex = 0; ArrayIndex < LoopIndex; ArrayIndex++)
		{
			lcd_displayChar(dispNum[LoopIndex-ArrayIndex-1],LcdID);
		}
	}
	
}

void lcd_disp_float(float num,uint8_t LcdID){
	
	float floatPart = ((num-(uint8_t)num)*100);
	lcd_disp_int((uint8_t)num,LcdID);
	lcd_displayChar('.',LcdID);
	lcd_disp_int((uint8_t)floatPart,LcdID);	
}