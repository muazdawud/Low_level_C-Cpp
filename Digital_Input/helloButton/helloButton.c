#include<avr/io.h>
#include<util/delay.h>

#define toggleOnLED() (PORTB = 0x3f)
#define toggleOffLED() (PORTB = 0x0)

int main(void){
	DDRD &= ~(1 << PD2);
	PORTD |= (1 << PD2);

	DDRB = 0x3f; 

	while(1){

		if(PIND & (1 << PD2)){
			toggleOnLED();
		}else{
			toggleOffLED();
		}
	}

	return 0;
}