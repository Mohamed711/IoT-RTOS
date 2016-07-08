#ifndef Shared_Memory_H
#define Shared_Memory_H

#ifdef __cplusplus
extern "C" {
#endif
/**
 * Type by which shared memories are referenced.  For example, a call to xSharedMemCreate()
 * returns an SharedMemHandle_t variable that can then be used as a parameter to
 * xSharedMemSend(), xSharedMemReceive().
 */
typedef void * SharedMemHandle_t ;

/**
 * Creates a new shared memory instance.  This allocates the storage required by the
 * new shared memory and returns a handle for the shared memory.

 * @param uxSharedMemSize is the desired size of the shared memory in bytes.

 *
 * @return a pointer to the created shared memory instance.

 */

#define xSharedMemCreate( uxSharedMemSize ) xSharedMemGenericCreate( uxSharedMemSize )

/**
 * Creates a new shared memory instance.  This allocates the storage required by the
 * new shared memory and returns a handle for the shared memory.
 * It is preferred that the macro xSharedMemCreate is called instead of this function
 *

 * @param uxSharedMemSize is the desired size of the shared memory in bytes.

 *
 * @return a pointer to the created shared memory instance.

 */

SharedMemHandle_t xSharedMemGenericCreate( const UBaseType_t uxSharedMemSize );


/**
 * posts an item to the front of the shared memory.
 *

 * @param xSharedMem is a pointer to the shared memory where the item is to be sent.
 * @param xMessage is the item to be sent.

 *
 * @return None.

 */
void xSharedMemSend( SharedMemHandle_t xSharedMem , uint32_t xMessage );

/**
 * receives an item from the shared memory.
 *
 * @param xSharedMem is a pointer to the shared memory where the item is to be received from.
 *
 * @return the item to be received.

 */
uint32_t xSharedMemReceive( SharedMemHandle_t xSharedMem );

#ifdef __cplusplus
}
#endif


#endif /* Shared_Memory_H */
