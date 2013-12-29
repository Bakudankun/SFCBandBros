/* 
 * スーパーファミコンのコントローラーを使うためのクラス。
 */

// 各ボタンの番号をインタプリタで振る。番号の順はシリアル通信の順。
#define BUTTON_A 8
#define BUTTON_B 0
#define BUTTON_X 9
#define BUTTON_Y 1
#define BUTTON_UP 4
#define BUTTON_DOWN 5
#define BUTTON_LEFT 6
#define BUTTON_RIGHT 7
#define BUTTON_L 10
#define BUTTON_R 11
#define BUTTON_START 3
#define BUTTON_SELECT 2


class SFCControler{
  public:
    SFCControler(byte clk, byte ps, byte dat1);
    // コンストラクタ。
    // clk: CLK出力のピン番号
    // ps: P/S出力のピン番号
    // dat1: DAT1入力のピン番号
    
    void refresh();
    // コントローラーの情報を最新のものに更新する。
    
    boolean isPushed(byte button);
    // あるボタンが現在押されているかを返す。
    // button: ボタンの名前(BUTTON_*)
    // return: 押されていれば1、押されていなければ0。
    
    void getState(byte *box);
    // ボタンの状態を与えられた2バイトの配列に収める。
    // box: ボタンの状態を収める配列(2バイト)
    
    int setPins(byte clk, byte ps, byte dat1);
    // ピン番号を設定する。
    // clk: CLK出力のピン番号
    // ps: P/S出力のピン番号
    // dat1: DAT1出力のピン番号
    // return: 設定が成功したら0、失敗したら1。

  private:
    byte CLK; // CLKピン番号(出力)
    byte PS; // P/Sピン番号(出力)
    byte DAT1; // DAT1ピン番号(入力)
    byte[2] buttonState; // ボタン状態。[0]のMSBから順にBYSeStudlrAXLR。
}
