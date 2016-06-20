
#ifndef TIMERCOUNTER0_H_
#define TIMERCOUNTER0_H_
#include <stdint.h>
#include <stdbool.h>



typedef void (*FnPtr)(void);

void timer0Init1ms();

uint8_t timer0Read();

void timer0Delay1ms(uint16_t millis, FnPtr timeoutFn);
void timer0Start (uint16_t millis, FnPtr timeoutFn);


uint8_t timer0ReadOVFFlag();

void trial_fn();
uint8_t timer0ReadCMPFlag();
void timer0Stop();


#endif /* TIMERCOUNTER0_H_ */