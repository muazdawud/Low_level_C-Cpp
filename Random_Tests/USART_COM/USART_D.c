/*
 * USART_D Library - High-performance USART communication
 * * Copyright (c) 2026 Dauda Muazu Sulaiman
 * All rights reserved.
 * * This software is licensed under the MIT License.
 * See the LICENSE file in the project root for full license information.
 */



#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/setbaud.h>
#include<util/delay.h>
#include <stdarg.h>

#include "USART_D.h"

#define TX_BUFFER 32
#define RX_BUFFER 64

volatile uint8_t txReadPtr = 0, txWritePtr = 0;
volatile char tx_buf[TX_BUFFER];
volatile char rx_buf[RX_BUFFER];
volatile uint8_t rx_end_flag = 0;
volatile uint8_t rxReadPtr = 0;



void USART_begin(void);
char USART_receive(void);
void USART_flush(void);
static void printNumber(int16_t num);
static inline void transferByte(char buffer);
void USART_print(const char buffer[], ...);



ISR(USART_UDRE_vect){
	if(txWritePtr != txReadPtr){

		UDR0 = tx_buf[txReadPtr];

		txReadPtr = (txReadPtr + 1) & (TX_BUFFER - 1);

	}else{

		UCSR0B &= ~(1 << UDRIE0);
	}
	
}



ISR(USART_RX_vect){

	if(!rx_end_flag){

		rx_buf[rxReadPtr] = UDR0;

		if(rx_buf[rxReadPtr] == '\r' || rxReadPtr >= 63){

			rx_buf[rxReadPtr+1] = '\0';
			rx_end_flag = 1;
			UCSR0B &= ~(1 << RXCIE0);
			TCCR2B = 0;
		}

		rxReadPtr = (rxReadPtr + 1) & (RX_BUFFER - 1);
	}else{

		UCSR0B &= ~(1 << RXCIE0);
		TCCR2B = 0;
	}
}



ISR(TIMER2_COMPA_vect){

	rx_buf[RX_BUFFER] = '\0';
	rx_end_flag = 1;
	UCSR0B &= ~(1 << RXCIE0);
	TCCR2B = 0;
}



static inline void initTIMER_2(void) {
    #if defined(TCCR2A) && defined(TIMSK2)
    	// MODERN (ATmega328P, 168, 2560, etc.)
        OCR2A = (uint8_t)((F_CPU / 1024) - 1);

		TCCR2A |= (1 << WGM21);
		TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);

		TIMSK2 |= (1 << OCIE2A);
    #elif defined(TCCR2) && defined(TIMSK)
		// LEGACY (ATmega8, 16, 32,  etc.)
        OCR2 = (uint8_t)((F_CPU / 1024) - 1);

        TCCR2 |= (1 << WGM21);
		TCCR2 |= (1 << CS22) | (1 << CS21) | (1 << CS20);

		TIMSK |= (1 << OCIE2);
    #else
        #error "This MCU is not supported by the 4D_7S library yet!"
    #endif
}



void USART_begin(void){

	UBRR0H = UBRRH_VALUE;
	UBRR0L = UBRRL_VALUE;

	#if USE_2X
	UCSR0A |= (1 << U2X0);
	#else
	UCSR0A &= ~(1 << U2X0);
	#endif

	UCSR0B |= (1 << TXEN0) | (1 << RXEN0);
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	
	sei();
}



char USART_getByte(void){

	loop_until_bit_is_set(UCSR0A, RXC0);

	char receivedByte = UDR0;

	transferByte(receivedByte);

	return receivedByte;
}



const char* USART_getString(void){

	 initTIMER_2();

	 UCSR0B |= (1 << RXCIE0);

	 TCNT2 = 0;
	 sei();

	 while(!rx_end_flag){};

	 return rx_buf;
}



void USART_flush(void){

	unsigned char dummy;

	while(bit_is_set(UCSR0A, RXC0)){
		dummy = UDR0;
	}
}



static inline void transferByte(char buffer){

	uint8_t nextPtr = (txWritePtr + 1) & (TX_BUFFER - 1);
    
    while (nextPtr == txReadPtr);

    tx_buf[txWritePtr] = buffer;
    txWritePtr = nextPtr;

	UCSR0B |= (1 << UDRIE0);
}



static void printNumber(int16_t num){

	char buf[6];
	int8_t i = 0;

	if(num < 0){
		num *= -1;
		transferByte('-');
	}

	do{
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}while(num > 0);

	while(i){
		transferByte(buf[--i]);
	}
}
	


void USART_print(const char buffer[], ...){

	va_list bytes;
	va_start(bytes, buffer);

	//char *i;

	for(uint8_t i = 0; buffer[i] != '\0'; i++){

		if(buffer[i] != '%'){
			transferByte(buffer[i]);

			continue;
		}

		i++;  // *i == '%', checking the next character

		switch(buffer[i]){
			case 'd': {//an integer is encountered
				int16_t number = va_arg(bytes, int);
	
				printNumber(number);
				break;
			}
			case 'c': {//a character is encountered
				char character = (char)va_arg(bytes, int);
	
				transferByte(character);
				break;
			}
			case 's': {//a string is encountered
				char *string = va_arg(bytes, char*);
	
				while(*string){
					transferByte(*string++);
				}
				break;
			}
			case '%': {//a literal '%' character is encountered
				transferByte('%');
				break;
			}
			default: {//specifier can't be identified
				transferByte(buffer[i]);
				break;
			}
		}
	}

	va_end(bytes);
} 