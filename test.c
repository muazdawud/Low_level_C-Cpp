#include<avr/io.h>
#include<util/delay.h>
#include "USART.h"

int main(void){
	uint16_t i;

	initUSART();

	printString("Welcome Back!\r\n");
	while(1){

		for(i = 0; i < 65535; i++){
			printByte(i);
			printString("\r\n");
		}

		printString("END!\r\n");
		break;
	}

	return 0;
}