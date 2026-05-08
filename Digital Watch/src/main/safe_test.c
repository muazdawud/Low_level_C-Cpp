
// // // /*															
// // // 													/
// // // 				SAFE TEST 1 (RESTORE POINT)			/
// // // 													/
// // // */				


// // // // #include<avr/io.h>
// // // // #include<avr/interrupt.h>
// // // // #include<util/delay.h>
// // // // #include<avr/power.h>

// // // // #include "reg_defs_t.h"
// // // // #include "4D_7S.h"
// // // // // #include "DHT_11.h"
// // // // #include "pinDefines.h"
// // // // #include "config.h"


// // // // #define 	DEBOUNCE_DELAY 	5
// // // // #define 	OPR_SECTION    	3 /* Entire Operation Sections */ 



// // // // volatile static uint8_t hour = 7;
// // // // volatile static uint8_t minute = 7; 
// // // // volatile static uint8_t seconds = 0;

// // // // volatile static uint8_t button_state = 0;
// // // // volatile static uint8_t button_click = 0;
// // // // volatile static uint8_t power_on = 0;
// // // // volatile static uint8_t ovf_counter = 0;

// // // // // volatile static uint8_t temperature = 0;
// // // // // volatile static uint8_t humidity = 0;

// // // // volatile static uint16_t display_number = 0;


// // // // uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


// // // // static inline void initTimer0(void);
// // // // static inline void init4D_7S(void);
// // // // static void mainRun(void);
// // // // static inline void endRun(void);



// // // // // /* ISR (On PORTB) From the DHT_11.h setup */
// // // // // ISR(PCINT0_vect){
 
// // // // // 	DHT_HandleSignal();
// // // // // }


// // // // /* Push Button Interrupt */
// // // // ISR(PCINT1_vect){

// // // // 	if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// // // // 		// _delay_ms(DEBOUNCE_DELAY);
// // // // 		if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// // // // 			button_state = 1;
// // // // 			power_on = 1;
// // // // 			button_click = (button_click + 1) % (OPR_SECTION);
// // // // 		}

// // // // 	}
// // // // }


// // // // /* ISR for updating the Time and date */
// // // // ISR(_TIMER0_OVF_){
// // // // 	ovf_counter = (ovf_counter + 1) % (F_OVERFLOW);

// // // // 	if(!(ovf_counter)){
// // // // 		seconds = (seconds + 1) % 60;
// // // // 		power_on = (power_on + 1) % OPR_TIME;

// // // // 		if(!(seconds)){
// // // // 			minute = (minute + 1) % 60;

// // // // 			if(!(minute)){
// // // // 				hour = (hour + 1) % 12;

// // // // 				if(!(hour)){
// // // // 					hour = 12;
// // // // 				}
// // // // 			}
// // // // 		}

// // // // 		display_number = (hour*100) + (minute);
// // // // 	}
// // // // }



// // // // int main(void){

// // // // 	PB_DDR &= ~(1 << PUSH_BUTTON);
// // // // 	PB_PORT |= (1 << PUSH_BUTTON);

// // // // 	PCICR |= (1 << PCIE1);
// // // // 	PCMSK1 |= (1 << PUSH_BUTTON);

// // // // 	/* 4D_7S Display Setup */
// // // // 	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
// // // // 	setPin(_4D_7S_Ground);

// // // // 	// // 	/* DHT_11 Setup */
// // // // 	// DHT_Init(DHT_PORT, DHT_PIN);

// // // // 	initTimer0();

// // // // 	// init4D_7S();
// // // // 	// endRun();

// // // // 	while(1){

// // // // 		if(button_state){

// // // // 			button_state = 0;
// // // // 			mainRun();
// // // // 		}

// // // // 	}

// // // // 	return 0;
// // // // }



// // // // static inline void initTimer0(void){

// // // // 	_TCR0B_ |= (1 << _CS02_);
// // // // 	_TIMSK0_ |= (1 << TOIE0);

// // // // 	sei();
// // // // }


// // // // static inline void init4D_7S(void){

// // // // 	// temperature = DHT_Get_Temp();
// // // // 	// humidity = DHT_Get_Humidity();

// // // // 	LED_LIVE_DDR |= (0xff);
// // // // 	LED_GROUND_DDR |= (0xf);
// // // // }


// // // // static void mainRun(void){

// // // // 	init4D_7S();

// // // // 	DISPLAY(display_number);

// // // // 	while(power_on){
// // // // 	}

// // // // 	endRun();
// // // // }


// // // // static inline void endRun(void){

// // // // 	LED_LIVE_DDR &= ~(0xff);
// // // // 	LED_GROUND_DDR &= ~(0xf);

// // // // 	power_on = 0;
// // // // 	button_click = 0;
// // // // 	button_state = 0;
// // // // }




// // // /*															
// // // 													/
// // // 				SAFE TEST 2 (RESTORE POINT)			/
// // // 													/
// // // */				


// // // // #include<avr/io.h>
// // // // #include<avr/interrupt.h>
// // // // #include<util/delay.h>
// // // // #include<avr/power.h>

// // // // #include "reg_defs_t.h"
// // // // #include "4D_7S.h"
// // // // #include "DHT_11.h"
// // // // #include "pinDefines.h"
// // // // #include "config.h"


// // // // #define 	DEBOUNCE_DELAY 	30
// // // // #define 	OPR_SECTION    	3 /* Entire Operation Sections */ 



// // // // volatile static uint8_t hour = 12;
// // // // volatile static uint8_t minute = 54; 
// // // // volatile static uint8_t seconds = 0;

// // // // volatile static uint8_t button_state = 0;
// // // // volatile static uint8_t button_click = 0;
// // // // volatile static uint8_t power_on = 0;
// // // // volatile static uint8_t ovf_counter = 0;

// // // // static uint8_t temp_ = 0;
// // // // static uint8_t humd_ = 0;

// // // // volatile static uint16_t display_number = 0;


// // // // uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


// // // // static inline void initTimer0(void);
// // // // static inline void init4D_7S(void);
// // // // // static void mainRun(void);
// // // // static inline void endRun(void);



// // // // /* ISR (On PORTB) From the DHT_11.h setup */
// // // // ISR(PCINT0_vect){
 
// // // // 	DHT_HandleSignal();
// // // // }


// // // // /* Push Button Interrupt */
// // // // ISR(PCINT1_vect){

// // // // 	// if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// // // // 	// 	//endRun();
// // // // 	// 	_delay_ms(DEBOUNCE_DELAY);
// // // // 	// 	if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// // // // 			button_state = 1;
// // // // 	// 		power_on = 1;
// // // // 	// 		// button_click = (button_click + 1) % (OPR_SECTION);
// // // // 	// 	}

// // // // 	// }
// // // // }


// // // // /* ISR for updating the Time and date */
// // // // ISR(_TIMER0_OVF_){
// // // // 	ovf_counter = (ovf_counter + 1) % (F_OVERFLOW);

// // // // 	if(!(ovf_counter)){
// // // // 		seconds = (seconds + 1) % 60;
// // // // 		power_on = (power_on + 1) % OPR_TIME;

// // // // 		if(!(seconds)){
// // // // 			minute = (minute + 1) % 60;

// // // // 			if(!(minute)){
// // // // 				hour = (hour + 1) % 12;

// // // // 				if(!(hour)){
// // // // 					hour = 12;
// // // // 				}

// // // // 				temp_ = DHT_Get_Temp();
// // // // 				humd_ = DHT_Get_Humidity();
// // // // 			}
// // // // 		}

// // // // 		display_number = (hour*100) + (minute);
// // // // 	}
// // // // }



// // // // int main(void){

// // // // 	PB_DDR &= ~(1 << PUSH_BUTTON);
// // // // 	PB_PORT |= (1 << PUSH_BUTTON);

// // // // 	PCICR |= (1 << PCIE1);
// // // // 	PCMSK1 |= (1 << PUSH_BUTTON);

// // // // 	/* 4D_7S Display Setup */
// // // // 	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
// // // // 	setPin(_4D_7S_Ground); 
 
// // // // 	/* DHT_11 Setup */
// // // // 	DHT_Init(DHT_PORT, DHT_PIN);

// // // // 	initTimer0();

// // // // 	temp_ = DHT_Get_Temp();
// // // // 	humd_ = DHT_Get_Humidity();


// // // // 	while(1){

// // // // 		if(button_state){

// // // // 			// temp_ = DHT_Get_Temp();
// // // // 			// humd_ = DHT_Get_Humidity();
// // // // 			button_state = 0;

// // // // 			if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// // // // 				//endRun();
// // // // 				_delay_ms(DEBOUNCE_DELAY);
// // // // 				if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// // // // 					// button_state = 1;
// // // // 					power_on = 1;
// // // // 					// button_click = (button_click + 1) % (OPR_SECTION);
// // // // 				}
// // // // 			}

// // // // 			if(power_on == 1){
// // // // 				init4D_7S();

				
// // // // 				// mainRun();

// // // // 				switch(button_click){
// // // // 					case 0:{
// // // // 						DISPLAY(display_number);
// // // // 						break;
// // // // 					}
// // // // 					case 1:{
// // // // 						DISPLAY(temp_);
// // // // 						break;

// // // // 					}
// // // // 					case 2:{
// // // // 						DISPLAY(humd_);
// // // // 						break;
// // // // 					}
// // // // 				}

// // // // 				button_click = (button_click + 1) % (OPR_SECTION);
// // // // 			}
// // // // 		}

// // // // 		if(!power_on){
// // // // 			endRun();
// // // // 		}

// // // // 	}

// // // // 	return 0;
// // // // }



// // // // static inline void initTimer0(void){

// // // // 	_TCR0B_ |= (1 << _CS02_);
// // // // 	_TIMSK0_ |= (1 << TOIE0);

// // // // 	sei();
// // // // }


// // // // static inline void init4D_7S(void){

// // // // 	LED_LIVE_DDR |= (0xff);
// // // // 	LED_GROUND_DDR |= (0xf);
// // // // }


// // // // // static void mainRun(void){

// // // // // 	if(power_on == 1){

		
// // // // // 	}

// // // // // 	if(power_on){
// // // // // 		mainRun();
// // // // // 	}

// // // // // 	endRun();
// // // // // }


// // // // static inline void endRun(void){

// // // // 	LED_LIVE_DDR &= ~(0xff);
// // // // 	LED_GROUND_DDR &= ~(0xf);

// // // // 	power_on = 0;
// // // // 	button_click = 0;
// // // // 	button_state = 0;
// // // // }




// // // if(button_state){

// // // 			if(bit_is_clear(PB_PIN, PUSH_BUTTON)){
// // // 				// cli();
// // // 				_delay_us(DEBOUNCE_DELAY);
// // // 				// sei();
// // // 				if(bit_is_clear(PB_PIN, PUSH_BUTTON)){
// // // 					display_check = 1;
// // // 				}
// // // 			}

// // // 			if(display_check >= 1){

// // // 				display_check = 0;
// // // 				LED_LIVE_DDR &= ~(0xff);
// // // 				LED_GROUND_DDR &= ~(0xf);
// // // 				DISPLAY_reset();
// // // 				init4D_7S();

// // // 				switch(button_click){
// // // 					case 0:{
// // // 						DISPLAY(display_number);
// // // 						break;
// // // 					}
// // // 					case 1:{
// // // 						DISPLAY_wChar(0x7840, temp_);
// // // 						break;
// // // 					}
// // // 					case 2:{
// // // 						DISPLAY_wChar(0x7440, humd_);
// // // 						break;
// // // 					}
// // // 				}

// // // 				button_click = (button_click + 1) % (OPR_SECTION);
// // // 			}

// // // 			button_state = 0;
// // // 		}





// // /*															
// // 													/
// // 				SAFE TEST 3 (RESTORE POINT)			/
// // 													/
// // */



// // #include<avr/io.h>
// // #include<avr/interrupt.h>
// // #include<util/delay.h>
// // #include<avr/power.h>

// // #include "reg_defs_t.h"
// // #include "4D_7S.h"
// // #include "DHT_11.h"
// // #include "pinDefines.h"
// // #include "config.h"


// // #define 	DEBOUNCE_DELAY 	1500
// // #define 	OPR_SECTION    	4 /* Entire Operation Sections */ 



// // volatile static uint8_t hour = 7;
// // volatile static uint8_t minute = 54; 
// // volatile static uint8_t seconds = 0;
// // volatile static uint8_t day = 7;
// // volatile static uint8_t month = 5;

// // volatile static uint8_t button_state = 0;
// // volatile static uint8_t button_click = 0;

// // volatile static uint8_t button_flag = 0;
// // volatile static uint8_t isr_flag = 0;
// // // volatile static uint8_t click = 0;

// // volatile static uint8_t power_on = 0;
// // volatile static uint8_t ovf_counter = 0;

// // static uint8_t temp_ = 0;
// // static uint8_t humd_ = 0;
// // volatile static uint8_t update_tnh = 0;

// // volatile static uint16_t display_number = 0;
// // volatile static uint8_t display_check = 0;


// // uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


// // static inline void initTimer0(void);
// // static inline void init4D_7S(void);
// // // static void mainRun(void);
// // static inline void endRun(void);



// // /* ISR (On PORTB) From the DHT_11.h setup */
// // ISR(PCINT0_vect){
 
// // 	DHT_HandleSignal();
// // }


// // // /* Push Button Interrupt */
// // // ISR(PCINT1_vect){

// // // 	button_state = 1;
// // // }


// // /* ISR for updating the Time and date */
// // ISR(_TIMER0_COMPA_){
// // 	ovf_counter = (ovf_counter + 1) % (F_OVERFLOW);

// // 	if(!(ovf_counter)){
// // 		seconds = (seconds + 1) % 60;
// // 		power_on = (power_on + 1) % OPR_TIME;

// // 		if(!(seconds)){
// // 			minute = (minute + 1) % 60;

// // 			if(!(minute)){
// // 				hour = (hour + 1) % 12;

// // 				if(!(hour)){
// // 					hour = 12;
// // 				}

// // 				update_tnh = 1;
// // 			}
// // 		}
// // 	}

// // 	if(bit_is_clear(PB_PIN, PUSH_BUTTON)){

// // 		isr_flag++;
// // 	}

// // 	if(isr_flag){

// // 		if(bit_is_set(PB_PIN, PUSH_BUTTON)){
// // 			button_flag = 1;
// // 			isr_flag = 0;
// // 		}
// // 	}
// // }



// // int main(void){

// // 	initTimer0();

// // 	/* 4D_7S Display Setup */
// // 	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
// // 	setPin(_4D_7S_Ground); 
 
// // 	/* DHT_11 Setup */
// // 	DHT_Init(DHT_PORT, DHT_PIN);

// // 	temp_ = DHT_Get_Temp();
// // 	humd_ = DHT_Get_Humidity();

// // 	PB_DDR &= ~(1 << PUSH_BUTTON);
// // 	PB_PORT |= (1 << PUSH_BUTTON);

// // 	while(1){

// // 		if(button_flag){
// // 			button_flag = 0;
// // 			power_on = 1;
// // 			button_state = 1;
// // 		}

// // 		if(button_state){

// // 			DISPLAY_reset();

// // 			switch(button_click){
// // 				case 0:{
// // 					display_number = (hour*100) + (minute);
// // 					DISPLAY(display_number);
// // 					break;
// // 				}
// // 				case 1:{
// // 					DISPLAY_wChar(0x7840, temp_);
// // 					break;
// // 				}
// // 				case 2:{
// // 					DISPLAY_wChar(0x7440, humd_);
// // 					break;
// // 				}
// // 				case 3:{
// // 					display_number = (day*100) + (month);
// // 					DISPLAY_nDP(display_number, 2);
// // 				}
// // 			}

// // 			init4D_7S();

// // 			button_click = (button_click + 1) % (OPR_SECTION);

// // 			button_state = 0;
// // 		}

// // 		if(update_tnh){

// // 			temp_ = DHT_Get_Temp();
// // 			humd_ = DHT_Get_Humidity();

// // 			update_tnh = 0;
// // 		}

// // 		if(!power_on){
// // 			endRun();
// // 		}

// // 	}

// // 	return 0;
// // }



// // static inline void initTimer0(void){

// // 	_OCR0A_ = (uint8_t)((F_CPU / (1024UL * 125UL)) - 1);

// // 	_TCR0A_ |= (1 << _WGM01_);
// // 	_TCR0B_ |= (1 << _CS02_) | (1 << _CS00_);

// // 	_TIMSK0_ |= (1 << _OCIE0A_);

// // 	sei();
// // }


// // static inline void init4D_7S(void){

// // 	LED_LIVE_DDR |= (0xff);
// // 	LED_GROUND_DDR |= (0xf);
// // }


// // // static void mainRun(void){

// // // 	if(power_on == 1){

		
// // // 	}

// // // 	if(power_on){
// // // 		mainRun();
// // // 	}

// // // 	endRun();
// // // }


// // static inline void endRun(void){

// // 	LED_LIVE_DDR &= ~(0xff);
// // 	LED_GROUND_DDR &= ~(0xf);

// // 	power_on = 0;
// // 	button_click = 0;
// // 	button_state = 0;
// // 	button_flag = 0;
// // 	isr_flag = 0;
// // }



// /*															
// 													/
// 				4D_7S.c SAFE TEST 1 (RESTORE POINT)			/
// 													/
// */



// /*
//  * 4D_7S Library - High-performance 4-Digit 7-Segment Multiplexing
//  * * Copyright (c) 2026 Dauda Muazu Sulaiman
//  * Copyright (c) 2026 KibrisOrder                <https://ss.kibrisorder.com>
//  * * Author: Dauda Muazu Sulaiman
//  * Organization: KibrisOrder
//  * All rights reserved.
//  * * This software is licensed under the MIT License.
//  * * See the LICENSE file in the project root for full license information.
//  * 
//  * See the README file in the project root to understand how to use the software.
//  */


// #include<avr/io.h>
// #include<avr/interrupt.h>
// #include<util/delay.h>

// #include "4D_7S.h"
// #include "reg_defs_t.h"
// #include "pinDefines.h"

// #define GROUND_SIZE 4

// volatile uint8_t *LED_DISPLAY_PORT;
// volatile uint8_t *LED_DISPLAY_GROUND;

// static uint8_t groundCount = 0;

// static uint8_t pattern = 0;

// static uint8_t numberArray[GROUND_SIZE];

// static uint8_t GROUND_ARRAY[GROUND_SIZE];

// static uint8_t DPF[GROUND_SIZE] = {0, 0, 0, 0};

// static uint8_t temp_DPF[GROUND_SIZE] = {0, 0, 0, 0};

// static volatile uint16_t second_timing = 0;

// static volatile uint8_t dp_check = 0;

// static uint16_t compare_val = 0;

// static uint16_t mid_cycle_compare = 0;

// static uint8_t Flick_Array[GROUND_SIZE] = {0, 0, 0, 0};

// static uint8_t Flick_Flag = 0;


// // THIS IS THE ARRAY WITHOUT DECIMAL POINTS
// static const uint8_t NUMBER_BYTES[10] = {
// 	0x3F, // 0
// 	0x06, // 1
// 	0x5B, // 2
// 	0x4F, // 3
// 	0x66, // 4
// 	0x6D, // 5
// 	0x7D, // 6
// 	0x07, // 7
// 	0x7F, // 8
// 	0x6F  // 9
// };


// ISR(_TIMER2_COMPA_) {

//     if((++second_timing) >= mid_cycle_compare){
//     	second_timing = 0;
//     	dp_check ^= (1);
//     	Flick_Flag ^= (1);
//     }

// 	for (uint8_t i = 0; i < 4; i++) {
//         *LED_DISPLAY_GROUND |= (1 << GROUND_ARRAY[i]);
//     }

//     pattern = numberArray[groundCount];

//     if(DPF[groundCount] && (dp_check)){

//     	pattern |= 0x80;
//     }

//     if(Flick_Array[groundCount] && !Flick_Flag){

//     	// if(Flick_Flag){
//     	// 	*LED_DISPLAY_PORT = pattern;
//     	// }else{
//     	// 	*LED_DISPLAY_PORT = 0;
//     	// }

//     	*LED_DISPLAY_PORT = 0;
//     }else{

//     	*LED_DISPLAY_PORT = pattern;
//     }

// 	*LED_DISPLAY_GROUND &= ~(1 << GROUND_ARRAY[groundCount]);

// 	if(++groundCount > 3){
// 		groundCount = 0;
// 	}
// }


// static inline void initTIMER_2(void) {
//     	/* 
// 			Changed the value that multiplies by F_CPU to 0.002
// 			To decrease ISR call latency and boost free clock cycles
// 			*/
//         _OCR2A_ = (uint8_t)((0.002 * F_CPU) / 1024 - 1);

// 		_TCR2A_ |= (1 << _WGM21_);

// 		compare_val = ((F_CPU / 1024UL) / (_OCR2A_ + 1));
// 		mid_cycle_compare = (compare_val / 2);

// 		_TIMSK2_ |= (1 << _OCIE2A_);
// }


// static void extractNumber(uint16_t number) {

// 	dp_check = 1;

//     for(uint8_t i = 3; i < 255; i--){
//     	uint8_t digit = number % 10;

//     	numberArray[i] = NUMBER_BYTES[digit];

//     	number /= 10;
//     }
// }


// void setPin(const uint8_t ground[]){

// 	for(uint8_t i = 0; i < GROUND_SIZE; i++){

// 		GROUND_ARRAY[i] = ground[i];
// 	}
// }


// void initLED_DISPLAY(volatile uint8_t *PORT_1, volatile uint8_t *PORT_2, uint8_t dp_mask){

// 	LED_DISPLAY_PORT = PORT_1;
// 	LED_DISPLAY_GROUND = PORT_2;

// 	//WITH THIS, A USER CAN PASS '0' IF HE DOESN'T WANT DPs

// 	if((--dp_mask) < 4){
// 		DPF[dp_mask] = 1;
// 	}

// 	if(dp_mask == 255){
// 		for(uint8_t i = 0; i < GROUND_SIZE; i++){
// 			DPF[i] = 0;
// 		}
// 	}

// 	initTIMER_2();
// }
 

// void DISPLAY(uint16_t num){

// 	DISPLAY_reset();

// 	extractNumber(num);

// 	_TCR2B_ |= (1 << _CS22_) | (1 << _CS21_) | (1 << _CS20_);
// 	TCNT2 = 0x1E;
// }


// /* 
// 	Should be updated to display characters at given/custom position with 
// 	This isn't and would not be made to be generic, it is fully custom and
// 	made for the need of showing characters

// 	==========||> [-CUSTOM FUNCTION BUILD-] <||==========
// */

// static void disable_decimal(){

// 	for(uint8_t i = 0; i < GROUND_SIZE; i++){
// 		temp_DPF[i] = DPF[i];
// 		DPF[i] = 0;
// 	}
// }

// void DISPLAY_wChar(uint16_t character, uint8_t number){

// 	DISPLAY_reset();
    
//     extractNumber(number);

//     numberArray[0] = (character >> 8);
//     numberArray[1] = (character);

//     disable_decimal();

// 	_TCR2B_ |= (1 << _CS22_) | (1 << _CS21_) | (1 << _CS20_);
// 	TCNT2 = 0x1E;
// }

// void DISPLAY_nDP(uint16_t num){

// 	DISPLAY_reset();

// 	extractNumber(num);

// 	disable_decimal();

// 	_TCR2B_ |= (1 << _CS22_) | (1 << _CS21_) | (1 << _CS20_);
// 	TCNT2 = 0x1E;
// }

// void DISPLAY_flick(uint16_t number, uint16_t flick_number){
	
// 	DISPLAY_reset();

// 	extractNumber(number);

// 	disable_decimal();

// 	while(flick_number){

// 		uint8_t digit = flick_number % 10;

// 		if(digit > 0){
// 			Flick_Array[digit-1] = 1;
// 		}

// 		flick_number /= 10;
// 	}

//     Flick_Flag = 1;

// 	_TCR2B_ |= (1 << _CS22_) | (1 << _CS21_) | (1 << _CS20_);
// 	TCNT2 = 0x1E;
// }

// void DISPLAY_reset(){

// 	_TCR2B_ &= ~(1 << _CS22_) & ~(1 << _CS21_) & ~(1 << _CS20_);

// 	groundCount = 0;
// 	pattern = 0;
// 	second_timing = 0;
// 	dp_check = 0;
// 	Flick_Flag = 0;

// 	for(uint8_t i = 0; i < GROUND_SIZE; i++){
// 		DPF[i] = temp_DPF[i];
// 		Flick_Array[i] = 0;
// 	}
// }
