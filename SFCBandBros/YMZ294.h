/* 
 * ArduinoでYMZ294.hをモノフォニックシンセサイザにしてMIDIっぽい命令で制御するクラス。
 * シフトレジスタを用いないので、使うにはArduinoのポートを丸々一つと、制御用に2つの計10ピン消費する。
 * noteOn/Offとピッチベンド調整、音量調節などができる。
 */

#include "Arduino.h"

#ifndef YMZ294_PORT
#define YMZ294_PORT B // ArduinoからYMZ294にデータを送るポート
#endif

#define YMZ294_MODE_NORMAL 0
#define YMZ294_MODE_UNISON 1
#define YMZ294_MODE_OCTAVE 2
#define YMZ294_MODE_5TH 3

#ifndef PITCH_RANGE
#define PITCH_RANGE 2
#endif

class YMZ294{
	public:
		YMZ294(byte wr, byte a0); 
		// コンストラクタ。
		// wr:WRに使用するピン番号。
		// a0:A0に使用するピン番号。

		void noteOn(char note);
		// MIDIノート番号noteの音を発音する。

		void noteOff();
		// 発音中の音を止める。

		void setPitch(int pitch);
		// ピッチベンドを設定する。
		// pitch:設定するピッチベンド値。-8192～8191の間。

		void setExpression(char val);
		// エクスプレッション値をvalに設定する。

		void nextTone();
		// 次の音色に切り替える。

		void prevTone();
		// 前の音色に切り替える。

	private:
		void writeResister(byte addr, byte val);
		// レジスタaddrに値valを書き込む。
		// addr:レジスタ番号。0x00～0x0D。
		// val:書き込む値

		float ntof(char note, int pitch);
		// ノート番号とピッチベンド値から発音する周波数を計算する。
		// note:ノート番号
		// pitch:ピッチベンド値
		// return:周波数

		void setTone(byte tone);
		// 音色を設定する。
		// tone:設定する音色。今はYMZ294_NORMALのみ。

		byte m_wrPin; // WRに使用するピン番号
		byte m_a0Pin; // A0に使用するピン番号
		int m_playing; // 今どの音を鳴らしているか。鳴らしていない場合は-1。
		int m_pitch; // ピッチベンドの値
		char m_expression; // エクスプレッション値
		byte m_tone; // 音色
}
