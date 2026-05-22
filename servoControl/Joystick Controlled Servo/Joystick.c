/*
	Author: Dauda Muazu Sulaiman

	Created on 22/05/2026.
*/


#include<avr/io.h>
#include<avr/power.h>



#define  ADC_PRESCALER  128


void initADC(void){

	clock_prescale_set(clock_div_1);

	ADMUX |= (1 << REFS0);

	ADCSRA &= ~(0xff);

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);

	loop_until_bit_is_clear(ADCSRA, ADSC);
}


uint16_t analogGet(uint8_t multiplexer){

	ADMUX = (0xf0 & ADMUX) | multiplexer;

	ADCSRA |= (1 << ADSC);

	loop_until_bit_is_clear(ADCSRA, ADSC);

	return (ADC);
}