#include <SNESpad.h>
// #include "tone.h"

SNESpad pad(2,3,4); // pin2:S/P, pin3:CLK, pin4:DAT

void setup(){ // 起動時に一度だけ呼ばれる初期化関数
	Serial.begin(57600);
}

void loop(){ // 起動後ループしつづける関数
	int input = pad.buttons();
	if(input & SNES_A) Serial.print("A ");
	if(input & SNES_B) Serial.print("B ");
	if(input & SNES_X) Serial.print("X ");
	if(input & SNES_Y) Serial.print("Y ");
	if(input & SNES_UP) Serial.print("u ");
	if(input & SNES_DOWN) Serial.print("d ");
	if(input & SNES_LEFT) Serial.print("l ");
	if(input & SNES_RIGHT) Serial.print("r ");
	if(input & SNES_L) Serial.print("L ");
	if(input & SNES_R) Serial.print("R ");
	if(input & SNES_START) Serial.print("St ");
	if(input & SNES_SELECT) Serial.print("Se ");
	Serial.println();
}
