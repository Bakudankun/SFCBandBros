#include "BandBros.h"

#define LRCOUNTER 100

BandBros::BandBros(byte buzzPin = -1){
	if(buzzPin >= 0 && buzzPin <= 13) buzzer = new Buzzer(buzzPin);
	key = 72;
	offset = 0;
	playing = -1;
	playButton = 0;
	prevButtons = 0;
	noteCounter = 0;
}

void BandBros::reset(){
	noteOff();
	BandBros(buzzPin);
	return;
}

void BandBros::decode(int buttons)
	// 入力が変更されたときに起動し、ボタン入力によって処理を行う。
	// buttons:変更されたボタン
{
	if(noteCounter) noteCounter--;
	if(buttons == prevButtons) return;
	if(!(playButton & buttons)){
		noteOff();
		playButton = 0;
		noteCounter = 0;
	}
	if(buttons & SNES_START){
		int ctrl = buttons & ~prevButtons;
		if(ctrl & SNES_LEFT) key--;
		if(ctrl & SNES_RIGHT) key++;
		if(ctrl & SNES_UP) key+=12;
		if(ctrl & SNES_DOWN) key-=12;
		if(ctrl & SNES_L) offset--;
		if(ctrl & SNES_R) offset++;
		key = constrain(key, 0, 127);
	} else if(int ctrl = (buttons & ~prevButtons) & (SNES_A | SNES_B | SNES_X | SNES_Y | SNES_UP | SNES_DOWN | SNES_LEFT | SNES_RIGHT)){
		for(int i = 0; i < 12; i++){
			if(bitRead(ctrl, i)){
				noteOn(btok(bit(i) | (buttons & (SNES_L | SNES_R))));
				playButton = bit(i);
				noteCounter = LRCOUNTER;
				break;
			}
		}
	} else if((noteCounter > 0) && (int ctrl = ((buttons & ~prevButtons) & (SNES_L | SNES_R)))){
		noteOn(playing + ((ctrl & SNES_L)?1:0) + ((ctrl & SNES_R)?12:0));
		noteCounter = LRCOUNTER;
	}

	prevButtons = buttons;
}


char BandBros::btok(int button){
	int nbutton = 0; // キーのボタンから何番目のボタンが押されたか
	
	switch(button & (SNES_A | SNES_B | SNES_X | SNES_Y | SNES_UP | SNES_DOWN | SNES_LEFT | SNES_RIGHT)){
		case SNES_A:
			nbutton = 6;
			break;
		case SNES_B:
			nbutton = 5;
			break;
		case SNES_X:
			nbutton = 7;
			break;
		case SNES_Y:
			nbutton = 4;
			break;
		case SNES_UP:
			nbutton = 2;
			break;
		case SNES_DOWN:
			nbutton = 0;
			break;
		case SNES_LEFT:
			nbutton = 1;
			break;
		case SNES_RIGHT:
			nbutton = 3;
			break;
		default:
			return -1;
			break;
	}
	nbutton += offset;

	int val = key; // 返すノート番号
	if(nbutton >= 0){
		for(int i = 0; i < nbutton; i++){
			switch(i%7){
				case 0:
					val += 2;
					break;
				case 1:
					val += 2;
					break;
				case 2:
					val += 1;
					break;
				case 3:
					val += 2;
					break;
				case 4:
					val += 2;
					break;
				case 5:
					val += 2;
					break;
				case 6:
					val += 1;
					break;
			}
		}
	} else {
		for(int i = 0; i > nbutton; i--){
			switch(i%7){
				case 0%7:
					val -= 1;
					break;
				case -1%7:
					val -= 2;
					break;
				case -2%7:
					val -= 2;
					break;
				case -3%7:
					val -= 2;
					break;
				case -4%7:
					val -= 1;
					break;
				case -5%7:
					val -= 2;
					break;
				case -6%7:
					val -= 2;
					break;
	}
	if(button & SNES_L) val++;
	if(button & SNES_R) val += 12;

	return constrain(val, 0, 127);
}

void BandBros::noteOn(char key){
	key = constrain(key, 0, 127);
	if(playing >= 0) noteOff();
	if(buzzer) buzzer.noteOn(key);
	playing = key;
	return;
}

void BandBros::noteOff(){
	if(playing < 0) return;
	if(buzzer) buzzer.noteOff();
	playing = -1;
	return;
}

