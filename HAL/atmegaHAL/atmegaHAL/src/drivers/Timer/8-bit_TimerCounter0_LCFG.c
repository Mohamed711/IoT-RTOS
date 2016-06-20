
#include "8-bit_TimerCounter0_LCFG.h"
//#include <util/delay.h>

#define F_CPU 8000000UL
const CLK_RATE1ms clk1ms [5] =
{
{(F_CPU)*0.001,1}, /*F_CPU , Value of CS00-CS01-CS02*/
{(F_CPU/8)*0.001,2},
{(F_CPU/64)*0.001,3},
{(F_CPU/256)*0.001,4},
{(F_CPU/1024)*0.001,5},
};


const TimerMODE MODE = 
{
	u8_MODE_CTC,
};