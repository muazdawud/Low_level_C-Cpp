/*
                                                               / 
 // Author: Dauda M. S.
                                                                /
 // Github: https://github.com/muazdawud
                                                                /
 This is the source file for player.h.
                                                                 /
 All functionalities are written in functions.
                                                                 /
                                                                 */


#include<avr/io.h>
#include<util/delay.h>
#include "pinDefines.h"
#include "player.h"


/*
                                                               /
 Each note has it's own duration (that is; how many times do we
 need to oscillate the speakers crystal<If using a buzzer> in 
 order to produce a sound).                                    
                                                              /
 >  `period` is the number of oscillation (generating and analog
 	voltage)
 >  `duration` is the time to take oscillating the signal.
                                                               / 
 >  All the above takes place in `playNote()` function.
                                                               / 
 */

void playNote(uint16_t period, uint16_t duration){
	uint16_t elapsed;
	uint16_t i;

	for(elapsed = 0; elapsed < duration; elapsed += period){
		for(i = 0; i < period; i++){
			_delay_us(1);
		}

		SPEAKER_PORT ^= (1 << SPEAKER);
	}
}

/*
 This is a resting function, as the name says.
 */

void __sleep__(uint16_t duration){
	do{
		_delay_us(1);
	}while(--duration);
}