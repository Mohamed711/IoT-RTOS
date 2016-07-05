
/*
 * Define if Watchdog-Timer should be disable at startup
 */
#define DISABLE_WDT_AT_STARTUP

/*
 * Watchdog-reset is issued at exit 'E'
 * define the timeout-value here (see avr-libc manual)
 */
#define EXIT_WDT_TIME   WDTO_250MS

/* character to start the bootloader*/
#define START_WAIT_UARTCHAR 'S'

/* wait-time for START_WAIT mode ( t = WAIT_TIME * 10ms ) */
#define WAIT_VALUE 10000 /* here: 1000*10ms = 10000ms = 10sec */

#include <stdint.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/boot.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "chipdef.h"
#include "HAL_UART.h"

/*a buffer to receive data in*/
uint8_t gBuffer[SPM_PAGESIZE];

HAL_Comm_UART_ConfigStruct_t uart_init_config;
HAL_Comm_UART_HandleTypeDefStruct_t uart_handle;

#if defined(BOOTLOADERHASNOVECTORS)
#warning "This Bootloader does not link interrupt vectors - see makefile"
/* make the linker happy - it wants to see __vector_default */
// void __vector_default(void) { ; }
void __vector_default(void) { ; }
#endif

static void bootLoader_SendChar(uint8_t data)
{
	uart_handle.transmit_char = data;
	HAL_comm_UART_Send(&uart_handle);
}

static uint8_t bootLoader_ReceiveChar(void)
{
	uint16_t x;
	HAL_comm_UART_Receive(&x);
	return x;
}

static inline void bootLoader_EraseFlash(void)
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

static inline void bootLoader_ReceiveBuffer(pagebuf_t size)
{
	pagebuf_t cnt;
	uint8_t *tmp = gBuffer;

	for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
		*tmp++ = (cnt < size) ? bootLoader_ReceiveChar() : 0xFF;
	}
}

static inline uint16_t bootLoader_WriteFlashPage(uint16_t waddr, pagebuf_t size)
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
	
	bootLoader_SendChar('F');
	bootLoader_SendChar('w');
	bootLoader_SendChar('r');
	bootLoader_SendChar('i');
	bootLoader_SendChar('t');
	bootLoader_SendChar('e');
	
	return baddr>>1;
}

static inline uint16_t bootLoader_WriteEEPROM(uint16_t address, pagebuf_t size)
{
	uint8_t *tmp = gBuffer;

	do {
		eeprom_write_byte( (uint8_t*)address, *tmp++ );
		address++;			// Select next byte
		size--;				// Decreas number of bytes to write
	} while (size);				// Loop until all bytes written

		bootLoader_SendChar('E');
		bootLoader_SendChar('w');
		bootLoader_SendChar('r');
		bootLoader_SendChar('i');
		bootLoader_SendChar('t');
		bootLoader_SendChar('e');
		

	return address;
}

static inline uint16_t bootLoader_ReadFlashPage(uint16_t waddr, pagebuf_t size)
{
	uint32_t baddr = (uint32_t)waddr<<1;
	uint16_t data;

	do {
		// don't read bootloader
		if ( baddr < APP_END ) {
			data = pgm_read_word_near(baddr);
		}
		else {
			data = 0xFFFF; // fake empty
		}
		bootLoader_SendChar(data);			// send LSB
		bootLoader_SendChar((data >> 8));		// send MSB
		baddr += 2;			// Select next word in memory
		size -= 2;			// Subtract two bytes from number of bytes to read
	} while (size);				// Repeat until block has been read

	return baddr>>1;
}

static inline uint16_t bootLoader_ReadEEPROM(uint16_t address, pagebuf_t size)
{
	do {
		bootLoader_SendChar( eeprom_read_byte( (uint8_t*)address ) );
		address++;
		size--;				// Decrease number of bytes to read
	} while (size);				// Repeat until block has been read

	return address;
}


static inline uint16_t bootLoader_CopyEEPROMToFlash(uint16_t eAddress, uint16_t fAddress, pagebuf_t size)
{
	pagebuf_t cnt;
	uint8_t *tmp = gBuffer;

	if (size > 128)
	{
		do {
			for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
				*tmp++ = eeprom_read_byte((uint8_t*)eAddress);
				bootLoader_SendChar( gBuffer[cnt] );
				eAddress++;
			}
			fAddress = bootLoader_WriteFlashPage(fAddress, 128);
			size = size - 128;
		} while (size > 128);
	}
	
	tmp = gBuffer;
	for (cnt = 0; cnt < sizeof(gBuffer); cnt++) {
		*tmp++ = (cnt < size) ? eeprom_read_byte((uint8_t*)eAddress) : 0xFF;
		bootLoader_SendChar( gBuffer[cnt] );
		eAddress++;
	}
	return bootLoader_WriteFlashPage(fAddress, size);
	
}	

static void bootLoader_SendEcho(void)
{
	bootLoader_SendChar('A');
	bootLoader_SendChar('V');
	bootLoader_SendChar('R');
	bootLoader_SendChar('B');
	bootLoader_SendChar('O');
	bootLoader_SendChar('O');
	bootLoader_SendChar('T');
}

static void (*jump_to_app1)(void) = 0x0000;

int main(void)
{
	uint16_t addressFR = 0;
	uint16_t addressFW = 0;
	uint16_t addressER = 0;
	uint16_t addressEW = 0;
	uint8_t val;

#ifdef DISABLE_WDT_AT_STARTUP

	cli();
	wdt_reset();
	wdt_disable();

#endif

	uart_init_config.Baud = 19200;
	uart_init_config.DataBits = DATA_BIT_8;
	uart_init_config.StopBits = STOP_BIT_1;
	uart_init_config.Parity = PARITY_DISABLE;
	uart_init_config.EnableInterrupt = 0;
	uart_init_config.U2X_State = U2X_DISABLE;
	
	HAL_comm_UART_Initialize(&uart_init_config);

		
	uint16_t cnt = 0;

	bootLoader_SendEcho();
	
	while (1) {
		
		if (UART_STATUS & (1<<UART_RXREADY))
		{
			bootLoader_SendChar('_');
			bootLoader_SendChar('1');
			bootLoader_SendChar('_');
			if (UART_DATA == START_WAIT_UARTCHAR)
			{
				
				bootLoader_SendChar('_');
				bootLoader_SendChar('2');
				bootLoader_SendChar('_');
				break;
			}				
		}
		if (cnt++ >= WAIT_VALUE) {
			
			bootLoader_SendChar('_');
			bootLoader_SendChar('3');
			bootLoader_SendChar('_');
			jump_to_app1();			// Jump to application sector
			bootLoader_SendChar('#');
		}

		_delay_ms(10);
	}
	
	bootLoader_SendEcho();

	for(;;) {
		val = bootLoader_ReceiveChar();
		// Autoincrement?
		if (val == 'a') {
			bootLoader_SendChar('Y');			// Autoincrement is quicker

		//write addressW
		} else if (val == 'W') {
			val = bootLoader_ReceiveChar();
			if(val == 'F')
			{
				addressFW = bootLoader_ReceiveChar();		//read address 8 MSB
				addressFW = (addressFW<<8) | bootLoader_ReceiveChar();
				bootLoader_SendChar('\r');		
			}
			else if(val == 'E')
			{
				addressEW = bootLoader_ReceiveChar();		//read address 8 MSB
				addressEW = (addressEW<<8) | bootLoader_ReceiveChar();
				bootLoader_SendChar('\r');	
			}
			else
			{
				bootLoader_SendChar(0);
			}
			
		//write addressR
		} else if (val == 'R'){
			val = bootLoader_ReceiveChar();
			if(val == 'F')
			{
				addressFR = bootLoader_ReceiveChar();		//read address 8 MSB
				addressFR = (addressFR<<8) | bootLoader_ReceiveChar();
				bootLoader_SendChar('\r');
			}
			else if(val == 'E')
			{
				addressER = bootLoader_ReceiveChar();		//read address 8 MSB
				addressER = (addressER<<8) | bootLoader_ReceiveChar();
				bootLoader_SendChar('\r');
			}
			else
			{
				bootLoader_SendChar(0);
			}
			
		} else if (val == 'C')
		{
			uint16_t size;
			size = bootLoader_ReceiveChar() << 8;				// Load high byte of buffersize
			size |= bootLoader_ReceiveChar();
			
			addressFW = bootLoader_CopyEEPROMToFlash(addressER, addressFW, size); 
			bootLoader_SendChar('#');
			bootLoader_SendChar('#');
		
		} else if (val == 'r')
		{
			bootLoader_SendChar('F');
			bootLoader_SendChar('R');
			bootLoader_SendChar((addressFR>>8) & 0xFF);
			bootLoader_SendChar(addressFR & 0xFF);
		
			bootLoader_SendChar('F');
			bootLoader_SendChar('W');
			bootLoader_SendChar((addressFW>>8) & 0xFF);
			bootLoader_SendChar(addressFW & 0xFF);
			
			bootLoader_SendChar('E');
			bootLoader_SendChar('R');
			bootLoader_SendChar((addressER>>8) & 0xFF);
			bootLoader_SendChar(addressER & 0xFF);
			
			bootLoader_SendChar('E');
			bootLoader_SendChar('W');
			bootLoader_SendChar((addressEW>>8) & 0xFF);
			bootLoader_SendChar(addressEW & 0xFF);

		// Start buffer load
		} else if (val == 'B') {
			uint16_t size;
			size = bootLoader_ReceiveChar() << 8;				// Load high byte of buffersize
			size |= bootLoader_ReceiveChar();
			bootLoader_SendChar('B');
			bootLoader_SendChar('1');				// Load low byte of buffersize
			val = bootLoader_ReceiveChar();				// Load memory type ('E' or 'F')
			bootLoader_SendChar(val);
			
			if (val == 'F')
			{
				if (size > 128)
				{
					bootLoader_SendChar('P');
					bootLoader_SendChar('0');
					do{
						bootLoader_SendChar('P');
						bootLoader_SendChar('1');
						bootLoader_ReceiveBuffer(128); //sizeof(Buffer) == SPM_PAGESIZE
						addressFW = bootLoader_WriteFlashPage(addressFW, 128);
						size = size - 128;
					} while (size > 128);
				}
				bootLoader_SendChar('P');
				bootLoader_SendChar('2');
				bootLoader_ReceiveBuffer((uint8_t)size);
				addressFW = bootLoader_WriteFlashPage(addressFW, (uint8_t)size);
				
			}
			else if (val == 'E')
			{
				if (size > SPM_PAGESIZE)
				{
					do{
						bootLoader_ReceiveBuffer(SPM_PAGESIZE); //sizeof(Buffer) == SPM_PAGESIZE
						addressEW = bootLoader_WriteEEPROM(addressEW, SPM_PAGESIZE);
						size = size - SPM_PAGESIZE;
					} while (size > SPM_PAGESIZE);
				}
				bootLoader_ReceiveBuffer((uint8_t)size);
				addressEW = bootLoader_WriteEEPROM(addressEW, (uint8_t)size);
			}
			
			
		// Block read
		} else if (val == 'g') {
			pagebuf_t size;
			size = bootLoader_ReceiveChar() << 8;				// Load high byte of buffersize
			size |= bootLoader_ReceiveChar();				// Load low byte of buffersize
			val = bootLoader_ReceiveChar();				// Get memtype

			if (val == 'F') {
				addressFR = bootLoader_ReadFlashPage(addressFR, size);
			} else if (val == 'E') {
				addressER = bootLoader_ReadEEPROM(addressER, size);
			}

		/*Chip erase*/
 		} else if (val == 'e') {
			val = bootLoader_ReceiveChar();
			if(val == 'F')
			{
				bootLoader_EraseFlash();
				addressFW = 0;
				bootLoader_SendChar('\r');				
			}
			else if(val == 'E')
			{
				bootLoader_EraseFlash();
				addressEW = 0;
				bootLoader_SendChar('\r');				
			}
			else
			{
				bootLoader_SendChar(0);
			}

		// Exit upgrade
		} else if (val == 'E') {
			wdt_enable(EXIT_WDT_TIME); // Enable Watchdog Timer to give reset
			bootLoader_SendChar('\r');

		// Return Signature Bytes (it seems that 
		// AVRProg expects the "Atmel-byte" 0x1E last
		// but shows it first in the dialog-window)
		} else if (val == 's') {
			bootLoader_SendChar(SIG_BYTE3);
			bootLoader_SendChar(SIG_BYTE2);
			bootLoader_SendChar(SIG_BYTE1);

		/* ESC */
		} else if(val != 0x1b) {
			bootLoader_SendChar('?');
		}
	}
	return 0;
}
