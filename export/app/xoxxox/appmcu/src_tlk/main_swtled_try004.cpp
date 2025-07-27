#include <Arduino.h>
#include <M5Stack.h>
#include "params.h"

void setup() {
  pinMode(pinred, OUTPUT);
  pinMode(pinblu, OUTPUT);
  pinMode(pingrn, OUTPUT);
  ledcSetup(0, 1000 , 8);
  ledcSetup(2, 1000 , 8);
  ledcSetup(4, 1000 , 8);
  ledcAttachPin(pinred, 0);
  ledcAttachPin(pinblu, 2);
  ledcAttachPin(pingrn, 4);
}

void loop() {
  ledcWrite(0, 128);
  ledcWrite(2,   0);
  ledcWrite(4,  32);
  delay(1000);
  ledcWrite(0, 128);
  ledcWrite(2,  64);
  ledcWrite(4,  64);
  delay(1000);
}
