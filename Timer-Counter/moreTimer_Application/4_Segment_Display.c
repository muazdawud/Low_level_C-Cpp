

#include<avr/io.h>
#include<util/delay.h>

#include "pinDefines.h"

#define PORT_SIZE      7


uint8_t PIN_ARRAY[PORT_SIZE] = {}

uint8_t NUMBER_BYTES[][7] = {
	{1, 1, 1, 1, 1, 1, 0}, // 0
	{0, 1, 1, 0, 0, 0, 0}, // 1
	{1, 1, 0, 1, 1, 0, 1}, // 2
	{1, 1, 1, 1, 0, 0, 1}, // 3
	{0, 1, 1, 0, 0, 1, 1}, // 4
	{1, 0, 1, 1, 0, 1, 1}, // 5
	{1, 0, 1, 1, 1, 1, 1}, // 6
	{1, 1, 1, 0, 0, 0, 0}, // 7
	{1, 1, 1, 1, 1, 1, 1}, // 8
	{1, 1, 1, 1, 0, 1, 1}  // 9
};


void DISPLAY(uint8_t num){

	const uint8_t *temp = NUMBER_BYTES[num];

	for(uint8_t i = 0; i < PORT_SIZE; i++){
		
		LED_DISPLAY |= (NUMBER_BYTES[i] << PIN_ARRAY[i]);
		_delay_us(1);
	}

}