#include<avr/io.h>
#include<util/delay.h>

#define PORT PORTB
#define DDR DDRB
#define DELAY 85

#define setBit(reg, bit) ((reg) = (1 << bit))
#define clearBit() (PORT = 0b00000000)

int main(void){
	DDR |= 0b00111111;
	uint8_t i = 0;

	while(1){
		while(i < 5){
			setBit(PORT, i);
			_delay_ms(DELAY);
			i++;
		}

		while(i > 0){
			setBit(PORT, i);
			_delay_ms(DELAY);
			i--;
		}
	}

	return 0;
}