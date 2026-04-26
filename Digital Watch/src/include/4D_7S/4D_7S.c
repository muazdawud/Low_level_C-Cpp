/*
 * 4D_7S Library - High-performance 4-Digit 7-Segment Multiplexing
 * * Copyright (c) 2026 Dauda Muazu Sulaiman
 * Copyright (c) 2026 KibrisOrder                <https://ss.kibrisorder.com>
 * * Author: Dauda Muazu Sulaiman
 * Organization: KibrisOrder
 * All rights reserved.
 * * This software is licensed under the MIT License.
 * * See the LICENSE file in the project root for full license information.
 * 
 * See the README file in the project root to understand how to use the software.
 */


#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#include "4D_7S.h"
#include "pinDefines.h"

#define GROUND_SIZE 4

volatile uint8_t *LED_DISPLAY_PORT;
volatile uint8_t *LED_DISPLAY_GROUND;

static uint8_t groundCount = 0;

static uint8_t pattern = 0;

static uint8_t numberArray[GROUND_SIZE];

static uint8_t GROUND_ARRAY[GROUND_SIZE];

static uint8_t DPF[GROUND_SIZE] = {0, 0, 0, 0};


// THIS IS THE ARRAY WITHOUT DECIMAL POINTS
static const uint8_t NUMBER_BYTES[10] = {
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


#if defined(TIMER2_COMPA_vect)
    ISR(TIMER2_COMPA_vect) {
#else
    ISR(TIMER2_COMP_vect) {
#endif

	for (uint8_t i = 0; i < 4; i++) {
        *LED_DISPLAY_GROUND |= (1 << GROUND_ARRAY[i]);
    }

    pattern = NUMBER_BYTES[numberArray[groundCount]];

    if(DPF[groundCount]){
    	pattern |= 0x80;
    }

    *LED_DISPLAY_PORT = pattern; 	

	*LED_DISPLAY_GROUND &= ~(1 << GROUND_ARRAY[groundCount]);

	groundCount = (groundCount + 1) % 4;
}


static inline void initTIMER_2(void) {
    #if defined(TCCR2A) && defined(TIMSK2)
    	// MODERN (ATmega328P, 168, 2560, etc.)
        OCR2A = (uint8_t)((0.001 * F_CPU) / 1024 - 1);

		TCCR2A |= (1 << WGM21);
		TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

		TIMSK2 |= (1 << OCIE2A);
    #elif defined(TCCR2) && defined(TIMSK)
		// LEGACY (ATmega8, 16, 32,  etc.)
        OCR2 = (uint8_t)((0.001 * F_CPU) / 1024 - 1);

        TCCR2 |= (1 << WGM21);
		TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);

		TIMSK |= (1 << OCIE2);
    #else
        #error "This MCU is not supported by the 4D_7S library yet!"
    #endif
}


static void extractNumber(uint16_t number) {
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


void setPin(const uint8_t ground[]){

	for(uint8_t i = 0; i < GROUND_SIZE; i++){

		GROUND_ARRAY[i] = ground[i];
	}
}


void initLED_DISPLAY(volatile uint8_t *PORT_1, volatile uint8_t *PORT_2, uint8_t dp_mask){
	
	initTIMER_2();

	LED_DISPLAY_PORT = PORT_1;
	LED_DISPLAY_GROUND = PORT_2;

	//WITH THIS, A USER CAN PASS '0' IF HE DOESN'T WANT DPs

	if((--dp_mask) < 4){
		DPF[dp_mask] = 1;
	}

	if(dp_mask == 255){
		for(uint8_t i = 0; i < GROUND_SIZE; i++){
			DPF[i] = 0;
		}
	}
}
 

void DISPLAY(uint16_t num){

	extractNumber(num);

	sei();
	TCNT2 = 0x02;
}