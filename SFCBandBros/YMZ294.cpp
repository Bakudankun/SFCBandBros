#include "Arduino.h"
#include "YMZ294.h"

#define DDRP DDR ## YMZ294_PORT
#define PORTP PORT ## YMZ294_PORT

YMZ294::YMZ294(byte wr, byte a0){
// コンストラクタ。
// wr:WRに使用するピン番号。
// a0:A0に使用するピン番号。
	
	m_wrPin = wr;
	m_a0Pin = a0;
	pinMode(m_wrPin, OUTPUT);
	pinMode(m_a0Pin, OUTPUT);
	DDRP = B11111111;
	PORTP = B00000000;

	noteOff();
	setPitch(0);
	setExpression(0);
	setTone(YMZ294_MODE_NORMAL);
}

void YMZ294::noteOn(char note);
// MIDIノート番号noteの音を発音する。

void YMZ294::noteOff();
// 発音中の音を止める。

void YMZ294::setPitch(int pitch);
// ピッチベンドを設定する。
// pitch:設定するピッチベンド値。-8192～8191の間。

void YMZ294::setExpression(char val);
// エクスプレッション値をvalに設定する。

void YMZ294::nextTone(){
	setTone((m_tone + 1) % 3);
	return;
}

void YMZ294::prevTone(){
	setTone((m_tone - 1) % 3);
	return;
}

int writeResister(byte addr, byte val){
	if(addr > 0x0D) return 1;

	digitalWrite(m_wr, LOW);
	digitalWrite(m_a0, LOW);
	PORTP = addr;
	digitalWrite(m_wr, HIGH);
	digitalWrite(m_wr, LOW);
	digitalWrite(m_a0, HIGH);
	PORTP = val;
	digitalWrite(m_wr, HIGH);
	digitalWrite(m_wr, LOW);
	digitalWrite(m_a0, LOW);
	PORTP = 0;
}

float ntof(char note, int pitch){
	return NOTE_A4 * pow(2, (key - 81 + ((float)constrain(pitch, -8191, 8192)) / 8192)/12.0);
}

void setTone(byte tone);
// 音色を設定する。
// tone:設定する音色。今はYMZ294_NORMALのみ。
