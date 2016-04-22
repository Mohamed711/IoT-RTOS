#include <stdint.h>
#include <avr/io.h>
/*#include <avr/wdt.h>*/
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "WATCHDOG.h"
#include "HAL_UART.h"
#include "chipdef.h"


// Pin definitions for boot or application reset state
#define	BOOT_STATE_PORT			PORTD
#define	BOOT_STATE_PIN			PIND
#define	BOOT_STATE_PIN_NUMBER	PD7
uint8_t gBuffer[SPM_PAGESIZE];
uint16_t address;

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

int main(void)
{
	cli();
	
	/**** THIS FUNCTION IS NOT IMPLEMENTED ****/
	//Reset_watchdog();
	/******************************************/
	WDT_Disable();
	
	HAL_UART_Init();

	// Use bootloader or application code?
	if( !(BOOT_STATE_PIN & (1<<BOOT_STATE_PIN_NUMBER)) ) /* If BOOT_STATE_PIN_NUMBER is low, use bootloader. */
	{
		while(1)
		{
			// wait for esc character (0x1B) and respond with AVRBOOT
			if(HAL_UART_Receive() == 0x1B)
			{
				// wait for software identifier request
				while( HAL_UART_Receive() != 'S');
				
				// answer the request
				returnSoftwareIdentifier();
				
				// begin servicing the commands
				AVRCommandParser();
			}
			else HAL_UART_Transmit('?');
		}
	}
	else
	{
		// If BOOT_STATE_PIN_NUMBER is high, don't use bootloader.
		// So jump to the application
		jump_to_app();
		BOOT_STATE_PORT &= ~(1<<BOOT_STATE_PIN_NUMBER);	// set to default
	}
	WDT_Enable(WDT_260MS);
	return 0;
}
void returnSoftwareIdentifier(void) // 'S'
{
	// Software identifier is 'AVRBOOT'
	HAL_UART_Transmit('A');
	HAL_UART_Transmit('V');
	HAL_UART_Transmit('R');
	HAL_UART_Transmit('B');
	HAL_UART_Transmit('O');
	HAL_UART_Transmit('O');
	HAL_UART_Transmit('T');
}
void set_address()
{
	address = HAL_UART_Receive();		//read address 8 MSB
	address = (address << 8) | HAL_UART_Receive();
	HAL_UART_Transmit('\r');
}
void checkBlockSupport(void) // 'b'
{
	HAL_UART_Transmit('Y'); // yes, block load is supported.
	HAL_UART_Transmit((SPM_PAGESIZE>>8) & 0xFF); // send MSB first.
	HAL_UART_Transmit(SPM_PAGESIZE & 0xFF); // send LSB second.
}
void AVRCommandParser()
{
	uint8_t cmd;

	while(1)
	{
		cmd = HAL_UART_Receive();

		switch (cmd)
		{
			case 'P':
			//enterProgramMode();
			break;
			
			case 'a':
			HAL_UART_Transmit('Y'); // Autoincrement?
			break;
			
			case 'A':
			set_address(); // write sent address
			break;
			
			case 'e':
			eraseFlash(); //flasherase
			break;
			
			case 'E' :
			WDT_Enable(WDT_260MS); // reset
			
			case 'L':
			HAL_UART_Transmit('\r'); //leave programming mode
			break;
			
			case 'T':
			//selectDeviceType();
			break;
			
			case 's':
			//readSignatureBytes();
			break;
			
			case 't':
			//returnSupportedDeviceCodes();
			break;
			case 'S':
			returnSoftwareIdentifier();
			break;
			case 'p':
			//returnProgrammerType();
			break;
			case 'b':
			checkBlockSupport();
			break;
			case 'B':
			// write flash or write to eeprom
			case 'g':
			//read from flash or eeprom
			
			default:
			HAL_UART_Transmit('?');
		}
	}
}
static inline uint16_t writeEEpromPage(uint16_t address, pagebuf_t size)
{
	uint8_t *tmp = gBuffer;

	do {
		eeprom_write_byte( (uint8_t*)address, *tmp++ );
		address++;			// Select next byte
		size--;				// Decrease number of bytes to write
	} while (size);				// Loop until all bytes written

	// eeprom_busy_wait();

	return address;
}

static inline uint16_t readEEpromPage(uint16_t address, pagebuf_t size)
{
	do {
		HAL_UART_Transmit( eeprom_read_byte( (uint8_t*)address ) );
		address++;
		size--;				// Decrease number of bytes to read
	} while (size);				// Repeat until block has been read

	return address;
}
static inline void eraseFlash(void)
{
	// erase only main section (bootloader protection)
	uint32_t addr = 0;
	while (APP_END > addr) {
		boot_page_erase(addr);		// Perform page erase
		boot_spm_busy_wait();		// Wait until the memory is erased.
		addr += SPM_PAGESIZE;
	}
	boot_rww_enable();
}

static inline uint16_t writeFlashPage(uint16_t waddr, pagebuf_t size)
{
	uint32_t pagestart = (uint32_t)waddr<<1;
	uint32_t baddr = pagestart;
	uint16_t data;
	uint8_t *tmp = gBuffer;

	do {
		data = *tmp++;
		data |= *tmp++ << 8;
		boot_page_fill(baddr, data);	// call asm routine.

		baddr += 2;			// Select next word in memory
		size -= 2;			// Reduce number of bytes to write by two
	} while (size);				// Loop until all bytes written

	boot_page_write(pagestart);
	boot_spm_busy_wait();
	boot_rww_enable();		// Re-enable the RWW section

	return baddr>>1;
}

static inline uint16_t readFlashPage(uint16_t waddr, pagebuf_t size)
{
	uint32_t baddr = (uint32_t)waddr<<1;
	uint16_t data;

	do {
		if ( baddr < APP_END ) {
			data = pgm_read_word_near(baddr);
		}
		else {
			data = 0xFFFF; // fake empty
		}
		HAL_UART_Transmit(data);			// send LSB
		HAL_UART_Transmit((data >> 8));		// send MSB
		baddr += 2;			// Select next word in memory
		size -= 2;			// Subtract two bytes from number of bytes to read
	} while (size);				// Repeat until block has been read

	return baddr>>1;
}

static inline void recvBuffer(pagebuf_t size)
{
	pagebuf_t cnt;
	uint8_t *tmp = gBuffer;

	for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
		*tmp++ = (cnt < size) ? HAL_UART_Receive() : 0xFF;
	}
}