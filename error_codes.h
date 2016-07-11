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
 * 
 *****************************************************************************/
 
 #ifndef ERROR_CODES_H_
 #define ERROR_CODEs_H_
 
 
 #define SUCCESS	( 0x00 )
  

 /* IPC ERRORS */
 /* Module Number 1 */
 
 #define IPC_QUEUE_CREATE_FAIL				( 0x0101 )
 #define IPC_QUEUE_EMPTY_FAIL					( 0x0102 )
 #define IPC_QUEUE_FULL_FAIL					( 0x0103 )	
 #define IPC_QUEUE_SEND_FRONT_FAIL		( 0x0104 )
 #define IPC_QUEUE_SEND_BACK_FAIL			( 0x0105 )
 #define IPC_QUEUE_OVERWRITE_FAIL			( 0x0106 )
 #define IPC_QUEUE_GETPEEK_FAIL				( 0x0107 )
 #define IPC_QUEUE_RECEIVE_FAIL				( 0x0108 )
 #define IPC_QUEUE_RESET_FAIL					( 0x0109 )
 #define IPC_QUEUE_MSG_WAITING_FAIL		( 0x010A )
 #define IPC_QUEUE_SPACE_AVAIL_FAIL		( 0x010B )
 #define IPC_QUEUE_ASYNC_SEND_FAIL		( 0x010C )
 #define IPC_QUEUE_ASYNC_RECV_FAIL		( 0x010D )
 #define IPC_QUEUE_SYNC_SEND_FAIL			( 0x010E )
 #define IPC_QUEUE_SYNC_RECV_FAIL			( 0x010F )
 #define IPC_QUEUE_PARTIAL_SEND_FAIL	( 0x0111 )
 #define IPC_QUEUE_PARTIAL_RECV_FAIL	( 0x0112 )
 
#define RM_NULLPTR 			 							(0x0301)
#define RM_CREATEQUEUE	 							(0x0302)
#define RM_ENQUEUE 										(0x0303)
#define RM_DEQUEUE 										(0x0304)
#define RM_OVERFLOW 									(0x0305)
#define RM_FULLBUFFER 								(0x0306)
 
 #endif