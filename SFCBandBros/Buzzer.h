/* 
 * Buzzerクラス。MIDIっぽい命令でブザーを鳴らす。
 */

#ifndef _BUZZER_H_
#define _BUZZER_H_

#include "Arduino.h"

class Buzzer{
	public:
		Buzzer(byte pin);
		// コンストラクタ。ピン番号pinのブザーを起動する。
		// pin:ブザーを繋いだピン番号
		
		void noteOn(char key);
		// ノート番号keyの音を鳴らす。

		void noteOff();
		// 今鳴っている音を止める。
	
	private:
		unsigned int ktof(char key);
		// キー番号からtone関数で使うための周波数をunsigned intで返す。
		// key: キー番号。MIDIに従い、A4が81。
		// return: 周波数。tone関数の引数がunsigned intのため四捨五入して返す。
		//         A4が440Hzだが、31Hzを下回らない。
		
		byte pin; // ブザー出力のピン番号

};

#endif
