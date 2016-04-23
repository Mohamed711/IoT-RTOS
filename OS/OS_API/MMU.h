/*************** MMU API ********************/
void *pvPortMalloc(size_t xWantedSize);
void vPortInitialiseBlocks(void);
size_t xPortGetFreeHeapSize(void);