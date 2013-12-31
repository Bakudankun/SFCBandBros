/* 
 * バンブラやる用のインターフェース。
 * ボタンからの入力をMIDIっぽい命令にしてBuzzerに渡す。
 * また、特殊コマンドの入力でステータスを変更する。
 */

#include "Arduino.h"
#include <SNESpad.h>
#include "Buzzer.h"

class BandBros{
	public:
		BandBros(byte buzzPin = -1);
		// コンストラクタ。バンブラの初期化。
		// buzzPin:ブザー出力のピン番号。-1の場合はブザー無し。
		
		void reset(); // 全部初期化する。
		
		void decode(int buttons);
		// 入力が変更されたときに起動し、ボタン入力によって処理を行う。
		// buttons:変更されたボタン
		
	
	private:
		char btok(int button);
		// ボタンをMIDIノート番号に変換する。
		// button:入力ボタン。ただし1になるのは十字ボタンとABXYの中から1ビットとLRのビットだけであること。
		// return:対応するノート番号。エラーの場合は負の値を返す。
		
		void noteOn(char key); // keyの音を鳴らす。
		
		void noteOff(); // 鳴っている音を止める。
		
		char key; // キー。デフォルト72。
		char offset; // どのボタンでキーの音が鳴るか。0で十字ボタン下。1で十字ボタン左。-1では十字ボタン下でレの音が鳴る。
		char playing; // 今どの音を鳴らしているか。何も鳴らしていない場合は-1にする。
		int buttons; // ボタン入力
		Buzzer *buzzer; // ブザー出力。ブザーが無い時はnull。
		
};
