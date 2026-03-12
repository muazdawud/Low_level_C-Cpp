#include<avr/io.h>
#include<util/delay.h>
#include "USART.h"
#include "pinDefines.h"

#define DELAY 700

static inline void initFreeRunningADC0(void){
	ADMUX |= (1 << REFS0);
	ADMUX |= (1 << ADLAR);

	ADCSRA &= ~(0xff);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);

	//ADCSRA |= (1 << ADATE);
	ADCSRA |= (1 << ADSC);
}

static readInput(uint8_t _address_){
	ADMUX = (0xf0 & ADMUX) | _address_;

	ADCSRA |= (1 << ADSC);
	loop_until_bit_is_clear(ADCSRA, ADSC);

	return (ADCH);
}

int main(void){

	uint8_t potValue, ldrValue;

	initUSART();
	initFreeRunningADC0();

	_delay_ms(5);

	printString("WELCOME TO ANALOG TEST!\r\n\n");

	while(1){

		potValue = readInput(POT);
		ldrValue = readInput(LIGHT_SENSOR);

		printString("POT VALUE = ");
		printByte(potValue);
		printString("\r\n");

		printString("LDR VALUE = ");
		printByte(ldrValue);
		printString("\r\n\n");

		_delay_ms(DELAY);
	}

	return 0;
}