



// #include<avr/io.h>
// #include<avr/interrupt.h>
// #include<util/delay.h>
// #include<avr/power.h>

// #include "reg_defs_t.h"
// #include "4D_7S.h"
// #include "pinDefines.h"
// #include "config.h"


// #define 	DEBOUNCE_DELAY 	1500
// #define 	OPR_SECTION    	4 /* Entire Operation Sections */ 



// volatile static uint8_t hour = 7;
// volatile static uint8_t minute = 54; 
// volatile static uint8_t seconds = 0;

// volatile static uint8_t button_state = 0;
// volatile static uint8_t button_click = 0;

// volatile static uint8_t button_flag = 0;
// volatile static uint16_t isr_flag = 0;

// volatile static uint8_t power_on = 0;
// volatile static uint8_t ovf_counter = 0;
// volatile static uint16_t click = 0;

// volatile static uint16_t display_number = 0;


// uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


// static inline void initTimer0(void);
// static inline void init4D_7S(void);
// static inline void endRun(void);


// /* ISR for updating the Time and date */
// ISR(_TIMER0_COMPA_){
// 	ovf_counter = (ovf_counter + 1) % (F_OVERFLOW);

// 	if(!(ovf_counter)){
// 		seconds = (seconds + 1) % 60;
// 		power_on = (power_on + 1) % OPR_TIME;

// 		if(!(seconds)){
// 			minute = (minute + 1) % 60;

// 			if(!(minute)){
// 				hour = (hour + 1) % 12;

// 				if(!(hour)){
// 					hour = 12;
// 				}
// 			}

// 			display_number = (hour*100) + (minute);
// 		}
// 	}

// 	if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// 		isr_flag++;
// 	}

// 	if(isr_flag){

// 		if(bit_is_set(PB_PIN, PUSH_BUTTON)){
// 			button_flag = 1;
// 			display_number = isr_flag;
// 			isr_flag = 0;
// 		}
// 	}
// }



// int main(void){

// 	initTimer0();

// 	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 1);
// 	setPin(_4D_7S_Ground); 

// 	PB_DDR &= ~(1 << PUSH_BUTTON);
// 	PB_PORT |= (1 << PUSH_BUTTON);

// 	display_number = (hour*100) + (minute);

// 	while(1){

// 		if(button_flag){

// 			button_flag = 0;
// 			power_on = 1;
// 			button_state = 1;
// 		}

// 		if(button_state){


// 			switch(button_click){
// 				case 0:{
// 					DISPLAY_wChar(0x640, click);
// 					break;
// 				}
// 				case 1:{
// 					DISPLAY_wChar(0x5B40, click);
// 					break;
// 				}
// 				case 2:{
// 					DISPLAY_flick(display_number, 1234, 1);
// 					break;
// 				}
// 				case 3:{
// 					DISPLAY(2356);
// 				}
// 			}

// 			init4D_7S();

// 			button_click = (button_click + 1) % (OPR_SECTION);

// 			button_state = 0;
// 		}

// 		if(!power_on){
// 			// DISPLAY_reset();
// 			endRun();
// 		}

// 	}

// 	return 0;
// }



// static inline void initTimer0(void){

// 	_OCR0A_ = (uint8_t)((F_CPU / (1024UL * 125UL)) - 1);

// 	_TCR0A_ |= (1 << _WGM01_);
// 	_TCR0B_ |= (1 << _CS02_) | (1 << _CS00_);

// 	_TIMSK0_ |= (1 << _OCIE0A_);

// 	sei();
// }


// static inline void init4D_7S(void){

// 	LED_LIVE_DDR = (0xff);
// 	LED_GROUND_DDR |= (0xf);
// }


// static inline void endRun(void){

// 	LED_LIVE_DDR &= ~(0xff);
// 	LED_GROUND_DDR &= ~(0xf);

// 	power_on = 0;
// 	button_click = 0;
// 	button_state = 0;
// 	button_flag = 0;
// 	isr_flag = 0;
// }