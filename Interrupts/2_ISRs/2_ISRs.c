#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "USART.h"

#define DEBOUNCE 10
#define LED_DELAY 250

volatile uint8_t check = 0;
volatile uint8_t ADC_Input;
volatile uint16_t input;

ISR(INT0_vect){
	_delay_ms(DEBOUNCE);
	if(bit_is_clear(PIND, PD2)){
		check ^= 1;
		printString("BUTTON Pressed.\r\nCheck = ");
		printByte(check);
		printString("\r\n");
	}
}

ISR(ADC_vect){

	input = ADCH;

	ADC_Input = (uint8_t)(input * 6 / 256) + 1;
}

void initADC(void){
	ADMUX |= (1 << REFS0) | (1 << ADLAR) | (1 << MUX1) | (1 << MUX0);

	ADCSRA &= ~(0xff);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	ADCSRA |= (1 << ADATE) | (1 << ADEN) | (1 << ADIE);

	ADCSRA |= (1 << ADSC);
}

void initInterrupt(void){
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	sei();
}

int main(void){

	DDRB = 0x3f;
	PORTD |= (1 << PD2);

	initUSART();
	initADC();
	initInterrupt();

	while(1){

		if(check){

			if(input != ADC_Input){
				printByte(input);
				printString("\r\n");
			}

			switch(ADC_Input){
				case 1:
					PORTB = 0x1;
					break;
				case 2:
					PORTB = 0x3;
					break;
				case 3:
					PORTB = 0x7;
					break;
				case 4:
					PORTB = 0xf;
					break;
				case 5:
					PORTB = 0x1f;
					break;
				case 6:
					PORTB = 0x3f;
					break;
			}

			_delay_ms(LED_DELAY);

		}else{
			
			PORTB = 0x0;
		}

	}

	return 0;
}