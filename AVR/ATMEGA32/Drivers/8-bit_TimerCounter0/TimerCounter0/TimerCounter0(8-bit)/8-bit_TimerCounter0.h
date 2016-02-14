/*
 * _8_bit_TimerCounter0.h
 *
 * Created: 1/31/2016 4:29:54 PM
 *  Author: Dell Ultrabook
 */ 


#ifndef TIMERCOUNTER0_H_
#define TIMERCOUNTER0_H_
#include <stdint.h>


// CPU clock speed
//#define F_CPU        16000000                         // 16MHz processor
//#define F_CPU        14745000                         // 14.745MHz processor
//#define F_CPU        8000000                          // 8MHz processor
//#define F_CPU        7372800                            // 7.37MHz processor
//#define F_CPU        4000000                          // 4MHz processor
//#define F_CPU        3686400                          // 3.69MHz processor
//#define CYCLES_PER_US ((F_CPU+500000)/1000000)  // cpu cycles per microsecond


void TimerCounter0_Init (void);
//void TimerCounter0_milliTimeNORMAL (uint8_t time);
uint8_t TimerCounter0_Read();
void delay_ms (uint16_t delayms);
//void delay_us (uint16_t delayus);
void delay1ms(uint16_t delay);
//void delay_CTC_milli (t);
//void delay_us(unsigned short time_us);
//void delay_ms(unsigned char time_ms);

#endif /* TIMERCOUNTER0_H_ */