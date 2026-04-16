




#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#include<avr/power.h>


#include "USART_D.h"
#include "DHT_11_TH.h"
#include "reg_defs_t.h"
 
 
DHT_Device mySensor;


volatile static uint32_t temp_nd_hum_data = 0;
volatile static uint8_t checksum = 0;
volatile static uint8_t temperature = 0;
volatile static uint8_t humidity = 0;
volatile static uint8_t temp_deci = 0;
volatile static uint8_t hum_deci = 0;

volatile static uint8_t temp_t = 0;
volatile static uint8_t temp_h = 0;
volatile static uint8_t temp_t_d = 0;
volatile static uint8_t temp_h_d = 0;


volatile static uint8_t timestamp;
volatile static uint8_t pcint_cycle = 0;
volatile static uint8_t bit_position_tnhd = 0; /*
						It is used to track the exact position of the data\
						bit in our `temp_nd_hum_data` variable (which stores
						the entire 32 data bits).
						*/

 

 
static void DHT_StartSignal(void);
static void DHT_Parse_Data(void); 
static uint8_t DHT_Verify_Checksum(void);
static inline void initTIMER_1(void);


void DHT_Init(uint8_t portValue, uint8_t PIN);
void DHT_HandleSignal(void);
void DHT_ReadSignal(void);
uint8_t DHT_Get_Temp(void);
uint8_t DHT_Get_Humidity(void); 



static void DHT_StartSignal(void) {

	// USART_print("	-> Inside DHT_StartSignal().\r\n");

	timestamp = 0;
	pcint_cycle = 0;

    *(mySensor.ddr) |= (1 << mySensor.bit);
    *(mySensor.port) &= ~(1 << mySensor.bit);
    _delay_ms(MCU_BD_LOW);

    *(mySensor.port) |= (1 << mySensor.bit);

    sei();
    _TCR1B_ |= (1 << _CS11_);
    TCNT1 = 0;
}


static void DHT_Parse_Data(void){

	USART_print("	-> Inside DHT_Parse_Data().\r\n");

	if(temp_nd_hum_data){

		humidity = (temp_nd_hum_data);

		hum_deci = (temp_nd_hum_data >> 8);

		temperature = (temp_nd_hum_data >> 16);

		temp_deci = (temp_nd_hum_data >> 24);

		if(!DHT_Verify_Checksum()){
			humidity = temp_h;
			hum_deci = temp_h_d;
			temperature = temp_t;
			temp_deci = temp_t_d;
		}
	}
}


static uint8_t DHT_Verify_Checksum(void){

	USART_print("	-> Inside DHT_Verify_Checksum().\r\n");

	uint8_t sum = humidity + hum_deci + temperature + temp_deci;

	if(checksum == sum){
		return 1;
	}

	return 0;
}


static inline void initTIMER_1(void){

	_TCR1B_ &= ~(1 << _WGM12_) & ~(1 << _WGM13_);
	_TCR1A_ &= ~(1 << _WGM10_) & ~(1 << _WGM11_);
}





void DHT_Init(uint8_t portSelection, uint8_t pinNum) {

	USART_print("	-> Inside DHT_Init().\r\n");

	clock_prescale_set(clock_div_1);

    mySensor.bit = pinNum;
    
    switch(portSelection) {
        case 1:
            mySensor.port = &PORTB;
            mySensor.ddr  = &DDRB;
            mySensor.pin  = &PINB;

            PCICR |= (1 << PCIE0);
            PCMSK0 |= (1 << pinNum);

            break;
        case 2:
            mySensor.port = &PORTC;
            mySensor.ddr  = &DDRC;
            mySensor.pin  = &PINC;

            PCICR |= (1 << PCIE1);
            PCMSK1 |= (1 << pinNum);

            break;
        case 3:
            mySensor.port = &PORTD;
            mySensor.ddr  = &DDRD;
            mySensor.pin  = &PIND;

            PCICR |= (1 << PCIE2);
            PCMSK2 |= (1 << pinNum);

            break;
    }

    initTIMER_1();
}


void DHT_HandleSignal(void){ 

	if(pcint_cycle < 2){
		*(mySensor.ddr) &= ~(1 << mySensor.bit);
		pcint_cycle++;
	}

	else{

		timestamp = TCNT1;
	}
}


void DHT_ReadSignal(void){

	uint16_t temp = TCNT1 - (timestamp);

	uint8_t bit_ = (temp >  90) ? 1 : 0;
 
	if(bit_position_tnhd < 32){

			temp_nd_hum_data = (temp_nd_hum_data << 1) | bit_;
	}

	else if(bit_position_tnhd < 40){

			checksum = (checksum << 1) | bit_;
	}

	bit_position_tnhd++;
}


uint8_t DHT_Get_Temp(void){

	USART_print("	-> Getting Temperature.\r\n");

	temp_t = temperature;
	temp_t_d = temp_deci;
	temp_h = humidity;
	temp_h_d = hum_deci;

	DHT_StartSignal();
	_delay_ms(DHT_READ_DELAY - MCU_BD_LOW);

	DHT_Parse_Data();

	USART_print("	-> Temperature in DHT_Get_Temp() = %d.\r\n", temperature);

	//cli();

	return temperature;
}


uint8_t DHT_Get_Humidity(void){

	USART_print("	-> Getting Humidity.\r\n");

	temp_t = temperature;
	temp_t_d = temp_deci;
	temp_h = humidity;
	temp_h_d = hum_deci;

	DHT_StartSignal();
	_delay_ms(DHT_READ_DELAY - MCU_BD_LOW);

	DHT_Parse_Data();

	USART_print("	-> Humidity in DHT_Get_Humidity() = %d.\r\n", humidity);

	//cli();

	return humidity;
}