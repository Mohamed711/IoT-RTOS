/*
 * Platform.c
 *
 * Created: 2/20/2016 4:34:31 PM
 *  Author: mido4
 */ 

#include <stdint.h>
#include <util/delay.h>

#include "BTN/BTN.h"
#include "BTN/BTN_CFG.h"
#include "LCD/LCD.h"
#include "LCD/LCD_Cfg.h"
#include "LED/LED.h"
#include "LED/LED_Cfg.h"

typedef enum {
	GPIO_TEST,
	TIMER_TEST,
	I2C_TEST,
	SPI_TEST,
	UART_TEST,
	ADC_TEST,
	AC_TEST,
	WIFI_TEST,
	WATCHDOG_TIMER_TEST
}tests;

int main(void)
{
	BTN_Init();
	LED_Init();
	lcd_Init();
	
	tests currentTest = GPIO_TEST ;
	uint8_t charSend , charReceived;
	lcd_clrScreen(LCD_ID0);
	lcd_dispString("GPIO TEST",LCD_ID0);
    LED_Switch_On(LED_ID0);
	
	while(1)
    {
		///////////// GPIO TEST ////////////
		if (currentTest == GPIO_TEST)
		{
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = TIMER_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("Timer Test",LCD_ID0);
			}
			else if (Btn_Read(BTN_ID1) == BTN_ACTIVE)
			{
				if (LED_State(LED_ID0) == LED_ON)
				{
					LED_Switch_Off(LED_ID0);
				}
				else
				{
					LED_Switch_On(LED_ID0);
				}
			}		
		}
		///////////// timer test //////////////
		else if (currentTest == TIMER_TEST)
		{
				// Make the led change its state each one second 
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = I2C_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("I2C Test",LCD_ID0);
				lcd_disp_string_xy("Send: ",1,0,LCD_ID0);
				lcd_disp_string_xy("Receive:",1,7,LCD_ID0);
				charSend = 'A'-1;
			}
			else if (Btn_Read(BTN_ID1) == BTN_ACTIVE)
			{
				// if this button is pushed 
				// add one second to the time 
			}
		}
		////////////// I2C Test /////////////////
		else if (currentTest == I2C_TEST)
		{
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = SPI_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("SPI Test",LCD_ID0);
				lcd_disp_string_xy("Send:",1,0,LCD_ID0);
				lcd_disp_string_xy("Receive:",1,7,LCD_ID0);
				charSend = 'A'-1;
			}
			else if (Btn_Read(BTN_ID1) == BTN_ACTIVE)
			{
				charSend += 1;
				// send the char 
				lcd_gotoxy(1,5,LCD_ID0);
				lcd_displayChar(charSend,LED_ID0);
				// receive a character in the charReceived variable
				lcd_gotoxy(1,15,LED_ID0);
				lcd_displayChar(charReceived,LED_ID0);
			}			
		}
		//////////// SPI Test  ////////////////
		else if (currentTest == SPI_TEST)
		{
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = UART_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("UART Test",LCD_ID0);
				lcd_disp_string_xy("Send: ",1,0,LCD_ID0);
				lcd_disp_string_xy("Receive:",1,7,LCD_ID0);
				charSend = 'A'-1;
			}
			else if (Btn_Read(BTN_ID1) == BTN_ACTIVE)
			{
				charSend += 1;
				// send the char
				lcd_gotoxy(1,5,LCD_ID0);
				lcd_displayChar(charSend,LED_ID0);
				// receive a character in the charReceived variable
				lcd_gotoxy(1,15,LED_ID0);
				lcd_displayChar(charReceived,LED_ID0);
			}			
		}
		/////////// UART Test ////////////////
		else if (currentTest == UART_TEST)
		{
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = ADC_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("ADC Test",LCD_ID0);
				lcd_disp_string_xy("val1: ",1,0,LCD_ID0);
			}	
			else if (Btn_Read(BTN_ID1) == BTN_ACTIVE)
			{
				charSend += 1;
				// send the char
				lcd_gotoxy(1,5,LCD_ID0);
				lcd_displayChar(charSend,LED_ID0);
				// receive a character in the charReceived variable
				lcd_gotoxy(1,15,LED_ID0);
				lcd_displayChar(charReceived,LED_ID0);
			}			
		}
		////////// ADC TEST  /////////////////
		else if (currentTest == ADC_TEST)
		{
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = AC_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("AC Test",LCD_ID0);
				lcd_disp_string_xy("val1:",1,0,LCD_ID0);
				continue;
			}	
			float number;
			// display the value of the ADC
			lcd_gotoxy(1,5,LCD_ID0);
			lcd_disp_float(number,LED_ID0);			
		}
		/////////// AC Test   //////////////
		else if (currentTest == AC_TEST)
		{
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = WIFI_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("WIFI Test",LCD_ID0);
				continue;
			}	
			float number;
			// display the value of the AC
			lcd_gotoxy(1,5,LCD_ID0);
			lcd_disp_float(number,LED_ID0);		
		}
		//////////  Wifi TEST //////////////
		else if (currentTest == WIFI_TEST)
		{
			if (Btn_Read(BTN_ID0) == BTN_ACTIVE)
			{
				currentTest = WATCHDOG_TIMER_TEST;
				lcd_clrScreen(LCD_ID0);
				lcd_dispString("WATCHDOG Test",LCD_ID0);
			}			
		}
		/////////  watchdog test ////////////
		else if (currentTest == WATCHDOG_TIMER_TEST)
		{
			// delay then reset the Microcontroller		
		}
		
		_delay_ms(20);
    }
}