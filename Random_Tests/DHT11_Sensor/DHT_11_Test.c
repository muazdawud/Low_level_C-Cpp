


#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#include "USART_D.h"
#include "DHT_11_TH.h"


ISR(PCINT1_vect){
 
	DHT_HandleSignal();
}


int main(void){

	DHT_Init(_PORT_C, P0);
	USART_begin();

	USART_print("\r\n==== DHT11_TEST ====\r\n");

	while(1){

		uint8_t temp = DHT_Get_Temp(); 
		uint8_t humd = DHT_Get_Humidity(); 

		USART_print("\r\n");
		USART_print("Current Temperature ->  %d\r\n", temp);
		USART_print("Current Humidity    ->  %d\r\n", humd);
		USART_print("\r\n");

		_delay_ms(3000);
	}
}