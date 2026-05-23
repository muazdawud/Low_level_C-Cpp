

// #include<avr/io.h>
// #include<util/delay.h>

// #include"USART.h"
// #include"Joystick.h"


// #define  transmitDelay  500


// int main(void){

// 	initUSART();
// 	initADC();

// 	printString("\r\n=== ADC Test ===\r\n");

// 	while(1){

// 		printByte(analogGet(0));
// 		printString("\r\n");

// 		_delay_ms(transmitDelay);
// 	}

// 	return 0;
// }