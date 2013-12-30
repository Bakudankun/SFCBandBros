#include "Buzzer.h"

#define NOTE_A4  440

class Buzzer{
	public:
		Buzzer(byte pin){
			pinMode(pin, OUTPUT);
			Buzzer::pin = pin;
		}

		void noteOn(char key){
			tone(pin, ktof(key));
			return;
		}

		void noteOff(){
			noTone(pin);
			return;
		}
	
	private:
		unsigned int ktof(char key){
			unsigned int f = (unsigned int)(NOTE_A4 * pow(2, ((float)(key - 81))/12.0) + 0.5);
			return max(10, f);
		}

}