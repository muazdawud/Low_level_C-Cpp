#include <avr/io.h>
#include <util/delay.h>

#define PORT PORTB
#define DDR DDRB
#define P_DEL 20 
#define P_MASTER_DEL 500 
#define S_MASTER_DEL 150
#define EXTRA_DEL 150

#define setBit(register__, bit) ((register__) |= (1 << bit)) 
#define clearBit(register__, bit) ((register__) &= ~(1 << bit))

int main(void){
	DDR = 0b00111111;

	while(1){ 

		////---------------PHASE_1-------------------////

		for(uint8_t i = 0; i < 6; i++){
			setBit(PORT, i);
			_delay_ms(P_DEL+10);
		}

		_delay_ms(P_MASTER_DEL);

		for(int8_t i = 5; i >= 0; i--){
			clearBit(PORT, i);
			_delay_ms(P_DEL+10);
		}

		_delay_ms(P_MASTER_DEL);

		for(int8_t num = 0; num < 2; num++){
			for(uint8_t i = 0; i < 6; i+=2){
				setBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);

			for(int8_t i = 4; i >= 0; i-=2){
				clearBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);

			for(uint8_t i = 1; i < 6; i+=2){
				setBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);

			for(int8_t i = 5; i >= 0; i-=2){
				clearBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);
		}

		_delay_ms(EXTRA_DEL);

		////---------------PHASE_2-------------------////

		for(int8_t i = 5; i >= 0; i--){
			setBit(PORT, i);
			_delay_ms(P_DEL+10);
		}

		_delay_ms(P_MASTER_DEL);

		for(uint8_t i = 0; i < 6; i++){
			clearBit(PORT, i);
			_delay_ms(P_DEL+10);
		}

		_delay_ms(P_MASTER_DEL);

		for(int8_t num = 0; num < 2; num++){
			for(uint8_t i = 1; i < 6; i+=2){
				setBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);

			for(int8_t i = 5; i >= 0; i-=2){
				clearBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);

			for(uint8_t i = 0; i < 6; i+=2){
				setBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);

			for(int8_t i = 4; i >= 0; i-=2){
				clearBit(PORT, i);
			}

			_delay_ms(S_MASTER_DEL);
		}

		_delay_ms(EXTRA_DEL);

	}

	return 0;
}