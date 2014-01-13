#include "Arduino.h"
#include "YMZ294.h"

#define DDRP DDR ## D
#define PORTP PORT ## D

#define YMZ294_MODE_NORMAL 0
#define YMZ294_MODE_DETUNE 1
#define YMZ294_MODE_OCTAVE 2
#define YMZ294_MODE_5TH 3
#define YMZ294_MODE_NUMBER 4

#define NOTE_A4  440

YMZ294::YMZ294(byte wr, byte a0){
	m_wr = wr;
	m_a0 = a0;
	pinMode(m_wr, OUTPUT);
	pinMode(m_a0, OUTPUT);
	digitalWrite(m_wr, HIGH);
	digitalWrite(m_a0, LOW);
	DDRP = B11111111;
	PORTP = B00000000;

	noteOff();
	setPitch(0);
	setTone(YMZ294_MODE_NORMAL);
	setVolume(15);

	noteOn(84);
	delay(500);
	noteOn(88);
	delay(500);
	noteOn(91);
	delay(500);
	noteOn(96);
	delay(500);
	noteOff();
}

void YMZ294::noteOn(char note){
// MIDIノート番号noteの音を発音する。

	switch(m_tone){
		case YMZ294_MODE_NORMAL: // ノーマルモード
			setFrequency(0, ntof(note, m_pitch));
			if(!m_playing) writeResister(0x07, B111110);
			break;

		case YMZ294_MODE_DETUNE: // デチューンモード
			break;

		case YMZ294_MODE_OCTAVE: // オクターブモード
			break;

		case YMZ294_MODE_5TH: // 5THモード
			break;
	}
	m_playing = note;
}

void YMZ294::noteOff(){
	if(m_playing) writeResister(0x07, B111111);
	m_playing = -1;
	return;
}

void YMZ294::setPitch(int pitch){
	m_pitch = constrain(pitch, -8192, 8191);
	switch(m_tone){
		case YMZ294_MODE_NORMAL: // ノーマルモード
			if(!m_playing)setFrequency(0, ntof(m_playing, m_pitch));
			break;

		case YMZ294_MODE_DETUNE: // デチューンモード
			break;

		case YMZ294_MODE_OCTAVE: // オクターブモード
			break;

		case YMZ294_MODE_5TH: // 5THモード
			break;
	}
	return;
}

void YMZ294::nextTone(){
	setTone((m_tone + 1) % YMZ294_MODE_NUMBER);
	return;
}

void YMZ294::prevTone(){
	setTone((m_tone + YMZ294_MODE_NUMBER - 1) % YMZ294_MODE_NUMBER);
	return;
}

void YMZ294::gainVolume(){
	setVolume(m_volume = constrain(m_volume + 1, 0, 15));
	return;
}

void YMZ294::loseVolume(){
	setVolume(m_volume = constrain(m_volume - 1, 0, 15));
	return;
}

int YMZ294::writeResister(byte addr, byte val){
	if(addr > 0x0D) return 1;

	digitalWrite(m_wr, LOW);
	PORTP = addr;
	digitalWrite(m_wr, HIGH);
	digitalWrite(m_a0, HIGH);
	digitalWrite(m_wr, LOW);
	PORTP = val;
	digitalWrite(m_wr, HIGH);
	digitalWrite(m_a0, LOW);
	PORTP = 0;
}

float YMZ294::ntof(char note, int pitch){
	return NOTE_A4 * pow(2, (note - 81 + PITCH_RANGE * ((float)constrain(pitch, -8191, 8191)) / 8191) / 12.0);
}

unsigned int YMZ294::ftotp(float freq){
	// ft = 1000000/8TP
	return (unsigned int)constrain((float)125000 / freq + 0.5, 1, (1 << 12) - 1);
}

void YMZ294::setTone(byte tone){
	// 音色を設定する。
	// tone:設定する音色。今はYMZ294_NORMALのみ。
	m_tone = tone;
	return;
}

void YMZ294::setVolume(byte vol){
	vol = constrain(vol, 0, 15);
	for(byte i=0x08; i<=0x0A; i++) writeResister(i, vol);
	m_volume = vol;
	return;
}

int YMZ294::setFrequency(byte channel, float freq){
	if(channel > 2) return 1;
	unsigned int tp = ftotp(freq);
	writeResister(channel * 2, lowByte(tp));
	writeResister(channel * 2 + 1, highByte(tp));
	return 0;
}
