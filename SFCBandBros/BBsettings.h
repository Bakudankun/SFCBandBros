#ifndef _BBSETTINGS_H_
#define _BBSETTINGS_H_

#define SNESPAD_SP 5 // コントローラのS/Pピン
#define SNESPAD_CLK 6 // コントローラのCLKピン
#define SNESPAD_DAT 7 // コントローラのDATピン

#define YMZ294_EXIST 1 // YMZ294が繋がれているかどうか
#if YMZ294_EXIST
#define YMZ294_PORT C // ArduinoからYMZ294にデータを送るポート
#define YMZ294_WR 8 // YMZ294のWRピン
#define YMZ294_A0 9 // YMZ294のA0ピン
// #define YMZ294_RST 13 // YMZ294のRSTピン
#endif

#define BUZZER_EXIST 0 // ブザーが繋がれているかどうか
#if BUZZER_EXIST
#define BUZZER_OUT 11 // ブザーに繋ぐピン
#endif

#define ADXL362_EXIST 0
// 加速度センサーADXL362が繋がれているかどうか。
// これが使われている場合、他のセンサでピン10～13を使うことはできない。

#endif
