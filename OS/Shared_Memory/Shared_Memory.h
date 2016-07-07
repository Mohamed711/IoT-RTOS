#ifndef Shared_Memory_H
#define Shared_Memory_H

typedef void * SharedMemHandle_t ;


#define xSharedMemCreate( uxSharedMemSize, uxItemSize ) xSharedMemGenericCreate( uxSharedMemSize )

SharedMemHandle_t xSharedMemGenericCreate( const UBaseType_t uxSharedMemSize );
BaseType_t xSharedMemSend( SharedMemHandle_t xSharedMem , uint32_t xMessage );
uint32_t xSharedMemGenericReceive( SharedMemHandle_t xSharedMem );

#ifdef __cplusplus
}
#endif


#endif /* Shared_Memory_H */
