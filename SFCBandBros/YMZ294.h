/* 
 * ArduinoでYMZ294.hをモノフォニックシンセサイザにしてMIDIっぽい命令で制御するクラス。
 * noteOn/Offとピッチベンド調整、音量調節などができる。
 */

#include "Arduino.h"

#define YMZ294_NORMAL 0
#define YMZ294_UNISON 1
#define YMZ294_OCTAVE 2
#define YMZ294_5TH 3

#define PITCH_RANGE 2

class YMZ294{
	public:
		YMZ294(); // コンストラクタ

		void noteOn(char note);
		// MIDIノート番号noteの音を発音する。

		void noteOff();
		// 発音中の音を止める。

		void setPitch(int pitch);
		// ピッチベンドを設定する。
		// pitch:設定するピッチベンド値。-8192〜8191の間。

		void setExpression(char val);
		// エクスプレッション値をvalに設定する。

		void nextTone();
		// 次の音色に切り替える。

		void prevTone();
		// 前の音色に切り替える。

	private:
		void writeResister(byte addr, byte val);
		// レジスタaddrに値valを書き込む。
		// addr:レジスタ番号。0x00〜0x0D。
		// val:書き込む値

		float ntof(char note, int pitch);
		// ノート番号とピッチベンド値から発音する周波数を計算する。
		// note:ノート番号
		// pitch:ピッチベンド値
		// return:周波数

		void setTone(byte tone);
		// 音色を設定する。
		// tone:設定する音色。今はYMZ294_NORMALのみ。

		int m_playing; // 今どの音を鳴らしているか。鳴らしていない場合は-1。
		int m_pitch; // ピッチベンドの値
		char m_expression; // エクスプレッション値
		byte m_tone; // 音色
}
