/*
 * BTN.h
 *
 * Created: 04/09/2015 10:48:33 ص
 *  Author: hossam
 */ 


#ifndef BTN_H_
#define BTN_H_

#define BTN_ACTIVE 0x01
#define BTN_INACTIVE 0x00
void BTN_Init(uint8_t portname,uint8_t btnMask);
uint8_t BTN_Read(uint8_t portname,uint8_t btnMask);
static uint8_t getIndex(uint8_t mask);


#endif /* BTN_H_ */