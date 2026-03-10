/*
	Gotta be improved with clock cycles and interrupts
*/

#include<avr/io.h>
#include<util/delay.h>
#include"USART.h"
#include"pinDefines.h"

#define DEBOUNCER_DEL 10
#define LED_ 0x3f

static inline uint8_t checkState(void){
	if(!(PIND & (1 << PD2)) == 1){
		return (1);
	}

	return 0;
}

static uint8_t checkBounce(void){

	_delay_ms(DEBOUNCER_DEL);

	if(checkState() == 1){
		return (1);
	}

	return 0;
}


int main(void){
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);

	LED_DDR = LED_;
	uint8_t buttonStatus = 1;

	initUSART();
	printString("Initiating UART\r\n");

	while(1){

		if(checkState()){

			if((buttonStatus == 0) && checkBounce()){

				uint8_t mask = LED_PORT;
				LED_PORT ^= LED_;
				buttonStatus = 1;

				if(!mask){
					printString("LED is ON\r\n");
				}else{
					printString("LED is OFF\r\n");
				}
				
			}

		}
		else{
			buttonStatus = 0;
		}

	}

	return 0;
}