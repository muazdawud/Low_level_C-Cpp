#include<avr/io.h>
#include<util/delay.h>

#define LED_ON 0x3f

int main(void){
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);

	DDRB = LED_ON;
	uint8_t buttonState = 0;

	while(1){

		if(PIND & (1 << PD2)){
			if(buttonState == 0){
				PORTB ^= LED_ON;
				buttonState = 1;
			}
		}else{
			buttonState = 0;
		}

	}

	return 0;
}