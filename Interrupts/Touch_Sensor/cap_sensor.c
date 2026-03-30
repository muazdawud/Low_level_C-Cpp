#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>
#include "USART.h"
#include "pinDefines.h"

#define DISCHARGE 50
#define THRESHOLD 500

volatile uint8_t i;
volatile uint8_t bufSize;
volatile uint8_t mainBuffer;
volatile uint8_t txWritePtr, txReadPtr;

volatile uint16_t charge_value;

ISR(PCINT1_vect){

    if (PINC & (1 << CAP_SENSOR)) {
        charge_value++;

        CAP_SENSOR_DDR |= (1 << CAP_SENSOR);
        _delay_us(1);

        CAP_SENSOR_DDR &= ~(1 << CAP_SENSOR);
    }

    PCIFR |= (1 << PCIF1);
}

ISR(USART_UDRE_vect){
	if(txWritePtr != txReadPtr){
		UDR0 = mainBuffer;

		txWritePtr = (txWritePtr + 1) % bufSize;

	}else{
		UCSR0B &= ~(1 << UDRIE0);
	}
	
}

void initPCI(void){
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT9);
}

void transferByte(uint8_t buffer){
	mainBuffer = buffer;

	txWritePtr = (txWritePtr + 1) % bufSize;

	UCSR0B |= (1 << UDRIE0);
}

void printWrd(uint16_t num){
	do{

	}while();
}

void printStr(const char str[]){
	bufSize = sizeof(str);

	for(i = 0; i < bufSize; i++){
		tranferByte(str[i]);
	}
}

int main(void){

	clock_prescale_set(clock_div_1);
	initPCI();
	initUSART();


	LED_DDR |= 0x3f;
	MCUCR |= (1 << PUD);
	CAP_SENSOR_PORT |= (1 << CAP_SENSOR);
	
	printString("====[ TOUCH SENSOR ]====\r\n\r\n");

	while(1){
		charge_value = 0;

		CAP_SENSOR_DDR &= ~(1 << CAP_SENSOR);

		sei();
		_delay_ms(DISCHARGE);
		cli();

		if(charge_value < THRESHOLD){
			LED_PORT = 0x3f;
		}else{
			LED_PORT = 0x0;
		}

		printWrd(charge_value);
		printStr("\r\n");


        CAP_SENSOR_DDR |= (1 << CAP_SENSOR);
	}

	return 0;
}