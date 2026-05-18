
#include<avr/io.h>
#include<util/delay.h>



#define DELAY 5000      // This value is in micro-seconds

#define LED_COUNT 6

static void initTimers(void){


	TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
	TCCR0A |= (1 << WGM01) | (1 << WGM00);
	TCCR0B |= (1 << CS01);


	TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	TCCR1B |= (1 << CS11);


	TCCR2A |= (1 << COM2A1) | (1 << COM2B1);
	TCCR2A |= (1 << WGM21) | (1 << WGM20);
	TCCR2B |= (1 << CS21);
}


int main(void){

	uint8_t i;
	uint8_t current_led = 0;
	uint8_t led_count = 0;
	int8_t direction = 1;

	initTimers();

	DDRB |= (1 << PB1) | (1 << PB2) | (1 << PB3);
	DDRD |= (1 << PD3) | (1 << PD5) | (1 << PD6);

	while(1){

		for(i = 0; i < 256; i += direction){

			if(i == 0){
				direction = 1;

				if((++led_count) >= 2){

					led_count = 1;
					
					if((++current_led) >= LED_COUNT){
						current_led = 0;
						PORTB &= ~(1 << PB1) & ~(1 << PB2) & ~(1 << PB3);
						PORTD &= ~(1 << PD3) & ~(1 << PD5) & ~(1 << PD6);
					}
				}
			}

			if(i == 255){
				direction = -1;			
			}

			switch(current_led){

				case 0:
					{
						OCR2B = i;
						break;
					}
				case 1:
					{
						OCR0B = i;
						break;
					}
				case 2:
					{
						OCR1A = i;
						break;
					}
				case 3:
					{
						OCR1B = i;	
						break;
					}
				case 4:
					{
						OCR2A = i;
						break;
					}
				case 5:
					{
						OCR0A = i;
						break;
					}
			}

		    _delay_us(DELAY);
		}
	}

	return 0;
}