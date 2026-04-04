#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include "USART.h"
#include "pinDefines.h"

static inline void initTimer1(void){
	TCCR1B |= (1 << CS12) | (1 << CS10);

	//That is 16MHz/1024
}

int main(void){

	initUSART();
	initTimer1();

	uint16_t counterValue = 0;
	uint16_t temp;

	unsigned char sreg = SREG;
	cli();

	TCNT1 = 0;

	SREG = sreg;
	sei();

	while(1){
		
		if((TCNT1 >> 4) != temp){
			counterValue += TCNT1 >> 4;

			printByte(counterValue);
			printString("\r\n");
		}

		temp = TCNT1 >> 4;
	}

	return 0;
}