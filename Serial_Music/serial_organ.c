/*
 // Author: Dauda M. S.
                                                                   /
 // Github: https://github.com/muazdawud


                                                                   /
 This is my custom built serial organ, with a custom independent 
 scaleGenerator.cpp program.
                                                                   /
                                                                   */


#include<avr/io.h>
#include<util/delay.h>
#include "pinDefines.h"
#include "scale.h"
#include "player.h"
#include "USART.h"


#define NOTE_DELAY        0xF000

int main(void){

	SPEAKER_DDR |= (1 << SPEAKER);
	initUSART();
	uint16_t noteDuration = NOTE_DELAY / 2;

	char compInput;

	const char keys[] = {
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
		'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.'
	};

	const uint16_t notes[] = {
		D5, F5, Ax5, B5, A5, Gx5, E6, C6, Cx6, Dx6,
		D6, F6, Ax6, B6, A6, Gx6, E7, C7, Cx7, Dx7, D7,
		F7, Ax7, B7, A7, Gx7, E8, C8, Cx8, Dx8
	};

	uint8_t noteCheck;
	uint8_t i;

	while(1){
		compInput = receiveByte();
		
		if(noteDuration == NOTE_DELAY){
			transmitByte('_');
		}else{
			transmitByte('-');
		}

		noteCheck = 0;
		for(i = 0; i < sizeof(keys); i++){
			if(compInput == keys[i]){
				playNote(notes[i], noteDuration);
				noteCheck = 1;
				break;
			}
		}

		if(!noteCheck){
			if(compInput == '['){
				noteDuration = NOTE_DELAY;
			}
			else if(compInput == ']'){
				noteDuration = NOTE_DELAY/2;
			}
			else{
				__sleep__(noteDuration);
			}
		}
	}

	return 0;
}
