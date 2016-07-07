/******************************************************************************
 *	RTOS V 0.0.0 - Copyright (C) 2016
 *  Computer and systems department
 *  Ain Shams University
 *  
 *  All rights reserved
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the redistributions of the
 *  source code must retain the above copyright notice, and this condition.
 *****************************************************************************/
 
 #ifndef IPC_TEST_H_
 #define IPC_TEST_H_
 
 /* parent testing functions */
 uint16_t IPC_test();
 uint16_t IPC_ModulerTest();
 uint16_t IPC_DiffScenariosTest();
 
 /* FUNCTION TESTS */
 uint16_t IPC_u16QueueCreate_test();
 uint16_t IPC_u16QueueEmpty_test();
 uint16_t IPC_u16QueueFull_test();
 uint16_t IPC_u16QueueSendToFront_test();
 uint16_t IPC_u16QueueSendToBack_test();
 uint16_t IPC_u16QueueOverwrite_test();
 uint16_t IPC_u16QueueGetPeek_test();
 uint16_t IPC_u16QueueReceive_test();
 uint16_t IPC_u16QueueReset_test();
 uint16_t IPC_u16QueueMsgWaiting_test();
 uint16_t IPC_u16QueueSpacesAvailable_test();
 
 
 /* MODULE TEST */
 uint16_t IPC_u16QUEUE_ASYNC_SEND_test();
 uint16_t IPC_u16QUEUE_ASYNC_RECEIVE_test();
 uint16_t	IPC_u16QUEUE_SYNC_SEND_test();
 uint16_t IPC_u16QUEUE_SYNC_RECEIVE_test();
 uint16_t IPC_u16QUEUE_PARTIAL_SEND_test();
 uint16_t IPC_u16QUEUE_PARTIAL_RECEIVE_test();

 #endif
 
 
 
 