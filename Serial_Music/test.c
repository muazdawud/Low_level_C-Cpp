/*
 // Author: Dauda M. S.
                                                                   /
 // Github: https://github.com/muazdawud
                                                                    /
 My custom built trial file.

                                                                   */




// #include<avr/io.h>
// #include<util/delay.h>
// #include "pinDefines.h"
// #include "player.h"
// #include "scale.h"
// #include "USART.h"

// #define NOTE_DELAY 0xF000

// uint16_t notes[] = {
// 	E0, C0, Cx0, Dx0, D0, F0, Ax0, B0, A0, Gx0,
// 	E1, C1, Cx1, Dx1, D1, F1, Ax1, B1, A1, Gx1,
// 	E2, C2, Cx2, Dx2, D2, F2, Ax2, B2, A2, Gx2,
// 	E3, C3, Cx3, Dx3, D3, F3, Ax3, B3, A3, Gx3,
// 	E4, C4, Cx4, Dx4, D4, F4, Ax4, B4, A4, Gx4,
// 	E5, C5, Cx5, Dx5, D5, F5, Ax5, B5, A5, Gx5,
// 	E6, C6, Cx6, Dx6, D6, F6, Ax6, B6, A6, Gx6,
// 	E7, C7, Cx7, Dx7, D7, F7, Ax7, B7, A7, Gx7,
// 	E8, C8, Cx8, Dx8, D8, F8, Ax8, B8, A8, Gx8
// };

// int main(void){

// 	SPEAKER_DDR |= (1 << SPEAKER);
// 	initUSART();
	 
// 	uint16_t delay = NOTE_DELAY/2;
// 	uint8_t count;

// 	while(1){

// 		for(count = 0; count < 90; count++){
// 			playNote(notes[count], delay);
// 			playNote(notes[count], delay);
// 			printByte(notes[count]);
// 			transmitByte('\r');
// 			transmitByte('\n');
// 			__sleep__(delay*delay);
// 		}

// 		__sleep__(delay*delay*delay);

// 	}

// 	return 0;
// }