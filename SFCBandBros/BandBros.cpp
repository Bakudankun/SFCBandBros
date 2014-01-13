#include "BandBros.h"

#define LRCOUNTER 15

BandBros::BandBros(Buzzer *buzz, YMZ294 *ymz294){
	m_buzzer = buzz;
	m_ymz294 = ymz294;
	key = 72;
	offset = 0;
	playing = -1;
	playButton = 0;
	prevButtons = 0;
	noteCounter = 0;
}

void BandBros::reset(){
	noteOff();
	if(m_ymz294) m_ymz294->reset();
	key = 72;
	offset = 0;
	playing = -1;
	playButton = 0;
	prevButtons = 0;
	noteCounter = 0;
	return;
}

void BandBros::decode(int buttons){
	int ctrl = 0;

	if(buttons == (SNES_L | SNES_R | SNES_START | SNES_SELECT)){
		reset();
		return;
	}
	if(noteCounter) noteCounter--;
	if(buttons == prevButtons) return;
	if(!(playButton & buttons)){
		noteOff();
		playButton = 0;
		noteCounter = 0;
	}
	if(buttons & SNES_START){
		ctrl = buttons & ~prevButtons;
		if(ctrl & SNES_LEFT) addKey(-1);
		if(ctrl & SNES_RIGHT) addKey(1);
		if(ctrl & SNES_UP) addKey(12);
		if(ctrl & SNES_DOWN) addKey(-12);
		if(ctrl & SNES_L) offset--;
		if(ctrl & SNES_R) offset++;
		if(ctrl & SNES_SELECT){
			key = 72;
			offset = 0;
		}
	} else if(buttons & SNES_SELECT){
		ctrl = buttons & ~prevButtons;
		if(ctrl & SNES_LEFT){
			if(m_ymz294) m_ymz294->prevTone();
		}
		if(ctrl & SNES_RIGHT){
			if(m_ymz294) m_ymz294->nextTone();
		}
		if(ctrl & SNES_UP){
			if(m_ymz294) m_ymz294->gainVolume();
		}
		if(ctrl & SNES_DOWN){
			if(m_ymz294) m_ymz294->loseVolume();
		}
	} else if(ctrl = (buttons & ~prevButtons) & (SNES_A | SNES_B | SNES_X | SNES_Y | SNES_UP | SNES_DOWN | SNES_LEFT | SNES_RIGHT)){
		for(int i = 0; i < 12; i++){
			if(bitRead(ctrl, i)){
				noteOn(btok(bit(i) | (buttons & (SNES_L | SNES_R))));
				playButton = bit(i);
				noteCounter = LRCOUNTER;
				break;
			}
		}
	} else if(noteCounter && ((buttons ^ prevButtons) & (SNES_L | SNES_R))){
		noteOn(playing + ((buttons & SNES_L) - (prevButtons & SNES_L))/SNES_L + ((buttons & SNES_R) - (prevButtons & SNES_R))/SNES_R*12);
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
	nbutton -= offset;

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
		}
	}
	if(button & SNES_L) val++;
	if(button & SNES_R) val += 12;

	return constrain(val, 0, 127);
}

void BandBros::noteOn(char key){
	key = constrain(key, 0, 127);
	if(playing >= 0) noteOff();
	if(m_buzzer) m_buzzer->noteOn(key);
	if(m_ymz294) m_ymz294->noteOn(key);
	playing = key;
	return;
}

void BandBros::noteOff(){
	if(playing < 0) return;
	if(m_buzzer) m_buzzer->noteOff();
	if(m_ymz294) m_ymz294->noteOff();
	playing = -1;
	return;
}

void BandBros::addKey(int val){
	val = val + key;
	if(val >= 0 && val <= 127) key = val;
	return;
}
