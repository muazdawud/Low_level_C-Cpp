



#ifndef _DHT_11_TH_H
#define _DHT_11_TH_H

/*
	 I'm using a custom generated name for the PORTs to avoid 
	 compiler error when passing the name of the PORTs and PINs
	 to the DHT_Config(); function, which takes two parameters;
	     ->>   PORT_NAME and PIN_BIT
	 so one of these three PORT_NAME below shall be used and 
	 passed to the function to configure the PORT to use for
	 the DHT11 sensor data line, and one of the available 
	 PIN_BIT shall be passed to configure the actual pin to 
	 handle the data line of the DHT sensor.
	 */

#define		_PORT_B   	1       //  A custom replacement for [PORTB]
#define 	_PORT_C   	2       //  A custom replacement for [PORTC]
#define 	_PORT_D   	3		//  A custom replacement for [PORTD]


#define 	P0   	0       //  A custom replacement for [PB0] / [PC0] / [PD0]
#define 	P1   	1       //  A custom replacement for [PB1] / [PC1] / [PD1]
#define 	P2   	2       //  A custom replacement for [PB2] / [PC2] / [PD2]
#define 	P3   	3       //  A custom replacement for [PB3] / [PC3] / [PD3]
#define 	P4   	4       //  A custom replacement for [PB4] / [PC4] / [PD4]
#define 	P5   	5       //  A custom replacement for [PB5] / [PC5] / [PD5]
#define 	P6   	6       //  A custom replacement for [PB6] / [PC6] / [PD6]
#define 	P7  	7       //  A custom replacement for [PB7] / [PC7] / [PD7]



#define 	MCU_BD_LOW     20 /*
			 ~18ms, BD stands for Begin Delay.
			 */
#define 	MCU_BD_HIGH    40 /*
			 ~40us, if susseccful, the DHT will make the next delay.
			 */
#define 	DHT_OD 		   80 /*
			 ~80us for both the LOW and HIGH signals, LOW first then HIGH
			 OD stands for Overall Delay.
			 */
#define 	DHT_TD_LOW 	   100 /* 
			 ~50*2us for the beginning of each bit being sent by the DHT
	 		 TD stands for Transmit Delay, the 50us is a low signal,
			 which exactly after, the DHT pulls the line to the appropriate 
			 signal (either HIGH or LOW).

			 When the last bit data is transmitted,
			 DHT11 pulls down the voltage level and keeps it for 50us to signal
			 end of transmission.
			 */
#define 	DHT_ZERO_BIT 	(54) /*
			 ~27*2us delay for a '0' bit to be sent (with `F_CPU/8` 
			 prescaler), and then drag pin value LOW and wait for 
			 exactly DHT_TD_LOW(us), to signal next bit transmission.
			 */
#define 	DHT_ONE_BIT 	(140) /*
			 ~70*2us to transmit a '1' bit thorugh the data line 
			 (with `F_CPU/8` prescaler).
			 */
#define 	DHT_READ_DELAY	25 /*
			 This (in ms) is the entire time it takes the DHT to sample
			 all the data beginning from the StartSignal to the end.
			 */
#define 	TIMER_TIMEOUT 	3 	
#define 	_OCR_VAL_		((F_CPU / 1024) - 1)


typedef struct {
    volatile uint8_t* port;
    volatile uint8_t* ddr;
    volatile uint8_t* pin;
    uint8_t bit;
} DHT_Device;



void DHT_Init(uint8_t portValue, uint8_t PIN);

void DHT_HandleSignal(void);

void DHT_ReadSignal(void);

uint8_t DHT_Get_Temp(void);

uint8_t DHT_Get_Humidity(void); 



#endif    /* _DHT_11_TH_H */