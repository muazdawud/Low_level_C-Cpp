


#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#include "USART_D.h"
#include "DHT_11_TH.h"


ISR(PCINT1_vect){
	if(bit_is_set(PINC, P0)){

		DHT_HandleSignal();
	}else{

		DHT_ReadSignal();
	}
}


int main(void){

	DHT_Init(_PORT_C, P0);
	USART_begin();

	USART_print("\r\n==== DHT11_TEST ====\r\n");

	while(1){

		uint8_t temp = DHT_Get_Temp();
		_delay_ms(1000);
		uint8_t humd = DHT_Get_Humidity();

		USART_print("\r\n");
		USART_print("Current Temperature ->  %d\r\n", temp);
		USART_print("Current Humidity    ->  %d\r\n", humd);
		USART_print("\r\n");

		_delay_ms(3000);
	}
}