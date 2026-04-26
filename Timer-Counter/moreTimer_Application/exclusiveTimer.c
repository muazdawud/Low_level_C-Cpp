/*
	Project Migrated to ../../Digital Watch folder
	*/

/*  NOTES;

	1. Make the ISR implimentation of every ISR required.
		- ISR for both the buzzer and LED update.
		- ISR for the 4-digit 7-segmant display.   (Done)
		- ISR for the POT update.
		- ISR for the DHT11 sensor update.         (Done)
		- ISR for USART.                           (Done)
	2. Make an implimentation of your custom USART library.    (Done)
	3. Make a custom DHT11 sensor module library (read it's datasheet).       (Done)
	4. Don't forget, the time is coming throug USART from ESP8266
	   which will be calling an NTP server for the time and sending
	   it, the recieval will be through ISR for the Atmega.
	5. The LEDs are just for animations and the buzzer is to signal seconds.


*/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#include "pinDefines.h"
#include "USART.h"

/*  
	T_D_THRESHOLD refers to the time required to update the
    running Time display (which is the 4-digit 7-segmant display)
*/ 

#define T_D_THRESHOLD 

volatile uint8_t buttonState = 0;

ISR(TIMER1_COMPA_vect){
	//Make an implementation for the LED animation

	BUZZER_PORT ^= (1 << BUZZER);
}
 
ISR(ADC_vect){
	//Read the ADC buffer
}

ISR(INT1_vect){
	//Trigger the toggle state for button
	buttonState ^= 1;
}

static inline void initISR(void){
/*
	Init ISR on INT1 pin for button, given high priority.
*/
	EICRA |= (1 << ISC11);
	EIMSK |= (1 << INT1);
}

static inline void initTIMER_1(void){
/*
	Set compare value to 15624, to reset the counter as it
	hits the value.
*/
	OCR1A = 0x3D08;

/*
	Set OC1A pin (which corresponds to pin PD6) to 
	toggle state on each compare match of OCR1A with
	Timer/Counter1 by enabling COM1A0 bit.

	Set clock prescaler to (sys_freq.)/1024 by enabling
	bits CS12 and CS10. Which makes the timer to increment
	it's value after every 1024 cycle of the MCU.
*/
	TCCR1A |= (1 << COM1A0);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TIMSK1 |= (1 << OCIE1A);
}

static inline void initTIMER_0(void){
	/*
	Set compare value to 3, to reset the counter as it
	hits the value. This means, the timer will reset at exactly
	every 64x3 (192) cycles of the MCU.
*/
	OCR0A = 0x03;

/*
	Enable CTC by setting WGM01 to 1. Compare value is 
	value of OCR0A above.

	Enable clock prescaler to (sys_freq.)/64 by enabling
	bit CS01 and CS00. Which makes the timer to increment
	it's value after every 64 cycle of the MCU.
*/
	TCCR0A |= (1 << WGM01);
	TCCR0B |= (1 << CS01) | (1 << CS00);
	TIMSK0 |= (1 << OCIE0A);
}

static inline void initADC(void){
/*
	Select internal VCC as reference and select ADLAR 
	which gives a 255 bit resolution/value as Digital Input
	instead of 1024 when `ADLAR = 0` 
*/
	ADMUX |= (1 << REFS0) | (1 << ADLAR);

/*	
	Enable Auto-trigger by setting ADATE bit, and enable 
	Interrupt driven Auto-triggger by setting ADIE to 1 also.

	Select a prescaler of 128 by setting all ADPS2:0 to 1.

	Select an Auto-trigger source                         /
	(in this case the Timer/Counter0 Compare Match A) 
	by setting the ADTS1:0 bits.

*/
	ADCSRA |= (1 << ADATE) | (1 << ADIE);
	ADCSRA |= (1 << ADPS2) | (1 << ADPS) | (1 << ADPS);
	ADCSRB |= (1 << ADTS1) | (1 << ADTS0);

/*
	Enable ADC with ADEN.
	Begin First conversion with setting ADSC to 1.
*/
	ADCSRA |= (1 << ADEN);
	ADCSRA |= (1 << ADSC);
}

int main(void){

	clock_prescale_set(clock_div_1);

	BUTTON_DDR &= ~(1 << BUTTON);
	BUTTON_PORT |= (1 << BUTTON);

	initISR();
	initTIMER_0();
	initTIMER_1();
	initADC();
/*
	This function is provided by the custom
	USART library above.
*/	
	initUSART_M();

/*
	This function is provided by the custom
	DHT11 module library above.
*/	
	initDHT_11();

	while(1){

		if(buttonState){

		}

	}


}