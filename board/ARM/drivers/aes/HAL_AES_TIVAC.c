#include "aes.h"
#include "HAL_AES_TIVAC.h"

void HAL_AES_Encrypt(AES_HandleTypeDef* handle)

{
        AESReset(handle->Base_Address);

	AESConfigSet(handle->Base_Address,((handle->Mode) | (handle->ui32Keysize) | AES_CFG_DIR_ENCRYPT));
	AESKey1Set(handle->Base_Address, handle->Key, handle->ui32Keysize);

        if (handle->Mode == AES_CFG_MODE_CBC)
           {
             
	     AESIVSet(handle->Base_Address, handle->pui32IVdata);
	   }
	
	 AESDataProcess(handle->Base_Address, handle->pui32Src, handle->pui32Dest,
		               handle->ui32Length);	

}

void HAL_AES_Decrypt(AES_HandleTypeDef* handle)

{
        AESReset(handle->Base_Address);

	AESConfigSet(handle->Base_Address,(handle->Mode) | (handle->ui32Keysize) | (AES_CFG_DIR_DECRYPT));
	AESKey1Set(handle->Base_Address, handle->Key, handle->ui32Keysize);

        if (handle->Mode == AES_CFG_MODE_CBC)
           {
             
	     AESIVSet(handle->Base_Address, handle->pui32IVdata);
	   }
	
	 AESDataProcess(handle->Base_Address, handle->pui32Src, handle->pui32Dest,
		               handle->ui32Length);	

}

