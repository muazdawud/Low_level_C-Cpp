

/*
	This file ocntains my first servo tests
	*/

#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/atomic.h>
#include<util/delay.h>

#include "USART.h"


#define  PULSE_MIN  2000
#define  PULSE_MID  3000
#define  PULSE_MAX  4000

uint16_t delay_value = 0;

// ISR(TIMER1_COMPA_vect){

// 	PORTB |= (1 << PB1);
// 	_delay_us(delay_value);
// 	PORTB &= ~(1 << PB1);
// }


static inline uint16_t getNumber16(void);

static inline void initTimer(void){

	TCCR1A |= (1 << COM1A1);
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);

	TCCR1B |= (1 << CS11);

	// TIMSK1 |= (1 << OCIE1A);

	ICR1 = 40000;

	// OCR1A = PULSE_MID; 

	// sei();
}


static void showOff(void){

	// ATOMIC_BLOCK(ATOMIC_RESTORESTATE){

		printString("Servo in Center\r\n");
		// PORTB |= (1 << PB1);
		// _delay_us(PULSE_MID);
		// PORTB &= ~(1 << PB1);
		OCR1A = PULSE_MID;
		_delay_ms(1500);

		printString("Servo Clockwise Max\r\n");
		// PORTB |= (1 << PB1);
		// _delay_us(PULSE_MAX);
		// PORTB &= ~(1 << PB1);
		OCR1A = PULSE_MAX;
		_delay_ms(1500);

		printString("Servo Counter-Clockwise Max\r\n");
		// PORTB |= (1 << PB1);
		// _delay_us(PULSE_MIN);
		// PORTB &= ~(1 << PB1);
		OCR1A = PULSE_MIN;
		_delay_ms(1500);

		printString("Servo in Center\r\n");
		// PORTB |= (1 << PB1);
		// _delay_us(PULSE_MID);
		// PORTB &= ~(1 << PB1);
		OCR1A = PULSE_MID;
		_delay_ms(1500);

	// }
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

		printString("Enter a number between 2000-4000\r\n");

		input = getNumber16();
		OCR1A = input;

		DDRB |= (1 << PB1);

		_delay_ms(1000);
	    printString("Releasing...\r\n");

	    while (TCNT1 < 15000){}
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