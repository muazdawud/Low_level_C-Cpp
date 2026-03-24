#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pinDefines.h"
#include "USART.h"

#define LED_DELAY 120
#define DEBOUNCE 10

uint8_t i;
volatile uint8_t check = 1;

ISR(INT0_vect){
	_delay_ms(DEBOUNCE);
	if(bit_is_clear(PIND, PD2)){
		printString("button Pressed.\r\n");
		check ^= 1;
		printString("check = ");
		printByte(check);
		printString("\r\n\r\n");
	}
}

void initInterrupt(void){
	EICRA |= (1 << ISC01);
	EIMSK |= (1 << INT0);
	sei();
}

static inline void moveA(void){
	for(i = 0; i < 6; i++){
		PORTB |= (1 << i);
		_delay_ms(LED_DELAY);
	}

	while(i < 255){
		PORTB &= ~(1 << i);
		_delay_ms(LED_DELAY);
		i--;
	}
}

static inline void moveB(void){
	for(i = 0; i < 6; i++){
		PORTB |= (1 << i);
		_delay_ms(LED_DELAY);
	}

	for(i = 0; i < 6; i++){
		PORTB &= ~(1 << i);
		_delay_ms(LED_DELAY);
	}
}

int main(void){

	DDRB = 0x3f;
	PORTD |= (1 << PD2);

	initUSART();
	initInterrupt();

	while(1){
		if(check){
			moveA();
			printString("moveA in service.\r\n");
			printString("\r\n");
		}else{
			moveB();
			printString("moveB in service.\r\n");
			printString("\r\n");
		}
	}

	return 0;
}