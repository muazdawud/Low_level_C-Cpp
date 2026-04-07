ISR(TIMER2_COMPA_vect){

	*LED_DISPLAY_GROUND = 0;

	*LED_DISPLAY_GROUND &= ~(1 << GROUND_ARRAY[groundCount]);

	temp = NUMBER_BYTES[numberArray[NA_POSITION]];


	NA_POSITION++;
	segment++;

	if(NA_POSITION >= 4){
		NA_POSITION = 0;
	}

	if(segment >= PORT_SIZE){
		segment = 0;
		groundCount++;
		if(groundCount >= GROUND_SIZE){
			groundCount = 0;
		}
	}
}




*LED_DISPLAY_GROUND &= ~(1 << GROUND_ARRAY[groundCount]);

	temp = NUMBER_BYTES[numberArray[NA_POSITION]];