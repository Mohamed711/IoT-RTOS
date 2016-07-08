#ifndef HAL_AES_TIVAC_H_
#define HAL_AES_TIVAC_H_

#include <stdint.h>
#include <stdbool.h>

//*****************************************************************************
//
//! Structure holding the parameters of the data to be processed
//!
//! \param Base_Address is the base address of the AES module.
//! \param *Key is an array of 32-bit words, containing the key to be
//! configured.  The least significant word in the 0th index.
//! \param Mode is the mode of operation and is specified with only one of the following flags.
//!
//! - \b AES_CFG_MODE_ECB - Electronic codebook mode
//! - \b AES_CFG_MODE_CBC - Cipher-block chaining mode
//!
//! \param pui32Src is a pointer to the memory location where the input data
//! is stored.  The data must be padded to the 16-byte boundary.
//! \param pui32Dest is a pointer to the memory location output is written.
//! The space for written data must be rounded up to the 16-byte boundary.
//! \param Key is an array of 32-bit words, containing the key to be
//! configured.  The least significant word in the 0th index.
//! \param ui32Keysize is the size of the key, which must be one of the
//! following values:  \b AES_CFG_KEY_SIZE_128, \b AES_CFG_KEY_SIZE_192, or
//! \b AES_CFG_KEY_SIZE_256.
//! \param pui32IVdata is an array of 4 words (128 bits), containing the IV
//! value to be configured.  The least significant word is in the 0th index.
//! \param ui32Length is the length of the cryptographic data in bytes.
//
//*****************************************************************************
typedef struct {
	uint32_t Base_Address;
	uint32_t Mode;
	uint32_t *Key;
	uint32_t ui32Keysize;
	uint32_t *pui32IVdata;
	uint32_t ui32Length; 
	uint32_t *pui32Dest; 
	uint32_t *pui32Src; 
} AES_HandleTypeDef;

void HAL_AES_Encrypt(AES_HandleTypeDef* handle);
void HAL_AES_Decrypt(AES_HandleTypeDef* handle);

#endif /* HAL_AES_TIVAC_H_ */
