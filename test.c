#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h> 

#include "USART.h"

volatile static uint16_t click = 0;
volatile static uint8_t button = 0;


ISR(PCINT1_vect){

	click++;
	button = 1;
}


int main(void){

	DDRC &= ~(1 << PC1);
	PORTC |= (1 << PC1);

	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PC1);

	initUSART();

	sei();

	printString("\r\n=====PCINT TEST=====\r\n");

	while(1){

		if(button){
			button = 0;
			_delay_us(1500);
			if(bit_is_clear(PINC, PC1)){
				printByte(click);
				printString("\r\n");
				click = 0;
			}
		}
	}

	return 0;
}