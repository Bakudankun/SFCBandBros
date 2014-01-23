#ifndef _BBSETTINGS_H_
#define _BBSETTINGS_H_

#define SNESPAD_SP 8 // コントローラのS/Pピン
#define SNESPAD_CLK 9 // コントローラのCLKピン
#define SNESPAD_DAT 10 // コントローラのDATピン

#define YMZ294_EXIST 1
#define YMZ294_PORT D // ArduinoからYMZ294にデータを送るポート
#define YMZ294_WR 11 // YMZ294のWRピン
#define YMZ294_A0 12 // YMZ294のA0ピン
#define YMZ294_RST 13 // YMZ294のRSTピン

#define BUZZER_EXIST 0
#define BUZZER_OUT 11 // ブザーに繋ぐピン

#endif
