#include "Arduino.h"
#include "YMZ294.h"

#define YMZ294_CONCAT(a, b) a ## b
#define YMZ294_DDRPORT(a) YMZ294_CONCAT(DDR, a)
#define YMZ294_OUTPORT(a) YMZ294_CONCAT(PORT, a)
#define DDRP YMZ294_DDRPORT(YMZ294_PORT)
#define PORTP YMZ294_OUTPORT(YMZ294_PORT)

#define YMZ294_MODE_NORMAL 0
#define YMZ294_MODE_DETUNE 1
#define YMZ294_MODE_OCTAVE 2
#define YMZ294_MODE_5TH 3
#define YMZ294_MODE_NUMBER 4

#define NOTE_A4  440

YMZ294::YMZ294()
	: m_wr(YMZ294_WR), m_a0(YMZ294_A0), m_rst(YMZ294_RST)
{
	pinMode(m_wr, OUTPUT);
	pinMode(m_a0, OUTPUT);
	pinMode(m_rst, OUTPUT);
	digitalWrite(m_rst, LOW);
	digitalWrite(m_wr, HIGH);
	digitalWrite(m_a0, LOW);
	DDRP = B11111111;
	PORTP = B00000000;
	delay(100);
	digitalWrite(m_rst, HIGH);
	delay(200);

	noteOff();
	setPitch(0);
	setTone(YMZ294_MODE_NORMAL);
	setVolume(10);
}

void YMZ294::reset(){
	digitalWrite(m_rst, LOW);
	digitalWrite(m_wr, HIGH);
	digitalWrite(m_a0, LOW);
	DDRP = B11111111;
	PORTP = B00000000;
	delay(100);
	digitalWrite(m_rst, HIGH);
	delay(200);

	noteOff();
	setPitch(0);
	setTone(YMZ294_MODE_NORMAL);
	setVolume(10);
}

void YMZ294::noteOn(char note){
// MIDIノート番号noteの音を発音する。

	switch(m_tone){
		case YMZ294_MODE_NORMAL: // ノーマルモード
			setFrequency(0, ntof(note, m_pitch));
			if(m_playing < 0) writeResister(0x07, B111110);
			break;

		case YMZ294_MODE_DETUNE: // デチューンモード
			setFrequency(0, ntof(note, m_pitch));
			setFrequency(1, ntof(note, m_pitch)*1.01);
			setFrequency(2, ntof(note, m_pitch)*0.99);
			if(m_playing < 0) writeResister(0x07, B111000);
			break;

		case YMZ294_MODE_OCTAVE: // オクターブモード
			setFrequency(0, ntof(note, m_pitch));
			setFrequency(1, ntof(note, m_pitch)*2);
			if(m_playing < 0) writeResister(0x07, B111100);
			break;

		case YMZ294_MODE_5TH: // 5THモード
			setFrequency(0, ntof(note, m_pitch));
			setFrequency(1, ntof(note, m_pitch)*3/2);
			if(m_playing < 0) writeResister(0x07, B111100);
			break;
	}
	m_playing = note;
}

void YMZ294::noteOff(){
	if(m_playing >= 0) writeResister(0x07, B111111);
	m_playing = -1;
	return;
}

void YMZ294::setPitch(int pitch){
	m_pitch = constrain(pitch, -8192, 8191);
	switch(m_tone){
		case YMZ294_MODE_NORMAL: // ノーマルモード
			if(m_playing >= 0)setFrequency(0, ntof(m_playing, m_pitch));
			break;

		case YMZ294_MODE_DETUNE: // デチューンモード
			if(m_playing >= 0){
				setFrequency(0, ntof(m_playing, m_pitch));
				setFrequency(1, ntof(m_playing, m_pitch)*1.01);
				setFrequency(2, ntof(m_playing, m_pitch)*0.99);
			}
			break;

		case YMZ294_MODE_OCTAVE: // オクターブモード
			if(m_playing >= 0){
				setFrequency(0, ntof(m_playing, m_pitch));
				setFrequency(1, ntof(m_playing, m_pitch)*2);
			}
			break;

		case YMZ294_MODE_5TH: // 5THモード
			if(m_playing >= 0){
				setFrequency(0, ntof(m_playing, m_pitch));
				setFrequency(1, ntof(m_playing, m_pitch)*3/2);
			}
			break;
	}
	return;
}

void YMZ294::nextTone(){
	setTone((char)m_tone + 1);
	return;
}

void YMZ294::prevTone(){
	setTone((char)m_tone - 1);
	return;
}

void YMZ294::gainVolume(){
	setVolume((char)m_volume + 1);
	return;
}

void YMZ294::loseVolume(){
	setVolume((char)m_volume - 1);
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

void YMZ294::setTone(char tone){
	m_tone = constrain(tone, 0, YMZ294_MODE_NUMBER - 1);
	return;
}

void YMZ294::setVolume(char vol){
	m_volume = constrain(vol, 0, B1111);
	for(byte i=0x08; i<=0x0A; i++) writeResister(i, m_volume);
	return;
}

int YMZ294::setFrequency(byte channel, float freq){
	if(channel > 2) return 1;
	unsigned int tp = ftotp(freq);
	writeResister(channel * 2, lowByte(tp));
	writeResister(channel * 2 + 1, highByte(tp));
	return 0;
}
