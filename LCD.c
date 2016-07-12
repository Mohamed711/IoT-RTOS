/*
 * LCD.c
 *
 * Created: 9/23/2015 4:45:17 PM
 *  Author: alaa
 */ 

#include "LCD.h"
#include <avr/io.h>

#define E  0x08
#define RW 0x04
#define RS 0x02

// for LCD 16x2
#define MAX_COLUMNS 16
#define MAX_ROWS		2

static uint8_t cursorPosition = 0x80;		// first row

// Private Function
static void OutCmd(uint8_t command) {
	// send Higher nibble
	LCD_DATA_PORT = command & 0xF0;
	LCD_CRL_PORT &= ~(E + RS + RW);	// E=0, R/W=0, RS=0
	LCD_CRL_PORT |= E;				// E=1, R/W=0, RS=0
	LCD_CRL_PORT &= ~(E + RS + RW);	// E=0, R/W=0, RS=0
	
	// send Lower nibble
	// PORTB &= 0x0F;	// clear Data bits
	LCD_DATA_PORT = (command << 4);
	LCD_CRL_PORT &= ~(E + RS + RW);	// E=0, R/W=0, RS=0
	LCD_CRL_PORT |= E;				// E=1, R/W=0, RS=0
	LCD_CRL_PORT &= ~(E + RS + RW);	// E=0, R/W=0, RS=0
	Timer_Wait(40);
}

/* Display Position: write by sending 0x80 + position
1   2  3  4  5	...	39 40
==========================
00 01 02 03 04	...	26 27
40 41 42 43 44	...	66 67
*/
void LCD_GoToXY(uint8_t row, uint8_t column) {
	if (row < MAX_ROWS && column < MAX_COLUMNS) {
		if (row != 0) {
			column += 0x40;	// move to the second row
		}
		cursorPosition = column + 0x80;
		OutCmd(cursorPosition);
	}
}

void LCD_Init (void) {
	DDRA |= 0xF0;	// Init LCD port as outputs
	DDRB |= E | RS | RW;
	Timer_Init(); // 1us TCNT
	/*** START INIT ***/
	Timer_Wait1ms(15); // 15 ms
	OutCmd(0x03); // function set
	Timer_Wait1ms(4); // 4 ms
	OutCmd(0x03); // second time
	Timer_Wait(100); // 100us
	OutCmd(0x03); // third time
		
	// now the busy flag could be read
	// 1. function set
	OutCmd(0x02);	// wasted as LCD initialized 8-bit by default
	OutCmd(0x28); // 4bit, N=1 2line, F=0 5by7
	// 2. Display off
	OutCmd(0x08); // D=0 display off, C=0 cursor off, B=0 blinking off
	// 3. Display clear
	LCD_Clear();
	// 4. Entry mode Set
	OutCmd(0x06); // Entry mode, I/D=1 Increment, S=0 no display shift
	OutCmd(0x80);	// Set RAM address
	/*** END INIT ***/
 	OutCmd(0x0E); // D=1 display on, C=1 cursor on, B=0 blink off
 	OutCmd(0x10); // S/C=0 cursor move, R/L=0 shift left
	LCD_GoToXY(0, 0);
	/*	S/C R/L
		0	0 Shifts the cursor position to the left. (AC is decremented by one.)
		0	1 Shifts the cursor position to the right. (AC is incremented by one.)
		1	0 Shifts the entire display to the left. The cursor follows the display shift.
		1	1 Shifts the entire display to the right. The cursor follows the display shift.
	*/
}

void LCD_OutChar(uint8_t letter) {
	// letter is ASCII code
	LCD_CRL_PORT &= ~(RW);	// write enable
	LCD_CRL_PORT |= (RS);	// for writing data
	/* send Higher nibble */
	LCD_DATA_PORT = letter & 0xF0;
	LCD_CRL_PORT &= ~(E); // E=0, R/W=0, RS=1
	LCD_CRL_PORT |= E; // E=1, R/W=0, RS=1
	LCD_CRL_PORT &= ~(E); // E=0, R/W=0, RS=1
	
	/* send Lower nibble */
	LCD_DATA_PORT = (letter << 4);
	LCD_CRL_PORT &= ~(E); // E=0, R/W=0, RS=1
	LCD_CRL_PORT |= E; // E=1, R/W=0, RS=1
	LCD_CRL_PORT &= ~(E); // E=0, R/W=0, RS=1
	Timer_Wait(40); // 40 us wait
	
	/* check the cursor position */
	cursorPosition++;
	if(cursorPosition >= 0x80 + MAX_COLUMNS - 1 && cursorPosition < 0xC0) {
		cursorPosition = 0xC0;
		LCD_GoToXY(1, 0);
	} else if (cursorPosition >= 0xC0 + MAX_COLUMNS -1) {
		cursorPosition = 0x80;
		LCD_GoToXY(0, 0);
	}
}

void LCD_Clear(void) {
	cursorPosition = 0x80;
	OutCmd(0x01);		// Clear Display
	Timer_Wait(1600);	// 1.6 ms wait
// 	OutCmd(0x02); // Cursor to home
// 	Timer_Wait(1600); // 1.6 ms wait
//	OutCmd(cursorPosition);
	LCD_GoToXY(0, 0);
	Timer_Wait(1600); // 1.6 ms wait
}

void LCD_OutString (char *str) {
	while (*str) {
		LCD_OutChar(*str);
		str++;
	}
}