#include<avr/io.h>
#include<util/delay.h>
#include "USART.h"
#include "pinDefines.h"

#define T_DEL 500
#define DURATION 0xf000

static inline void initADC(void){
	ADMUX |= (1 << REFS0);
	ADCSRA &= ~(0xff);
	ADCSRA |= (7 << ADPS0) | (1 << ADEN);
}

static void toggleLED(uint16_t period){
	uint16_t delay_;
	uint16_t i;

	printByte(period);
	printString("\r\n");

	if(period){

		for(delay_ = 0; delay_ < DURATION; delay_+=period){
			for(i = 0; i < period; i++){
				_delay_us(1);
			}

			LED_PORT ^= (1 << LED0);
		}

	}

}

int main(void){

	LED_DDR |= (1 << LED0);

	initADC();
	initUSART();

	printString("Transmitting LDR Resistance Value\r\n");

	while(1){
		ADCSRA |= (1 << ADSC);
		loop_until_bit_is_clear(ADCSRA, ADSC);

		toggleLED(ADC);
	}

	return 0;
}