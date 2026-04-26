




#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>

#include "4D_7S.h"
#include "DHT_11.h"
#include "pinDefines.h"


/* ISR (On PORTB) From the DHT_11.h setup */
ISR(PCINT0_vect){
 
	DHT_HandleSignal();
}



uint8_t LED_ARRAY_BIT[] = {LA1, LA2, LA3, LA4};

uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


static inline initLED_ARRAY();
static inline init4D_7S();
static inline initADC_POT();


int main(void){

	/* PushButton Setup */
	BUTTON_PORT |= (1 << BUTTON);
	
	/* LED_ARRAY Setup */
	initLED_ARRAY();

	/* 4D_7S Display Setup */
	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
	setPin(_4D_7S_Ground);
	init4D_7S();

	/* DHT_11 Setup */
	DHT_Init(DHT_PORT, DHT_PIN);

	/* ADC Setup for POT */
	initADC_POT();

	/* Buzzer Setup */
	BUZZER_DDR |= (1 << BUZZER);


	while(1){

		

	}

	return 0;
}


static inline initLED_ARRAY(){

	LED_DDR |= (0x3C);
}


static inline init4D_7S(){

	LED_LIVE_DDR |= (0xff);
	LED_GROUND_DDR |= (0xf);
}


static inline initADC_POT(){

	ADMUX |= (1 << REFS0);
	ADMUX |= (1 << ADLAR); /* Read only ADCH and not ADC */

	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}











