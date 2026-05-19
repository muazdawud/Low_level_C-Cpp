/*
	A Non-blocking PWM implementation
	using Interrupts Routine
	*/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>


#define 	DELAY	3   /*
					A magnitude of 1 DELAY is to be interpretted
					as ~0.001024s which is ~1.02ms (which eliminates
					visible flicker).
					So for an increased value of DELAY, the frequency
					is going to be;

					F_PWM =	(NEW DELAY) * (F_TIMER_OVF_ISR);

					F_TIMER_OVF_ISR = 977Hz;

					Usually a frequency between 1kHz - 5kHz is ideal
					for LED PWM.
					*/


volatile uint8_t displayA = 0;
volatile uint8_t displayB = 255;
volatile uint8_t delay_check = 0;
volatile uint8_t update = 0;
uint8_t difference = 0;

static inline void initTimer(void);


ISR(TIMER0_OVF_vect){

	PORTB |= 0x3f;
	OCR0A = displayA;
	OCR0B = displayB;

	if(++delay_check >= DELAY){

		delay_check = 0; 
		update = 1;
	} 
}

ISR(TIMER0_COMPA_vect){

	PORTB &= ~(1 << PB0) & ~(1 << PB2) & ~(1 << PB4);
}

ISR(TIMER0_COMPB_vect){

	PORTB &= ~(1 << PB1) & ~(1 << PB3) & ~(1 << PB5);
}



int main(void){

	DDRB |= 0x3f;
 
	initTimer(); 

	update = 1;

	while(1){
 		
		if(displayA == 0){

			difference = 1;
		}

		if(displayA == 255){
		
			difference = -1;
		}

		if(update){

			update = 0;
			displayA += difference;
			displayB -= difference;
		}

	}

	return 0;
}




static inline void initTimer(void){

	TCCR0B |= (1 << CS01) | (1 << CS00);

	TIMSK0 |= (1 << OCIE0A) | (1 << OCIE0B) | (1 << TOIE0);

	sei();
}