/* 
 * キー番号からtone関数で音を鳴らすための関数群。
 */

#include "Arduino.h"

#define NOTE_A4  440
#define BUZZER 6

unsigned int ktof(byte key){
	// キー番号からtone関数で使うための周波数をunsigned intで返す。
	// key: キー番号。MIDIに従い、A4が81。
	// return: 周波数。tone関数の引数がunsigned intのため四捨五入して返す。
	//         A4が440Hzだが、10Hzを下回らない。

	unsigned int f = (unsigned int)(440 * pow(2, ((float)(key - 81))/12.0) + 0.5);
	return max(10, f);
}

void noteOn(byte key){
	tone(BUZZER, ktof(key));
	return;
}

void noteOff(){
	noTone(BUZZER);
	return;
}



