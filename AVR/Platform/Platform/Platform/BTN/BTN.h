/*
 * BTN.h
 *
 * Created: 10/9/2015 7:46:16 PM
 *  Author: mido4
 */ 


#ifndef BTN_H_
#define BTN_H_

#include <stdint.h>

#define BTN_ACTIVE 0x00
#define BTN_INACTIVE 0x01

void BTN_Init(void);
uint8_t Btn_Read(uint8_t BtnId);



#endif /* BTN_H_ */