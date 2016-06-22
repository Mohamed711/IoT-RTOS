
/*************** IPC API ********************/

xQueueCreate( uxQueueLength, uxItemSize );
xQueueSendToFront( xQueue, pvItemToQueue, xTicksToWait );
xQueueSendToBack( xQueue, pvItemToQueue, xTicksToWait );
xQueueSend( xQueue, pvItemToQueue, xTicksToWait );
xQueueOverwrite( xQueue, pvItemToQueue );
xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition );
xQueuePeek( xQueue, pvBuffer, xTicksToWait );
xQueuePeekFromISR( QueueHandle_t xQueue, void * const pvBuffer );
xQueueReceive( xQueue, pvBuffer, xTicksToWait );
xQueueGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait, const BaseType_t xJustPeek );
uxQueueMessagesWaiting( const QueueHandle_t xQueue );
uxQueueSpacesAvailable( const QueueHandle_t xQueue );
vQueueDelete( QueueHandle_t xQueue );
xQueueSendToFrontFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken );
xQueueSendToBackFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken );
xQueueOverwriteFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken );
xQueueSendFromISR( xQueue, pvItemToQueue, pxHigherPriorityTaskWoken );
xQueueGenericSendFromISR( QueueHandle_t xQueue, const void * const pvItemToQueue,
 BaseType_t * const pxHigherPriorityTaskWoken, const BaseType_t xCopyPosition );
xQueueGiveFromISR( QueueHandle_t xQueue, BaseType_t * const pxHigherPriorityTaskWoken );
xQueueReceiveFromISR( QueueHandle_t xQueue, void * const pvBuffer, BaseType_t * const pxHigherPriorityTaskWoken );
xQueueIsQueueEmptyFromISR( const QueueHandle_t xQueue );
xQueueIsQueueFullFromISR( const QueueHandle_t xQueue );
uxQueueMessagesWaitingFromISR( const QueueHandle_t xQueue );
xQueueAltGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, BaseType_t xCopyPosition );
xQueueAltGenericReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait, BaseType_t xJustPeeking );
xQueueAltSendToFront( xQueue, pvItemToQueue, xTicksToWait );
xQueueAltSendToBack( xQueue, pvItemToQueue, xTicksToWait );
xQueueAltReceive( xQueue, pvBuffer, xTicksToWait );
xQueueAltPeek( xQueue, pvBuffer, xTicksToWait );

