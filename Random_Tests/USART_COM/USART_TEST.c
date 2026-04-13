


#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include<avr/power.h>

#include "USART_D.h"


int main(void){

    clock_prescale_set(clock_div_1);

    char ch = '#';
    int8_t age = 0x22;
    int8_t neg = -123;
    char name [] = "Sadik";

    USART_begin();

    USART_print("\r\n==== USART_TEST ====\r\n");

    while(1){

        USART_print("\r\nHello World!\r\n");
        USART_print("My name is %s.\r\n", name);
        USART_print("How are you? %c\r\n", ch);
        USART_print("I am %d years old.\r\n", age);
        USART_print("My account balance is %d.\r\n", neg);
        USART_print("\r\n");

        //const char* input = ;

        USART_print("INPUT =  ");
        USART_print("%s.\r\n\r\n", USART_getString());

        _delay_ms(3000);
    }

    return 0;
}