/* 
 * ArduinoでYMZ294.hをモノフォニックシンセサイザにしてMIDIっぽい命令で制御するクラス。
 * シフトレジスタを用いないので、使うにはArduinoのポートを丸々一つと、制御用に2つの計10ピン消費する。
 * noteOn/Offとピッチベンド調整、音量調節などができる。
 */

#ifndef _YMZ294_H_
#define _YMZ294_H_

#include "Arduino.h"
#include "BBsettings.h"

#ifndef PITCH_RANGE
#define PITCH_RANGE 2 // ピッチベンドのレンジ
#endif

class YMZ294{
	public:
		YMZ294(); 
		// コンストラクタ

		void reset();
		// RSTを0にしてYMZ294をリセットする。

		void noteOn(char note);
		// MIDIノート番号noteの音を発音する。

		void noteOff();
		// 発音中の音を止める。

		void setPitch(int pitch);
		// ピッチベンドを設定する。
		// pitch:設定するピッチベンド値。-8192～8191の間。

		void nextTone();
		// 次の音色に切り替える。

		void prevTone();
		// 前の音色に切り替える。

		void gainVolume();
		// 全体音量を上げる。

		void loseVolume();
		// 全体音量を下げる。

	private:
		int writeResister(byte addr, byte val);
		// レジスタaddrに値valを書き込む。
		// addr:レジスタ番号。0x00～0x0D。
		// val:書き込む値
		// return:成否。成功したら0。

		float ntof(char note, int pitch);
		// ノート番号とピッチベンド値から発音する周波数を計算する。
		// note:ノート番号
		// pitch:ピッチベンド値
		// return:周波数

		unsigned int ftotp(float freq);
		// 周波数の値から変数TPとして出力されるべき12ビットの値に変換する。
		// freq:出力したい周波数
		// return:TPとして出力するべき値

		void setTone(char tone);
		// 音色を設定する。
		// tone:設定する音色。今はYMZ294_NORMALのみ。

		void setVolume(char vol);
		// 全体の音量を設定する。0～15の16段階。
		// vol:設定する音量。0～15。これを外れた場合はconstrainされる。

		int setFrequency(byte channel, float freq);
		// 各チャンネルの周波数を設定する。
		// channel:設定するチャンネル。0～2。
		// freq:設定する周波数。
		// return:成否。成功したら0。

		byte m_wr; // WRに使用するピン番号
		byte m_a0; // A0に使用するピン番号
		byte m_rst; // rstに使用するピン番号
		char m_playing; // 今MIDIノート番号でどの音を鳴らしているか。鳴らしていない場合は-1。
		int m_pitch; // ピッチベンドの値。-8192～8191の間。
		byte m_tone; // 音色
		byte m_volume; // 全体の音量
};

#endif
