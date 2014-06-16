#include <avr/io.h>
#include <avr/interrupt.h>

#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#include "rc5.h"

/* We use https://github.com/pinkeen/avr-rc5 lib */

#define BLINK_INTERVAL 100L

int main(void) {
	/* Set PC0 to output */
	DDRC |= _BV(PC0);
	RC5_Init();

	/* Enable interrupts */
	sei();

	for(;;) {
		uint16_t command;
     
		/* Poll for new RC5 command */
		if (RC5_NewCommandReceived(&command)) {   
			/* Reset RC5 lib so the next command
			 * can be decoded. This is a must! */
			RC5_Reset();

			int j=0; for (j=0; j<5; j++) {PORTC &= ~(1<<PC0); _delay_ms(BLINK_INTERVAL); PORTC |= (1<<PC0); _delay_ms(BLINK_INTERVAL);}

     
			/* Do something with the command 
			 * Perhaps validate the start bits and output
			 * it via UART... */
			if(RC5_GetStartBits(command) != 3) {   
				/* ERROR */
			}

			uint8_t toggle = RC5_GetToggleBit(command);
			uint8_t address = RC5_GetAddressBits(command);
			uint8_t cmdnum = RC5_GetCommandBits(command);
        	}
	}   
	return 0;
}
