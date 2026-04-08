/*
 * 4D_7S Library - High-performance 4-Digit 7-Segment Multiplexing
 * * Copyright (c) 2026 Dauda Muazu Sulaiman
 * All rights reserved.
 * * This software is licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>

#include "4D_7S.h"
#include "pinDefines.h"


uint8_t groundArray[4] = {PB0, PB1, PB2, PB3};

int main(void){

	clock_prescale_set(clock_div_1);

/*
	THE RULE IS THAT, SINCE YOU PASSED AN ENTIRE PORT TO THE initLED_DISPLAY()
	function, THEN THE PROGRAM IS GOING TO AND USE THE ENTIRE PORT TO POWER THE
	4-DIGIT-7-SEGMENT DISPLAY. BUT THERE ARE OTHER WAYS YOU CAN IMPROVE IT BY 
	USING AN SPI_BASED PIN EXPANDER LIKE 74HC
*/

	initLED_DISPLAY(&PORTD, &PORTB, 0);
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