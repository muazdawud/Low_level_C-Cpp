

/*
	This file ocntains my first servo tests
	*/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/atomic.h>
#include<util/delay.h>

#include "USART.h"


#define  F_OCPWM  50
#define  PRESCALER  64
#define  TOP  ((F_CPU / (F_OCPWM * PRESCALER)) - 1)


#define  PULSE_MIN  ((TOP / 20) * 1)
#define  PULSE_MID  ((TOP / 20) * 1.5)
#define  PULSE_MAX  ((TOP / 20) * 2)

uint16_t delay_value = 0;

static inline uint16_t getNumber16(void);

static inline void initTimer(void){

	TCCR1A |= (1 << COM1A1);

	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	TCCR1B |= (1 << CS11) | (1 << CS10);

	ICR1 = TOP;
}


static void showOff(void){

	printString("Servo in Center\r\n");
	OCR1A = PULSE_MID;
	_delay_ms(1500);

	printString("Servo Clockwise Max\r\n");
	OCR1A = PULSE_MAX;
	_delay_ms(1500);

	printString("Servo Counter-Clockwise Max\r\n");
	OCR1A = PULSE_MIN;
	_delay_ms(1500);

	printString("Servo in Center\r\n");
	OCR1A = PULSE_MID;
	_delay_ms(1500);
}


int main(void){

	initTimer();
	initUSART();

	printString("\r\n=== SERVO TEST ===\r\n");

	uint16_t input = 0;

	DDRB |= (1 << PB1);
	showOff();

	while(1){

		DDRB &= ~(1 << PB1);

		printString("Enter a number between 128-620\r\n");

		input = getNumber16();
		OCR1A = input;

		DDRB |= (1 << PB1);

		_delay_ms(1000);
	    printString("Releasing...\r\n");

	    while (TCNT1 < (PULSE_MAX * 2)){}
	}

	return 0;
}

static inline uint16_t getNumber16(void) {
  // Gets a PWM value from the serial port.
  // Reads in characters, turns them into a number
  char thousands = '0';
  char hundreds = '0';
  char tens = '0';
  char ones = '0';
  char thisChar = '0';

  do {
    thousands = hundreds;                        /* shift numbers over */
    hundreds = tens;
    tens = ones;
    ones = thisChar;
    thisChar = receiveByte();                   /* get a new character */
    transmitByte(thisChar);                                    /* echo */
  } while (thisChar != '\r');

  transmitByte('\n');                                       /* newline */
  return (1000 * (thousands - '0') + 100 * (hundreds - '0') +
          10 * (tens - '0') + ones - '0');
}