#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>
#include "USART.h"
#include "pinDefines.h"

#define DISCHARGE 50
#define THRESHOLD 500
#define TX_BUFFER 32

volatile char mainBuffer[TX_BUFFER];
volatile uint8_t txWritePtr, txReadPtr;

volatile uint16_t charge_value;

ISR(PCINT1_vect){

    if (PINC & (1 << CAP_SENSOR)) {
        charge_value++;

        CAP_SENSOR_DDR |= (1 << CAP_SENSOR);

        CAP_SENSOR_DDR &= ~(1 << CAP_SENSOR);
    }

    PCIFR |= (1 << PCIF1);
}

ISR(USART_UDRE_vect){
	if(txWritePtr != txReadPtr){

		UDR0 = mainBuffer[txReadPtr];

		txReadPtr = (txReadPtr + 1) % TX_BUFFER;

	}else{

		UCSR0B &= ~(1 << UDRIE0);
	}
	
}

inline void initPCI(void){
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT9);
}

static inline void transferByte(char buffer){
	uint8_t nextPtr = (txWritePtr + 1) % TX_BUFFER;
    
    while (nextPtr == txReadPtr); 

    mainBuffer[txWritePtr] = buffer;
    txWritePtr = nextPtr;

	UCSR0B |= (1 << UDRIE0);
}

static void printWrd(uint16_t num){
	char buf[TX_BUFFER];
	int8_t i = 0;

	do{
		buf[i++] = (num % 10) + '0';
		num /= 10;
	}while(num > 0);

	while(i){
		transferByte(buf[--i]);
	}
}

static void printStr(const char str[]){
	for(int8_t i = 0; str[i] != '\0'; i++){
		transferByte(str[i]);
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