



// #include<avr/io.h>
// #include<avr/interrupt.h>
// #include<util/delay.h>
// #include<avr/power.h>

// #include "reg_defs_t.h"
// #include "4D_7S.h"
// // #include "DHT_11.h"
// #include "pinDefines.h"
// #include "config.h"


// #define 	DEBOUNCE_DELAY 	5
// #define 	OPR_SECTION    	3 /* Entire Operation Sections */ 



// volatile static uint8_t hour = 7;
// volatile static uint8_t minute = 7; 
// volatile static uint8_t seconds = 0;

// volatile static uint8_t button_state = 0;
// volatile static uint8_t button_click = 0;
// volatile static uint8_t power_on = 0;
// volatile static uint8_t ovf_counter = 0;

// // volatile static uint8_t temperature = 0;
// // volatile static uint8_t humidity = 0;

// volatile static uint16_t display_number = 0;


// uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


// static inline void initTimer0(void);
// static inline void init4D_7S(void);
// static void mainRun(void);
// static inline void endRun(void);



// // /* ISR (On PORTB) From the DHT_11.h setup */
// // ISR(PCINT0_vect){
 
// // 	DHT_HandleSignal();
// // }


// /* Push Button Interrupt */
// ISR(PCINT1_vect){

// 	if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// 		// _delay_ms(DEBOUNCE_DELAY);
// 		if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// 			button_state = 1;
// 			power_on = 1;
// 			button_click = (button_click + 1) % (OPR_SECTION);
// 		}

// 	}
// }


// /* ISR for updating the Time and date */
// ISR(_TIMER0_OVF_){
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
// 		}

// 		display_number = (hour*100) + (minute);
// 	}
// }



// int main(void){

// 	PB_DDR &= ~(1 << PUSH_BUTTON);
// 	PB_PORT |= (1 << PUSH_BUTTON);

// 	PCICR |= (1 << PCIE1);
// 	PCMSK1 |= (1 << PUSH_BUTTON);

// 	/* 4D_7S Display Setup */
// 	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
// 	setPin(_4D_7S_Ground);

// 	// // 	/* DHT_11 Setup */
// 	// DHT_Init(DHT_PORT, DHT_PIN);

// 	initTimer0();

// 	// init4D_7S();
// 	// endRun();

// 	while(1){

// 		if(button_state){

// 			button_state = 0;
// 			mainRun();
// 		}

// 	}

// 	return 0;
// }



// static inline void initTimer0(void){

// 	_TCR0B_ |= (1 << _CS02_);
// 	_TIMSK0_ |= (1 << TOIE0);

// 	sei();
// }


// static inline void init4D_7S(void){

// 	// temperature = DHT_Get_Temp();
// 	// humidity = DHT_Get_Humidity();

// 	LED_LIVE_DDR |= (0xff);
// 	LED_GROUND_DDR |= (0xf);
// }


// static void mainRun(void){

// 	init4D_7S();

// 	DISPLAY(display_number);

// 	while(power_on){
// 	}

// 	endRun();
// }


// static inline void endRun(void){

// 	LED_LIVE_DDR &= ~(0xff);
// 	LED_GROUND_DDR &= ~(0xf);

// 	power_on = 0;
// 	button_click = 0;
// 	button_state = 0;
// }