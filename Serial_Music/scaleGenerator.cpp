/*
 // Author: Dauda M. S.
                                                                   /
 // Github: https://github.com/muazdawud


                                                                   /
 This file, when compiled, provides the scale file which is
 is used in the main AVR code titled 'serial_organ.c'.
                                                                   /
 File can be tweaked and modified based on user need.
 MAX_PITCH used in this scale is `20000` and 8 OCTAVES, 
 all can be modified for a more broader or short scale.
                                                                    /
 I used a funciton which reads F(x) = A*e^(-kx);
 Where `A` is MAX_PITCH; `k` is the descend coefficient of the curve;
 and `x` is the number of OCTAVES. 
                                                                   /
 By changing `k`, it modifies if
 the scale descent rapidly (when `k` is increased) or slowly (when
 `k` is decreased).
                                                                   /
                                                                   */


#include<bits/stdc++.h>
#include<string>
using namespace std;

vector<string> noteCode = {"E", "C", "Cx", "Dx", "D", "F", "Ax",
 "B", "A", "Gx"};

inline int calculatePitch(uint16_t maxSize){
	const uint16_t MAX_PITCH = 20000;
	const uint8_t OCTAVE = 8;

	double temp = 0.5/OCTAVE;
	temp = MAX_PITCH * exp(-temp * maxSize);

	return temp;
}

void writeToFile(fstream &f){ 
	uint8_t ID;
	int pitch_level;
	uint8_t octave;

	for(octave = 0; octave < 9; octave++){

		for(uint8_t note = 0; note < 10; note++){

			ID = (octave * 10) + note;
		
			pitch_level = calculatePitch(ID);


			f << "#define    " << noteCode[note] << int(octave);
			if(noteCode[note].size() > 1){
				f << "    ";
			}else{
				f << "     ";
			}
			f << pitch_level << endl;
		
		}
	}
}

int main(){
	string FILENAME = "scale.h";

	fstream File;
	File.open(FILENAME, ios::out | ios::trunc);

	if(!File) return 1;

	File << " // This file provides the scale on which each note depends." << endl;
	File << " // Scale is in the key of 30000" << endl;
	File << " // Automatically generated using scaleGenerator.cpp" << endl << endl << endl;

	writeToFile(File);
	File.close();

	return 0;
}