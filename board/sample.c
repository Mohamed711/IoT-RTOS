#include <stdio.h>
#include "structureParams.h"
#include "default_Initialization.h"
/*
#define UART_INIT(...) do { UART_InitTypeDef __TEMP_VAR__ = UART_DEFAULT_VAL;  	\
COUNT_VARARGS(__VA_ARGS__); 												\
passingInitStructure(&__TEMP_VAR__); } while(0)

typedef struct UART_InitTypeDef
{
  int baud_rate;
  int parity;
  int start;
  int stop_bits;
  int activate;
}UART_InitTypeDef;

void passingInitStructure(UART_InitTypeDef* x)
{
	printf("%d %d %d %d %d \n",x->baud_rate,x->parity,x->start,x->stop_bits,x->activate);
}	


void getParams_test()
{

UART_INIT(stop_bits = 25, activate = 13);

}
*/
