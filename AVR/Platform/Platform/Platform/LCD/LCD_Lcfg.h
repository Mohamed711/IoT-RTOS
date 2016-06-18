
#ifndef LCD_LCFG_H_
#define LCD_LCFG_H_

#include <stdint.h>
#include "LCD_Cfg.h"


typedef struct  
{
	uint8_t RegisterSelectPort;
	uint8_t RegisterSelectMask;
	uint8_t ReadWriteControlPort;
	uint8_t ReadWriteControlMask;
	uint8_t EnablePort;
	uint8_t EnableMask;
	uint8_t DataPort;
	uint8_t DataMask;

}LCD_ConfigType;

extern LCD_ConfigType LCD_ConfigData[MAX_LCD_NUM];

#endif /* LCD_LCFG_H_ */