/*
 * LED.h
 *
 * Created: 10/16/2015 7:52:07 AM
 *  Author: mido4
 */ 


#ifndef LED_H_
#define LED_H_

#include <stdint.h>

#define LED_OFF 0x00
#define LED_ON 0x01

void LED_Init();
void LED_Switch_On(uint8_t LedID);
void LED_Switch_Off(uint8_t LedID);
uint8_t LED_State(uint8_t LedID);


#endif /* LED_H_ */