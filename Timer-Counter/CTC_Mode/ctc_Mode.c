#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "pinDefines.h"
#include "USART.h"

volatile uint8_t check = 0;

ISR(TIMER1_COMPA_vect){
	check = 1;
}

static void setOCR1A(void){

	OCR1A = 0x3D08;
}

static inline void initTimer1(void){

	setOCR1A();

	TCCR1B |= (1 << WGM12);
	TIMSK1 |= (1 << OCIE1A);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	
	sei();
}

int main(void){

	initUSART();
	initTimer1();

	LED_DDR = 0x3f;

	uint16_t count = 0;
	TCNT1 = 0;

	while(1){

		if(check){
			count++;
			printByte(count);
			printString("\r\n");

			check = 0;
			LED_PORT ^= 0x3f;
		}
	}

	return 0;
}