#include "Buzzer.h"

#define NOTE_A4  440

Buzzer::Buzzer(byte pin){
	pinMode(pin, OUTPUT);
	Buzzer::pin = pin;
}

void Buzzer::noteOn(char key){
	tone(pin, ktof(key));
	return;
}

void Buzzer::noteOff(){
	noTone(pin);
	return;
}

unsigned int Buzzer::ktof(char key){
	unsigned int f = (unsigned int)(NOTE_A4 * pow(2, ((float)(key - 81))/12.0) + 0.5);
	return max(10, f);
}
