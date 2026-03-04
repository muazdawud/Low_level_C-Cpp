#include<avr/io.h>
#include<util/delay.h>
#include "pinDefines.h"
#include "USART.h" 
 

/*
   This code shows how serial communication with and AVR MCU works.
   The MCU in this example is an Arduino UNO board (rather than the chip itself).
   But all functionalities are the same except for the small tweak on
   assigning the LED_PORT inside the while loop. So, if you're using a real AVR
   it almost crucial to change the LED_PORT mask from;

   -->>  LED_PORT = (serialData >> 2); to LED_PORT = serialData; <<--

   Other functionalitis can be added, based on user needs.
*/


int main(void){
	char serialData;
	LED_DDR = 0x3f;
	initUSART();
	printString("Welcome to AVR Programming.\r\n");

	while(1){
		serialData = receiveByte();
		transmitByte(serialData);
		LED_PORT = (serialData >> 2);
	}

	return 0;
}