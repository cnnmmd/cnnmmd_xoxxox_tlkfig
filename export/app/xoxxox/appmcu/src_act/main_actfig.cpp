//--------------------------------------------------------------------------
// 参照

#include "params.h"

//--------------------------------------------------------------------------
// 設定

IPAddress adrslf;
ServoEasing servox;
ServoEasing servoy;
WebServer server;
DynamicJsonDocument dicang(200);
int angdfy, angdfx;
int mscdfy, mscdfx;

//--------------------------------------------------------------------------
// 定義

void hdlMov() {
  if (server.hasArg("plain")) {
    deserializeJson(dicang, server.arg("plain"));
    angdfx = dicang["dfx"].as<int>();
    angdfy = dicang["dfy"].as<int>();
    mscdfx = dicang["msx"].as<int>();
    mscdfy = dicang["msy"].as<int>();
    angcox = angcox + angdfx;
    angcoy = angcoy + angdfy;
    Serial.print("x:"); Serial.println(angcox); // DBG
    Serial.print("y:"); Serial.println(angcoy); // DBG
    servox.easeToD(angcox, mscdfx); // 角度：左右
    servoy.easeToD(angcoy, mscdfy); // 角度：上下
    server.send(200, "text/plain", "sts: update servo angles");
  }
  else {
    server.send(400, "text/plain", "err: invalid request");
  }
}

//--------------------------------------------------------------------------
// 処理（初期）

void setup() {
  Serial.begin(115200);
  WiFi.begin(keynet, pwdnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("sts: connect wifi"); // DBG
  adrslf = WiFi.localIP();
  Serial.println(adrslf);
  // サーボの初期化
  servox.attach(pinsvx);
  servoy.attach(pinsvy);
  servox.setEasingType(modang);
  servoy.setEasingType(modang);
  servox.startEaseTo(angcox);
  servoy.startEaseTo(angcoy);
  server.on("/", HTTP_POST, hdlMov);
  server.begin();
  Serial.println("sts: start server"); // DBG
}

//--------------------------------------------------------------------------
// 処理（反復）

void loop() {
  server.handleClient();
}
