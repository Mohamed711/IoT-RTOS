#include "HAL_AES_AVR.h"

void HAL_AES_Encrypt(AES_HandleTypeDef* handle)
{
	if (handle->mode==AES_CFG_MODE_ECB)
	{
		AES128_ECB_encrypt(handle->input, handle-> key, handle-> output);
	}
	else if(handle->mode==AES_CFG_MODE_CBC)
	{
		AES128_CBC_encrypt_buffer(handle-> output, handle-> input, handle-> length, handle-> key, handle-> iv);
	}
}

void HAL_AES_Decrypt(AES_HandleTypeDef* handle)
{
	if (handle->mode==AES_CFG_MODE_ECB)
	{
		AES128_ECB_decrypt(handle->input, handle-> key, handle-> output);
	}
	else if(handle->mode==AES_CFG_MODE_CBC)
	{
		AES128_CBC_decrypt_buffer(handle-> output, handle-> input, handle-> length, handle-> key, handle-> iv);
	}
}