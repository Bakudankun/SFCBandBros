#include "BandBros.h"
// #include <SNESpad.h>

BandBros game();

void setup(){ // 起動時に一度だけ呼ばれる初期化関数
	// Serial.begin(57600);
}

void loop(){ // 起動後ループしつづける関数
	int input = 0;
	for(byte i = 0; i < 20; i++) input |= game.getInput(); // 確認のため20回回す
	// if(input & SNES_A) Serial.print("A ");
	// if(input & SNES_B) Serial.print("B ");
	// if(input & SNES_X) Serial.print("X ");
	// if(input & SNES_Y) Serial.print("Y ");
	// if(input & SNES_UP) Serial.print("^ ");
	// if(input & SNES_DOWN) Serial.print("v ");
	// if(input & SNES_LEFT) Serial.print("< ");
	// if(input & SNES_RIGHT) Serial.print("> ");
	// if(input & SNES_L) Serial.print("L ");
	// if(input & SNES_R) Serial.print("R ");
	// if(input & SNES_START) Serial.print("St ");
	// if(input & SNES_SELECT) Serial.print("Se ");
	// Serial.println();

	game.decode(input);
}
