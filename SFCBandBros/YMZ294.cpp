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

void YMZ294::nextTone();
// 次の音色に切り替える。

void YMZ294::prevTone();
// 前の音色に切り替える。

int writeResister(byte addr, byte val){
// レジスタaddrに値valを書き込む。
// addr:レジスタ番号。0x00～0x0D。
// val:書き込む値
// return:成否

	
}

float ntof(char note, int pitch);
// ノート番号とピッチベンド値から発音する周波数を計算する。
// note:ノート番号
// pitch:ピッチベンド値
// return:周波数

void setTone(byte tone);
// 音色を設定する。
// tone:設定する音色。今はYMZ294_NORMALのみ。
