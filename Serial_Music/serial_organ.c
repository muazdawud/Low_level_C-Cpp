/*Running the ffmpeg;
	Open cmd after installing ffmpeg and type;
		-->	ffmpeg -i <file path> -f u8 -acodec pcm_u8 -ac 1 -ar 8000 <destination>.raw
*/
#include<avr/io.h>
#include<util/delay.h>
#include"pinDefines.h"
#include"USART.h"


#define NOTE_DELAY        

int main(void){

	SPEAKER_DDR |= (1 << SPEAKER);
	initUSART();
	uint16_t noteDuration = NOTE_DELAY/2;

	char compInput;

	const char keys[] = {
		'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
		'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
		'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.'
	}

	const uint16_t notes[] = {
	}

	uint8_t noteCheck;
	uint8_t i;

	while(1){
		compInput = recieveByte();
		
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
				sleep(noteDuration);
			}
		}
	}

	return 0;
}
