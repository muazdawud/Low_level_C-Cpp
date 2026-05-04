



#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>

#include "reg_defs_t.h"
#include "4D_7S.h"
#include "DHT_11.h"
#include "pinDefines.h"
#include "config.h"


#define 	DEBOUNCE_DELAY 	2
#define 	OPR_SECTION    	3 /* Entire Operation Sections */ 



volatile static uint8_t hour = 7;
volatile static uint8_t minute = 54; 
volatile static uint8_t seconds = 0;

volatile static uint8_t button_state = 0;
volatile static uint8_t button_click = 0;
volatile static uint8_t power_on = 0;
volatile static uint8_t ovf_counter = 0;

static uint8_t temp_ = 0;
static uint8_t humd_ = 0;

volatile static uint16_t display_number = 0;


uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


static inline void initTimer0(void);
static inline void init4D_7S(void);
// static void mainRun(void);
static inline void endRun(void);



/* ISR (On PORTB) From the DHT_11.h setup */
ISR(PCINT0_vect){
 
	DHT_HandleSignal();
}


/* Push Button Interrupt */
ISR(PCINT1_vect){

	button_state = 1;
}


/* ISR for updating the Time and date */
ISR(_TIMER0_COMPA_){
	ovf_counter = ((F_CPU / 1024UL) / _OCR2A_);

	if(!(ovf_counter)){
		seconds = (seconds + 1) % 60;
		power_on = (power_on + 1) % OPR_TIME;

		if(!(seconds)){
			minute = (minute + 1) % 60;

			if(!(minute)){
				hour = (hour + 1) % 12;

				if(!(hour)){
					hour = 12;
				}

				temp_ = DHT_Get_Temp();
				humd_ = DHT_Get_Humidity();
			}
		}

		display_number = (hour*100) + (minute);
	}
}



int main(void){

	// PB_DDR &= ~(1 << PUSH_BUTTON);
	// PB_PORT |= (1 << PUSH_BUTTON);

	PCICR |= (1 << PCIE1);
	PCMSK1 |= (1 << PUSH_BUTTON);

	/* 4D_7S Display Setup */
	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
	setPin(_4D_7S_Ground); 
 
	/* DHT_11 Setup */
	DHT_Init(DHT_PORT, DHT_PIN);

	initTimer0();

	temp_ = DHT_Get_Temp();
	humd_ = DHT_Get_Humidity();
	display_number = (hour*100) + (minute);

	while(1){

		if(button_state){

			button_state = 0;

			if(bit_is_clear(PB_PIN, PUSH_BUTTON)){
				// cli();
				// _delay_ms(DEBOUNCE_DELAY);
				// sei();
				if(bit_is_clear(PB_PIN, PUSH_BUTTON)){
					power_on = 1;
				}
			}

			if(power_on == 1){

				init4D_7S();

				switch(button_click){
					case 0:{
						DISPLAY(display_number);
						break;
					}
					case 1:{
						DISPLAY_wChar(0x7840, temp_);
						break;

					}
					case 2:{
						DISPLAY_wChar(0x7440, humd_);
						break;
					}
				}

				button_click = (button_click + 1) % (OPR_SECTION);
			}
		}

		if(!power_on){
			endRun();
		}

	}

	return 0;
}



static inline void initTimer0(void){

	_OCR0A_ = (uint8_t)((F_CPU / (1024UL * 125UL)) - 1);

	_TCR0A_ |= (1 << _WGM01_);
	_TCR0B_ |= (1 << _CS02_) | (1 << _CS00_);

	_TIMSK0_ |= (1 << _OCIE0A_);

	sei();
}


static inline void init4D_7S(void){

	LED_LIVE_DDR |= (0xff);
	LED_GROUND_DDR |= (0xf);
}


// static void mainRun(void){

// 	if(power_on == 1){

		
// 	}

// 	if(power_on){
// 		mainRun();
// 	}

// 	endRun();
// }


static inline void endRun(void){

	LED_LIVE_DDR &= ~(0xff);
	LED_GROUND_DDR &= ~(0xf);

	power_on = 0;
	button_click = 0;
	button_state = 0;
}