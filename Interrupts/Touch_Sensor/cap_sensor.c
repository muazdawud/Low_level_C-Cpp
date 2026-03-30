#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>
#include "USART.h"
#include "pinDefines.h"

#define DISCHARGE 50
#define THRESHOLD 500

volatile uint16_t charge_value;

ISR(PCINT1_vect){

    if (PINC & (1 << CAP_SENSOR)) {
        charge_value++;

        CAP_SENSOR_DDR |= (1 << CAP_SENSOR);   // Output
        CAP_SENSOR_PORT &= ~(1 << CAP_SENSOR); // LOW
        
        _delay_us(1); 

        CAP_SENSOR_DDR &= ~(1 << CAP_SENSOR);  // Input
    }

    PCIFR |= (1 << PCIF1);
}

void initPCI(void){
	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PCINT9);
}

int main(void){

	clock_prescale_set(clock_div_1);
	initPCI();
	initUSART();


	LED_DDR |= 0x3f;
	
	printString("====[ TOUCH SENSOR ]====\r\n\r\n");

	while(1){
		charge_value = 0;

		CAP_SENSOR_PORT &= ~(1 << CAP_SENSOR);
		CAP_SENSOR_DDR |= (1 << CAP_SENSOR);
		_delay_us(3);

		CAP_SENSOR_PORT |= (1 << CAP_SENSOR);
		CAP_SENSOR_DDR &= ~(1 << CAP_SENSOR);

		sei();
		_delay_ms(DISCHARGE);
		cli();

		if(charge_value < THRESHOLD){
			LED_PORT = 0x3f;
		}else{
			LED_PORT = 0x0;
		}

		printWord(charge_value);
		printString("\r\n");
	}

	return 0;
}