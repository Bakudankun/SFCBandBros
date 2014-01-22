/* 
 * バンブラやる用のインターフェース。
 * ボタンからの入力をMIDIっぽい命令にしてBuzzerに渡す。
 * また、特殊コマンドの入力でステータスを変更する。
 */

#ifndef _BANDBROS_H_
#define _BANDBROS_H_

#include "Arduino.h"
#include "BBsettings.h"
#include <SNESpad.h>
#if BUZZER_EXIST
#include "Buzzer.h"
#endif
#if YMZ294_EXIST
#include "YMZ294.h"
#endif

class BandBros{
	public:
		BandBros();
		// コンストラクタ。バンブラの初期化。
		
		void reset();
		// 全部初期化する。

		int getInput();
		// ボタン入力をint型の変数に格納する。SNESpad.h参照。
		
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

		void addKey(int val); // キーをvalだけ加算する。
		
		char key; // キー。デフォルト72。
		char offset; // どのボタンでキーの音が鳴るか。0で十字ボタン下。1で十字ボタン左。-1では十字ボタン下でレの音が鳴る。
		char playing; // 今何番のノートがONか。何も鳴らしていない場合は-1にする。
		int playButton; // どのボタンが音を鳴らしているか。SNESpadに従うビットのうち１つが1になる。
		int prevButtons; // ボタン入力を最後に記録して変化を抽出するのに使う
		byte noteCounter; // LRの挙動に使うカウンター。0以外の時は既に鳴っている音に対してLRが利く。
		SNESpad m_pad; // コントローラー入力
#if BUZZER_EXIST
		Buzzer m_buzzer; // ブザー出力
#endif
#if YMZ294_EXIST
		YMZ294 m_ymz294; // 音源ICのYMZ294
#endif
#if ADXL362_EXIST
		ADXL362 m_adxl362; // 加速度センサーのADXL362
#endif
		
};

#endif
