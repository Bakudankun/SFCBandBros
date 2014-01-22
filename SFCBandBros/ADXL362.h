/* 
 * 加速度センサーADXL362を使うためのライブラリ。
 * ArduinoのSPIライブラリを使用するので10～13ピンを消費する。
 */

#ifndef _ADXL362_H_
#define _ADXL362_H_

#include "Arduino.h"
#include <SPI.h>

#define ADXL362_MODE_NORMAL B00000010
#define ADXL362_MODE_LOW_NOISE B00010010
#define ADXL362_MODE_ULTRA_LOW_NOISE B00100010

class ADXL362{
	public:
		ADXL362(byte range, byte mode);
		// コンストラクタ。
		// range:測定レンジ
		// mode:低ノイズモードの設定。ADXL362_MODE_NORMAL,ADXL362_MODE_LOW_NOISE,ADXL362_MODE_ULTRA_LOW_NOISEのいずれか。

		void reset();
		// ソフトリセットする。

		int getAccel(char axis);
		// 1軸の加速度を取得する。
		// axis:'x','y','z'のいずれか。
		// return:取得した加速度。

		void get3Accel(int a[3]);
		// 3軸の加速度をすべて取得する。
		// a[3]:取得した3軸の加速度を格納する配列。


	private:
		void setRange(byte range);
		// 測定レンジを設定する。
		// range:2,4,8のいずれか。

		void readRegister(byte addr, byte *val, byte n=1);
		// レジスタを読む。第三引数を2以上に指定すると複数バイトを同時に読み出す。
		// addr:読みたいレジスタのアドレス
		// val:読んだ結果を格納する配列
		// n:そこから何バイト読むか

		void writeRegister(byte addr, byte *val, byte n=1);
		// レジスタを書く。第三引数を2以上に指定すると複数バイトを同時に書き出す。
		// addr:書きたいレジスタのアドレス
		// val:書く内容を格納するnバイトの配列
		// n:そこから何バイト書くか

};

#endif
