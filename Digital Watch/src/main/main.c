



#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>

#include "reg_defs_t.h"
#include "4D_7S.h"
#include "DHT_11.h"
#include "pinDefines.h"
#include "config.h"


#define 	DEBOUNCE_DELAY 	1500
#define 	OPR_SECTION    	4 /* 
					Entire Operation Section <Including time[1],
					temperature[2], humidity[3] and date[4]>.
					*/ 
#define 	SETUP_SECTION	5 /* 
					Entire Setup Section <Including hour[1],
					minute[2], day[3], month[4] and year[5]>.
					*/ 



volatile static uint8_t setup_flag = 0;

volatile static uint8_t hour = 7;
volatile static uint8_t minute = 54; 
volatile static uint8_t seconds = 0;
volatile static uint8_t day = 7;
volatile static uint8_t month = 5;

volatile static uint8_t button_state = 0;
volatile static uint8_t button_click = 0;

volatile static uint8_t button_flag = 0;
volatile static uint8_t isr_flag = 0;

volatile static uint8_t power_on = 0;
volatile static uint8_t ovf_counter = 0;

static uint8_t temp_ = 0;
static uint8_t humd_ = 0;
volatile static uint8_t update_tnh = 0;

volatile static uint16_t display_number = 0;
volatile static uint8_t display_check = 0;


uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


static inline void initTimer0(void);
static inline void init4D_7S(void);
static inline void endRun(void);

static void setupWatch(void);


/* ISR (On PORTB) From the DHT_11.h setup */
ISR(PCINT0_vect){
 
	DHT_HandleSignal();
}


// /* Push Button Interrupt */
// ISR(PCINT1_vect){

// 	button_state = 1;
// }


/* ISR for updating the Time and date */
ISR(_TIMER0_COMPA_){
	ovf_counter = (ovf_counter + 1) % (F_OVERFLOW);

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

				update_tnh = 1;
			}
		}
	}

	if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

		isr_flag = (isr_flag + 1) % (OPR_SECTION + SETUP_SECTION);
	}

	if(isr_flag < OPR_SECTION){

		if(bit_is_set(PB_PIN, PUSH_BUTTON)){
			button_flag = 1;
			setup_flag = 0;
		}
	}
	else if(isr_flag < SETUP_SECTION){

		if(bit_is_set(PB_PIN, PUSH_BUTTON)){
			setup_flag = 1;
			button_flag = 0;
		}
	}
}



int main(void){

	initTimer0();

	/* 4D_7S Display Setup */
	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
	setPin(_4D_7S_Ground); 
 
	/* DHT_11 Setup */
	DHT_Init(DHT_PORT, DHT_PIN);

	temp_ = DHT_Get_Temp();
	humd_ = DHT_Get_Humidity();

	PB_DDR &= ~(1 << PUSH_BUTTON);
	PB_PORT |= (1 << PUSH_BUTTON);

	while(1){

		if(button_flag){
			button_flag = 0;
			power_on = 1;
			button_state = 1;
		}

		if(setup_flag){

			setupWatch();
		}

		if(button_state){

			DISPLAY_reset();

			switch(button_click){
				case 0:{
					display_number = (hour*100) + (minute);
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
				case 3:{
					display_number = (day*100) + (month);
					DISPLAY_nDP(display_number, 2);
				}
			}

			init4D_7S();

			button_click = (button_click + 1) % (OPR_SECTION);

			button_state = 0;
		}

		if(update_tnh){

			temp_ = DHT_Get_Temp();
			humd_ = DHT_Get_Humidity();

			update_tnh = 0;
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


static inline void endRun(void){

	LED_LIVE_DDR &= ~(0xff);
	LED_GROUND_DDR &= ~(0xf);

	setup_flag = 0;

	power_on = 0;
	button_click = 0;
	button_state = 0;
	button_flag = 0;
	isr_flag = 0;
}


static void setupWatch(void){

	while(power_on){

	}
}