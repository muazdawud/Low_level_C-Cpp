/*
	Author: Dauda Muazu Sulaiman

	Created on 22/05/2026.
*/


#ifndef  ANALOG_INPUT_H
#define  ANALOG_INPUT_H  1


void initADC(void);

uint16_t analogGet(uint8_t multiplexer);


#endif /* ANALOG_INPUT_H */