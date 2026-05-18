/*
	A Non-blocking PWM implementation
	using Interrupts Routine
	*/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>


#define 	DELAY	100


volatile uint8_t displayA = 0;
volatile uint8_t displayB = 0;
volatile uint8_t delay_check = 0;
volatile uint8_t update = 0;

static inline void initTimer(void);


ISR(TIMER0_OVF_vect){

	PORTB |= 0x3f;
	OCR0A = displayA;

	if(++delay_check >= DELAY){

		delay_check = 0;

		if(++update >= 3){
			update = 1;
		}
	}
}

ISR(TIMER0_COMPA_vect){
	PORTB &= ~(0x3f);
}

// ISR(TIMER0_COMPB_vect){

// }



int main(void){

	DDRB |= 0x3f;

	uint8_t i;

	initTimer();

	update = 1;

	while(1){

		
		if(update == 1){

			for(i = 0; i < 255; i++){
				// _delay_ms(DELAY);
				displayA = i;
				// displayB = 255 - i;
			}
		}

		if(update == 2){
		
			for(i = 254; i > 0; i--){
				displayA = i;
				// displayB = 255 - i;
			}
		}

	}

	return 0;
}




static inline void initTimer(void){

	TCCR0B |= (1 << CS01) | (1 << CS00);

	// TIMSK0 |= (1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0A);
	TIMSK0 |= (1 << OCIE0A) | (1 << TOIE0);

	sei();
}