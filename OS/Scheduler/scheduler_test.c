#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "scheduler_test.h"
#include "Process.h"
#include "realTimeClock.h"
#include "Initialize.h"
#include "nullProcess.h"
#include "queue.h"
#include "../RTOS.h"

#include "../../board/ARM/drivers/inc/hw_memmap.h"
#include "../../board/ARM/drivers/inc/hw_types.h"
#include "../../board/ARM/drivers/sysctl/sysctl.h"
#include "../../board/ARM/drivers/gpio/gpio.h"
#include "../../board/ARM/drivers/uart/HAL_UART.h"

#include "E:/Keil/ARM/CMSIS/Include/core_cmFunc.h"

uint32_t get_MSP()
{
	return __get_MSP();
}

extern pid32 currpid;
extern struct procent proctab[NPROC];		  /* table of processes */
extern qid16 readylist;
extern qid16 suspendedlist;
extern qid16 sleepq;
extern uint32_t prcount;

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
	
	
	initializeNullProcess();
	nullProc(&transmit);
}
