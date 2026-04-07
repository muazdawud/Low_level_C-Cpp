

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#include "4D_7S.h"
#include "pinDefines.h"

#define PORT_SIZE 7
#define GROUND_SIZE 4

volatile uint8_t *LED_DISPLAY_PORT;
volatile uint8_t *LED_DISPLAY_GROUND;

volatile uint8_t segment = 0;
volatile uint8_t groundCount = 0;

uint8_t numberArray[GROUND_SIZE];

uint8_t GROUND_ARRAY[GROUND_SIZE];

uint8_t NUMBER_BYTES[10] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};


ISR(TIMER2_COMPA_vect){

	for (uint8_t i = 0; i < 4; i++) {
        *LED_DISPLAY_GROUND |= (1 << GROUND_ARRAY[i]);
    }

	*LED_DISPLAY_PORT = NUMBER_BYTES[numberArray[groundCount]];

	*LED_DISPLAY_GROUND &= ~(1 << GROUND_ARRAY[groundCount]);

	groundCount = (groundCount + 1) % 4;
}


static inline void initTIMER_2(void){
	OCR2A = 0x1E;

	TCCR2A |= (1 << WGM21);
	TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

	TIMSK2 |= (1 << OCIE2A);
}


void setPin(const uint8_t ground[]){

	for(uint8_t i = 0; i < GROUND_SIZE; i++){

		GROUND_ARRAY[i] = ground[i];
	}
}


void initLED_DISPLAY(volatile uint8_t *PORT_1, volatile uint8_t *PORT_2){
	
	initTIMER_2();

	LED_DISPLAY_PORT = PORT_1;
	LED_DISPLAY_GROUND = PORT_2;
}


void extractNumber(uint16_t number) {
    uint8_t _tmp_[4];
    
    for (int8_t i = 3; i >= 0; i--) {
        _tmp_[i] = number % 10;
        number /= 10;
    }

    cli();
    for (uint8_t k = 0; k < 4; k++) {
        numberArray[k] = _tmp_[k];
    }
    sei();
}


void DISPLAY(uint16_t num){

	extractNumber(num);

	sei();
	TCNT2 = 0x02;
}