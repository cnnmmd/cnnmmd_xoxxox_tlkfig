//--------------------------------------------------------------------------
// 参照

#include "shared.h"
#include "params.h"

//--------------------------------------------------------------------------
// 関数

void swtled(int swt) {
  if (swt == 0) {
    digitalWrite(pinred, HIGH);
    digitalWrite(pinblu, HIGH);
    digitalWrite(pingrn, HIGH);
  }
  if (swt == 1) {
    digitalWrite(pinred, HIGH);
    digitalWrite(pinblu, LOW);
    digitalWrite(pingrn, LOW);
  }
}

// 光源：初期
void iniled() {
  pinMode(pinred, OUTPUT);
  pinMode(pinblu, OUTPUT);
  pinMode(pingrn, OUTPUT);
}

// 通信／音声／光源：サーバから音声データを取得〜音声を再生〜発光を切替
void rcvvce() {
  cliweb.setTimeout(15000); // タイムアウト（15 sec）
  cliweb.begin(urlrcv);
  int resweb = cliweb.GET();
  if (resweb == HTTP_CODE_OK) {
    WiFiClient* stream = cliweb.getStreamPtr();
    uint8_t buffer[lenbff_rcv];

    int flgled = 0; // 光源：発光
    int cntswt = 0; // 光源：発光
    while (stream->available()) {
      size_t difcon = stream->readBytes(buffer, sizeof(buffer));
      modvol(buffer, sizeof(buffer), volume); // 調整：音量
      size_t difbff;
      i2s_write(I2S_NUM_0, (uint8_t*)buffer, difcon, &difbff, portMAX_DELAY);
      // 光源：発光
      if (cntswt >= maxswt) {
        if (flgled == 0) {
          swtled(1);
          flgled = 1;
        }
        else {
          swtled(0);
          flgled = 0;
        }
        cntswt = 0;
      }
      cntswt = cntswt + 1;
      //
    }
  }
  else {
    Serial.println("err: recieve data from server"); // DBG
  }
  cliweb.end();
}

//--------------------------------------------------------------------------
// 処理

// 初期
void setup() {
  inienv();
  cnnnet();
  iniled();
}

// 反復
void loop() {
  // 初期
  M5.update(); // ボタンの状態を更新
  // 送信
  inii2s_snd();
  setmsg("rec: bgn");
  recvce();
  setmsg("rec: end");
  sndvce();
  endi2s();
  // 受信
  inii2s_rcv();
  setmsg("ply: bgn");
  rcvvce();
  setmsg("ply: end");
  endi2s();
  // 初期
  setmsg("prc: ini");
  while (! (M5.BtnC.wasPressed())) {
    M5.update(); // ボタンの状態を再度更新
    delay(10);
  }
}
