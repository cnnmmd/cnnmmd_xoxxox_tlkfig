#include <Arduino.h>
#include <M5Stack.h>
#include "params.h"

void setup() {
  pinMode(pinred, OUTPUT);
  pinMode(pinblu, OUTPUT);
  pinMode(pingrn, OUTPUT);
}

void loop() {
  analogWrite(pinred, 128);
  analogWrite(pinblu,   0);
  analogWrite(pingrn,  32);
  delay(1000);
  analogWrite(pinred, 128);
  analogWrite(pinblu,  64);
  analogWrite(pingrn,  64);
  delay(1000);
}
