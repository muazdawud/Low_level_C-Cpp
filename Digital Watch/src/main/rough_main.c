




// #include<avr/io.h>
// #include<avr/interrupt.h>
// #include<util/delay.h>
// #include<avr/power.h>

// #include "4D_7S.h"
// #include "DHT_11.h"
// #include "pinDefines.h"
// #include "reg_defs_t.h"


// #define DEBOUNCE_DELAY 5


// volatile static uint8_t button_state = 0;
// volatile static uint8_t button_click = 0;
// volatile static uint8_t pre_check = 0;
// volatile static uint8_t temperature = 0;
// volatile static uint8_t humidity = 0;
// volatile static uint8_t potentiometer = 0;
// volatile static uint16_t display_number = 0;
// volatile static uint8_t ovf_counter = 0;
// volatile static uint8_t seconds = 0;
// volatile static uint8_t minute = 0;
// volatile static uint8_t hour = 0;
// volatile static uint8_t on_time = 0;


// /* ISR (On PORTB) From the DHT_11.h setup */
// ISR(PCINT0_vect){
 
// 	DHT_HandleSignal();
// }


// /* Push Button Interrupt */
// ISR(PCINT1_vect){

// 	if(bit_is_clear(BUTTON_PIN, BUTTON)){

// 		_delay_ms(DEBOUNCE_DELAY);
// 		if(bit_is_clear(BUTTON_PIN, BUTTON)){

// 			button_state = 1;
// 		}

// 	}
// }


// /* ISR for updating the Time and date */
// ISR(_TIMER0_OVF_){
// 	ovf_counter++;

// 	if(ovf_counter >= 61){
// 		seconds++;
// 		on_time++;

// 		if(seconds >= 60){
// 			minute++;

// 			if(minute >= 60){
// 				hour++;

// 				if(hour >= 12){
// 					hour = 1;
// 				}

// 				minute = 0;
// 			}

// 			display_number = (hour*100) + (minute);

// 			seconds = 0;
// 		}

// 		ovf_counter = 0;
// 	}
// }


// uint8_t LED_ARRAY_BIT[] = {LA1, LA2, LA3, LA4};

// uint8_t _4D_7S_Ground[] = {LED_GP1, LED_GP2, LED_GP3, LED_GP4};


// static inline void initLED_ARRAY(void);
// static inline void init4D_7S(void);
// static inline void initADC_POT(void);
// static inline void initTimer0(void);

// static inline void starter_run(void);

// static void mainRun(void);

// int main(void){

// 	/* PushButton Setup */
// 	BUTTON_PORT |= (1 << BUTTON);
	
// 	/* LED_ARRAY Setup */
// 	initLED_ARRAY();

// 	/* 4D_7S Display Setup */
// 	initLED_DISPLAY(&LED_LIVE_PORT, &LED_GROUND_PORT, 2); /* Decimal Point on 2nd Number */
// 	setPin(_4D_7S_Ground);
// 	init4D_7S();

// 	/* DHT_11 Setup */
// 	DHT_Init(DHT_PORT, DHT_PIN);

// 	/* ADC Setup for POT */
// 	initADC_POT();

// 	/* Buzzer Setup */
// 	BUZZER_DDR |= (1 << BUZZER);

// 	initTimer0();


// 	while(1){

// 		if(button_state){

// 			button_state = 0;
// 			button_click++;
// 			on_time = 1;

// 			mainRun();

// 		}
// 	}

// 	return 0;
// }


// static inline void initLED_ARRAY(void){

// 	LED_DDR |= (0x3C);
// }


// static inline void init4D_7S(void){

// 	LED_LIVE_DDR |= (0xff);
// 	LED_GROUND_DDR |= (0xf);
// }


// static inline void initADC_POT(void){

// 	ADMUX |= (1 << REFS0);
// 	ADMUX |= (1 << ADLAR); /* Read only ADCH and not ADC */

// 	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
// }

// static inline void initTimer0(void){

// 	_TCR0B_ |= (1 << _CS00_) | (1 << _CS02_);
// 	_TIMSK0_ |= (1 << TOIE0);

// 	sei();
// }


// static inline void starter_run(void){

// 	temperature = DHT_Get_Temp();
// 	humidity = DHT_Get_Humidity();

// 	ADCSRA |= (1 << ADEN);

// 	ADCSRA |= (1 << ADSC);
// 	loop_until_bit_is_set(ADCSRA, ADSC);

// 	potentiometer = ADCH;
// }




// static void mainRun(void){

// 	if(!pre_check){
// 		starter_run(); /* The function that allows to get the values for the initial temp, POT and humidity */
// 		pre_check++;
// 	}


// 	while(on_time){

// 		switch(button_click){
// 			case 1:{

// 				DISPLAY(display_number);
// 				break;
// 			}
// 			case 2:{
				
// 				DISPLAY(temperature);
// 				break;
// 			}
// 			case 3:{
				
// 				DISPLAY(humidity);
// 				break;
// 			}
// 			// case 4:{

// 			// 	DISPLAY()			
// 			// 	break;
// 			// }
// 			// case 5:{
			
// 			// 	break;
// 			// }
// 			default:{
				
// 				button_click = 0;
// 				break;
// 			}
// 		}


// 		if(on_time >= 6){
// 			end_sequence();

// 			break;
// 		}

// 	}

// }


