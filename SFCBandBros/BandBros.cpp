#include "BandBros.h"

class BandBros{
	public:
		BandBros(byte buzzPin = -1){
			if(buzzPin >= 0 && buzzPin <= 13) buzzer = new Buzzer(buzzPin);
			key = 72;
			offset = 0;
			playing = -1;
		}
		
		void init(byte buzzPin)
		// 全部初期化する。
		{
		}
		
		void decode(int buttons)
		// 入力が変更されたときに起動し、ボタン入力によって処理を行う。
		// buttons:変更されたボタン
		{
			if(buttons == BandBros::buttons) return;
			
			BandBros::buttons = buttons;
		}

	
	private:
		char btok(int button);
		// ボタンをMIDIノート番号に変換する。
		// button:入力ボタン。ただし1になるのは十字ボタンとABXYの中から1ビットとLRのビットだけであること。
		// return:対応するノート番号。エラーの場合は負の値を返す。
		
		void noteOn(char key){ // keyの音を鳴らす。
			if(buzzer) buzzer.noteOn(key);
			return;
		}
		
		void noteOff(){
			if(buzzer) buzzer.noteOff;
			return;
		}
}