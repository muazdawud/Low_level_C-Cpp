

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>

#include "4D_7S.h"
#include "pinDefines.h"

uint8_t groundArray[4] = {PB0, PB1, PB2, PB3};

int main(void){

	clock_prescale_set(clock_div_1);

	initLED_DISPLAY(&PORTD, &PORTB);
	setPin(groundArray);
	
	DDRD = 0xFF;
	DDRB = 0x3F;

	while(1){

		for(uint16_t i = 0; i < 10000; i++){

			DISPLAY(i);
			_delay_ms(1000);
		}
	}

	return 0;
}