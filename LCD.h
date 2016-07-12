/*
 * LCD.h
 *
 * Created: 9/23/2015 4:45:26 PM
 *  Author: alaa
 */ 


#ifndef LCD_H_
#define LCD_H_

#include "Timer0.h"
#include "RTOS_Headers.h"

#define	LCD_DATA_PORT	PORTA	// D7-D4 connected on PORTA[4-0]
#define LCD_CRL_PORT		PORTB	// E, RW & RS on PORTB[3-1]

void LCD_Init (void);

void LCD_GoToXY(uint8_t row, uint8_t column);

void LCD_OutChar(uint8_t letter);

void LCD_Clear(void);

void LCD_OutString (char *str);

#endif /* LCD_H_ */