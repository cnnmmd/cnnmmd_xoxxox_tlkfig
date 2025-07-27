//--------------------------------------------------------------------------

#ifndef PARAMS
#define PARAMS

//--------------------------------------------------------------------------
// 参照

#include <Arduino.h>

//--------------------------------------------------------------------------
// 定義：変数

// 通信
const char* wifiid = "XXX"; // 無線（Wifi）：ＩＤ
const char* wifipw = "XXX"; // 無線（Wifi）：パスワード
const char* srvadr = "192.168.0.1"; // アドレス
const uint16_t srvprt = 10001;
const char* pthsnd = "/sps000";
const char* pthrcv = "/gpp000";

// 音声
const char* pthaud = "/vcetmp.pcm"; // 音声ファイルの格納場所（一時的）
const int secrec = 5; // 録音時間（秒）
const float volume = 0.5; // 調整：音量

// 光源
constexpr int pinred =  2; // ピン番号（赤）
constexpr int pinblu =  5; // ピン番号（青）
constexpr int pingrn = 17; // ピン番号（緑）
constexpr int maxswt = 10; // 発光を切り替える間隔（音声のバッファを１フレームとして、Ｎフレームごとに）

//--------------------------------------------------------------------------

#endif // PARAMS
