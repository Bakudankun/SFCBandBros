#include <SNESpad.h>
#include "tone.h"

SNESpad pad(2,3,4); // pin2:S/P, pin3:CLK, pin4:DAT

void setup(){ // 起動時に一度だけ呼ばれる初期化関数
	Serial.begin(57600);
	pinMode(BUZZER, OUTPUT);
}

void loop(){ // 起動後ループしつづける関数
	int input = pad.buttons();
	if(input & SNES_A){
		Serial.print("A ");
		noteOn(83);
	}
	if(input & SNES_B){
		Serial.print("B ");
		noteOn(81);
	}
	if(input & SNES_X){
		Serial.print("X ");
		noteOn(84);
	}
	if(input & SNES_Y){
		Serial.print("Y ");
		noteOn(79);
	}
	if(input & SNES_UP){
		Serial.print("u ");
		noteOn(76);
	}
	if(input & SNES_DOWN){
		Serial.print("d ");
		noteOn(72);
	}
	if(input & SNES_LEFT){
		Serial.print("l ");
		noteOn(74);
	}
	if(input & SNES_RIGHT){
		Serial.print("r ");
		noteOn(77);
	}
	if(input & SNES_L){Serial.print("L ");}
	if(input & SNES_R){Serial.print("R ");}
	if(input & SNES_START){Serial.print("St ");}
	if(input & SNES_SELECT){Serial.print("Se ");}
	if(!input) noteOff();
	Serial.println();
}
