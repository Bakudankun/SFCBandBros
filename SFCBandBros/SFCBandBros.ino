#define SNESPAD_SP 8 // コントローラのS/Pピン
#define SNESPAD_CLK 9 // コントローラのCLKピン
#define SNESPAD_DAT 10 // コントローラのDATピン
#define YMZ294_PORT D // ArduinoからYMZ294にデータを送るポート
#define YMZ294_WR 11 // YMZ294のWRピン
#define YMZ294_A0 12 // YMZ294のA0ピン
#define BUZZER 8 // ブザーに繋ぐピン

#include <SNESpad.h>
#include "BandBros.h"
#include "Buzzer.h"
#include "YMZ294.h"

SNESpad *pad = NULL;
Buzzer *buzzer = NULL;
YMZ294 *ymz294 = NULL;
BandBros *game;

void setup(){ // 起動時に一度だけ呼ばれる初期化関数
	pad = new SNESpad(SNESPAD_SP,SNESPAD_CLK,SNESPAD_DAT);
	// buzzer = new Buzzer(BUZZER);
	ymz294 = new YMZ294(YMZ294_WR, YMZ294_A0);
	game = new BandBros(buzzer, ymz294);
	// Serial.begin(57600);
}

void loop(){ // 起動後ループしつづける関数
	int input = 0;
	for(byte i = 0; i < 20; i++) input |= pad->buttons(); // 確認のため20回回す
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

	game->decode(input);
}
