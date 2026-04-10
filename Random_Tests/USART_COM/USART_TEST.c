


#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

#include "USART_D.h"


int main(void){

    char ch = '#';
    int8_t age = 0x22;
    int8_t neg = -123;
    char name [] = "Sadik";

    USART_begin();

    USART_print("==== USART_TEST ====\r\n");

    while(1){

        USART_print("Hello World!\r\n");
        USART_print("My name is %s.\r\n", name);
        USART_print("How are you? %c\r\n", ch);
        USART_print("I am %d years old.\r\n", age);
        USART_print("My account balance is %d.\r\n", neg);
        USART_print("\r\n");

        const char* input = USART_getString();

        USART_print("INPUT =  ");
        USART_print(input);
        USART_print("\r\n");

        USART_flush();

        _delay_ms(3000);
    }

    return 0;
}