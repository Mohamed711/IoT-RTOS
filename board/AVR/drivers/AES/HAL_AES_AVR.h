
#ifndef HAL_AES_AVR_H_
#define HAL_AES_AVR_H_

#include <stdint.h>
#include "AES_AVR.h"

#define AES_CFG_MODE_ECB 0
#define AES_CFG_MODE_CBC 1

typedef struct{
	uint8_t mode;
	uint8_t* input;
	uint8_t* output;
	uint8_t* key;
	uint8_t* iv;
	uint32_t length;
} AES_HandleTypeDef;

void HAL_AES_Encrypt(AES_HandleTypeDef* handle);
void HAL_AES_Decrypt(AES_HandleTypeDef* handle);

#endif /* HAL_AES_AVR_H_ */