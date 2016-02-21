
#ifndef LCD_H_
#define LCD_H_

#include <stdint.h>

void lcd_displayChar(uint8_t data,uint8_t LcdID);
void lcd_Init(void);
void lcd_gotoxy(uint8_t x , uint8_t y , uint8_t LcdID);
void lcd_clrScreen(uint8_t LcdID);
void lcd_dispString(uint8_t * ptr,uint8_t LcdID);
void lcd_disp_string_xy(uint8_t * ptr , uint8_t y , uint8_t x,uint8_t LcdID);
void lcd_disp_int(uint8_t num,uint8_t LcdID);
void lcd_disp_float(float num,uint8_t LcdID);

#endif /* LCD_H_ */