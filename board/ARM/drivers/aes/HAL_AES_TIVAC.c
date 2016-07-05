#include "aes.h"
#include "HAL_AES_TIVAC.h"

void HAL_AES_Encrypt(AES_HandleTypeDef* handle)

{
        AESReset(handle->Base_Address);
        handle->ui32Config = handle->ui32Config | AES_CFG_DIR_ENCRYPT;
	AESConfigSet(handle->Base_Address,handle->Config);
	AESKey1Set(handle->Base_Address, handle->Key, handle->ui32Keysize);

        if (handle->Config & AES_CFG_MODE_CBC)
           {
             
	     AESIVSet(handle->Base_Address, handle->pui32IVdata);
	   }
	
	 AESDataProcess(handle->Base_Address, handle->pui32Src, handle->pui32Dest,
		               handle->ui32Length);	

}

void HAL_AES_Decrypt(AES_HandleTypeDef* handle)

{
        AESReset(handle->Base_Address);
        handle->ui32Config = handle->ui32Config | AES_CFG_DIR_DECRYPT;
	AESConfigSet(handle->Base_Address,handle->Config);
	AESKey1Set(handle->Base_Address, handle->Key, handle->ui32Keysize);

        if (handle->Config & AES_CFG_MODE_CBC)
           {
             
	     AESIVSet(handle->Base_Address, handle->pui32IVdata);
	   }
	
	 AESDataProcess(handle->Base_Address, handle->pui32Src, handle->pui32Dest,
		               handle->ui32Length);	

}

