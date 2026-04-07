#include<avr/io.h>
#include<util/delay.h> 

int main(void) {

	// -------- Inits --------- //
	DDRB |= (1 << PB5);

	while (1) {

	  PORTB |= (1 << PB5);                                      /* wait */

	}                                                  /* End event loop */
	return 0;                            /* This line is never reached */
}
