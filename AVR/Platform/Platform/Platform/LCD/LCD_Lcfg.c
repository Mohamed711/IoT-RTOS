
#include "LCD_Lcfg.h"
#include "../DIO/DIO.h"

LCD_ConfigType LCD_ConfigData[MAX_LCD_NUM]=
{
	{
		PB,
		0x02,
		PB,
		0x04,
		PB,
		0x08,
		PA,
		0xF0
	}
};