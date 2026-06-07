

/*
	This file contains my first servo tests
	*/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/atomic.h>
#include<util/delay.h>

#include "AnalogInput.h"


#define  F_OCPWM  (50)
#define  PRESCALER  (64)
#define  TOP  ((F_CPU / (F_OCPWM * PRESCALER)) - 1)


#define  PULSE_MIN  ((TOP * 10) / 80)
#define  PULSE_MID  ((TOP * 6) / 80)
#define  PULSE_MAX  (TOP / 40)


#define  ADC_PIN_COUNT  0


uint8_t analogPin = 0;
volatile uint8_t servoUpdate = 0;
uint16_t input = 0;


ISR(TIMER1_CAPT_vect){

		servoUpdate = 1;
}


static inline void initTimer(void){

	TCCR1A |= (1 << COM1A1);

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	/* A Prescaler of 64 */
	TCCR1B |= (1 << CS11) | (1 << CS10);

	TIMSK1 |= (1 << ICIE1);

	ICR1 = (TOP);

	sei();
}


static void showOff(void){

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		OCR1A = PULSE_MID;
		_delay_ms(1500);

		OCR1A = PULSE_MAX;
		_delay_ms(1500);

		OCR1A = PULSE_MIN;
		_delay_ms(1500);

		OCR1A = PULSE_MID;
		_delay_ms(1500);
	}
}


static uint16_t map(uint16_t input){
	/* 
		 No need for the extra load, we alredy know the oldMax and oldMin
		 through the PULSE_MAX and PULSE_MIN macro, and our newLow and
		 newHigh will be 1023 and 0 respectively, from the ADC 10-bit buffer
		 */

	return ( ( ((uint32_t)input * (PULSE_MIN - PULSE_MAX) ) / 1023) + PULSE_MAX);
} 


int main(void){

	initADC();
	initTimer();

	DDRB |= (1 << PB1);
	showOff();

	while(1){

		if(servoUpdate){

			ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
				input = analogGet(0);
			}

			uint16_t tempOCR = OCR1A;
			uint16_t tempInput = map(input);

			uint16_t difference = (tempInput > tempOCR) ? (tempInput - tempOCR) : (tempOCR - tempInput);

			if(difference > 8){

				OCR1A = tempInput;
			}

		  servoUpdate = 0;
		}
	}

	return 0;
}