
#include "TM4C123GH6PM.h"

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifdef ARM
#include "E:/Keil/ARM/CMSIS/Include/core_cmFunc.h"
#endif 


#include "Process.h"
#include "queue.h"
#include "realTimeClock.h"
#include "Initialize.h"
#include "nullProcess.h"
#include "scheduler_test.h"
#include "../RTOS.h"

	extern uint32_t prcount;
	extern qid16 readylist;
	extern qid16 suspendedlist;
	extern qid16 sleepq;
	extern struct procent proctab[NPROC];	
	
	
void set_MSP(uint32_t x)
{
	__set_MSP(x);
}

uint32_t get_MSP()
{
	return __get_MSP();
}

	
void SchedulerTest()
	{
	Uart_InitTypeDef initConf;	
	initializeUART(&initConf,UART0_BASE);
	
	Uart_HandleTypeDef transmit;
	transmit.init = initConf;

	prcount=0;
	readylist = newqueue();
	suspendedlist = newqueue();
	sleepq = newqueue();
	
	
	Scheduler_initializenullProcess();
	//insert(0, readylist, 0);
	Scheduler_nullProc(&transmit);
}

