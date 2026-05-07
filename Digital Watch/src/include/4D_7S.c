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
#include "reg_defs_t.h"
#include "pinDefines.h"

#define GROUND_SIZE 4

volatile uint8_t *LED_DISPLAY_PORT;
volatile uint8_t *LED_DISPLAY_GROUND;

static uint8_t groundCount = 0;

static uint8_t pattern = 0;

static uint8_t numberArray[GROUND_SIZE];

static uint8_t GROUND_ARRAY[GROUND_SIZE];

static uint8_t DPF[GROUND_SIZE] = {0, 0, 0, 0};

static uint8_t temp_DPF[GROUND_SIZE] = {0, 0, 0, 0};

static volatile uint16_t second_timing = 0;

static volatile uint8_t dp_check = 0;

static uint8_t dp_disable = 0;

static uint8_t temp_dp = 0;

static uint16_t compare_val = 0;


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


ISR(_TIMER2_COMPA_) {

    second_timing = (second_timing + 1) % (compare_val/2);

    if(!second_timing){
    	dp_check ^= (1); 
    }

	for (uint8_t i = 0; i < 4; i++) {
        *LED_DISPLAY_GROUND |= (1 << GROUND_ARRAY[i]);
    }

    pattern = numberArray[groundCount];

    if(DPF[groundCount] && (dp_check)){

    	pattern |= 0x80;
    }

    *LED_DISPLAY_PORT = pattern; 	

	*LED_DISPLAY_GROUND &= ~(1 << GROUND_ARRAY[groundCount]);

	groundCount = (groundCount + 1) % 4;
}


static inline void initTIMER_2(void) {
    	/* 
			Changed the value that multiplies by F_CPU to 0.002
			To decrease ISR call latency and boost free clock cycles
			*/
        _OCR2A_ = (uint8_t)((0.002 * F_CPU) / 1024 - 1);

		_TCR2A_ |= (1 << _WGM21_);

		compare_val = ((F_CPU / 1024UL) / _OCR2A_);

		_TIMSK2_ |= (1 << _OCIE2A_);
}


static void extractNumber(uint16_t number) {

	dp_check = 1;

    uint8_t _tmp_[4];
    
    for (int8_t i = 3; i >= 0; i--) {
        _tmp_[i] = number % 10;
        number /= 10;
    }

    // cli();
    for (uint8_t k = 0; k < 4; k++) {
        numberArray[k] = NUMBER_BYTES[_tmp_[k]];
    }
    
}


void setPin(const uint8_t ground[]){

	for(uint8_t i = 0; i < GROUND_SIZE; i++){

		GROUND_ARRAY[i] = ground[i];
	}
}


void initLED_DISPLAY(volatile uint8_t *PORT_1, volatile uint8_t *PORT_2, uint8_t dp_mask){

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

	initTIMER_2();
}
 

void DISPLAY(uint16_t num){

	extractNumber(num);

	// sei();
	_TCR2B_ |= (1 << _CS22_) | (1 << _CS21_) | (1 << _CS20_);
	TCNT2 = 0x1E;
}


/* 
	Should be updated to display characters at given/custom position with 
	This isn't and would not be made to be generic, it is fully custom and
	made for the need of showing characters

	==========||> [-CUSTOM FUNCTION BUILD-] <||==========
*/
void DISPLAY_wChar(uint16_t character, uint8_t number){
    
    extractNumber(number);

    numberArray[0] = (character >> 8);
    numberArray[1] = (character);

    for(uint8_t i = 0; i < GROUND_SIZE; i++){
		temp_DPF[i] = DPF[i];
		DPF[i] = 0;
	}

	dp_disable = 255;

	_TCR2B_ |= (1 << _CS22_) | (1 << _CS21_) | (1 << _CS20_);
	TCNT2 = 0x1E;
}

void DISPLAY_nDP(uint16_t num, uint8_t disable_dp){

	extractNumber(num);


	if((disable_dp-1) < 255){
		temp_dp = DPF[disable_dp-1];
		DPF[disable_dp-1] = 0;
		dp_disable = disable_dp-1;
	}

	if((disable_dp-1) == 255){

		for(uint8_t i = 0; i < GROUND_SIZE; i++){
			temp_DPF[i] = DPF[i];
			DPF[i] = 0;
		}

		dp_disable = disable_dp-1;
	}


	_TCR2B_ |= (1 << _CS22_) | (1 << _CS21_) | (1 << _CS20_);
	TCNT2 = 0x1E;
}

void DISPLAY_reset(){

	groundCount = 0;
	pattern = 0;
	second_timing = 0;
	dp_check = 0;

	if(dp_disable < 255){
		DPF[dp_disable] = temp_dp;
	}

	if(dp_disable == 255){

		for(uint8_t i = 0; i < GROUND_SIZE; i++){
			DPF[i] = temp_DPF[i];
		}
	}

	_TCR2B_ &= ~(1 << _CS22_) & ~(1 << _CS21_) & ~(1 << _CS20_);
}