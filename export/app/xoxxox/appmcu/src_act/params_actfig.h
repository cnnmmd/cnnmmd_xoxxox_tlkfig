//--------------------------------------------------------------------------

#ifndef PARAMS
#define PARAMS

//--------------------------------------------------------------------------
// 参照

#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ServoEasing.hpp>

//--------------------------------------------------------------------------
// 定義：変数

const char* keynet = "XXX"; // 無線（Wifi）：ＩＤ
const char* pwdnet = "XXX"; // 無線（Wifi）：パスワード
const int pinsvx = 25;
const int pinsvy = 21;
int angcox = 90;
int angcoy = 90;
const int modang = EASE_LINEAR;

//--------------------------------------------------------------------------

#endif // PARAMS
