
#ifndef FOURD_7S_H
#define FOURD_7S_H

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

extern volatile uint8_t *LED_DISPLAY_PORT;
extern volatile uint8_t *LED_DISPLAY_GROUND;

void setPin(const uint8_t ground[]);

void initLED_DISPLAY(volatile uint8_t *PORT_1, volatile uint8_t *PORT_2);

void DISPLAY(uint16_t num);

#endif