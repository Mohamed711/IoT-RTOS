/*
 * bootloader_tweeka.h
 *
 * Created: 4/24/2016 12:16:50 AM
 *  Author: Mark
 */ 


#ifndef BOOTLOADER_TWEEKA_H_
#define BOOTLOADER_TWEEKA_H_



void returnSoftwareIdentifier(void);
void set_address();
void checkBlockSupport(void);
void AVRCommandParser();
static inline uint16_t writeEEpromPage(uint16_t address, pagebuf_t size);
static inline uint16_t readEEpromPage(uint16_t address, pagebuf_t size);
static inline void eraseFlash(void);
static inline uint16_t writeFlashPage(uint16_t waddr, pagebuf_t size);
static inline uint16_t readFlashPage(uint16_t waddr, pagebuf_t size);
static inline void recvBuffer(pagebuf_t size);
static void (*jump_to_app)(void) = 0x0000;

// Pin definitions for boot or application reset state
#define	BOOT_STATE_PORT			PORTD
#define	BOOT_STATE_PIN			PIND
#define	BOOT_STATE_PIN_NUMBER	PD7


#endif /* BOOTLOADER_TWEEKA_H_ */