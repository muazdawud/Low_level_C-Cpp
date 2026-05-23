#include<avr/io.h>
#include<util/delay.h>
#include "USART.h"
#include "pinDefines.h"

#define TRANSMIT_DELAY 500
#define PORTB_PIN 0x3f

static inline void initADC(void){
	// ADMUX |= (1 << REFS0);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADEN);
}

int main(void){

	initUSART();
	initADC();

	uint16_t x_axis = 0;
	uint16_t y_axis = 0;

	printString("Transmitting LDR Resistance Values;\r\n");

	while(1){
		ADCSRA |= (1 << ADSC);
		loop_until_bit_is_clear(ADCSRA, ADSC);

		printByte(ADC);
		printString("\r\n");

		_delay_ms(TRANSMIT_DELAY);
	}

	return 0;
}