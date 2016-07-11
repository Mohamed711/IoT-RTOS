#ifndef TESTS_H_
#define TESTS_H_


#define NO_TEST									0
#define ARMScheduler_TEST 			1

/* IPC TEST */
#define IPC_MODULAR_TEST				2
#define IPC_ASYNC_TEST					3
#define IPC_SYNC_SEND_TEST			4
#define IPC_SYNC_RECV_TEST			5
#define IPC_PAR_SEND_TEST				6
#define IPC_PAR_RECV_TEST				7

#define AVR_ADC_TEST						8
#define AVR_TIMER_TEST					9
#define AVR_SPI_TEST						10
#define AVR_I2C_TEST						11
#define AVR_UART_TEST						12
#define AVR_WATCHDOG_TEST				13


#define 	TEST_USED		IPC_SYNC_SEND_TEST


#endif