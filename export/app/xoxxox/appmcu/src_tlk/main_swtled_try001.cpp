#include <Arduino.h>
#include <M5Stack.h>
#include "params.h"

void setup() {
  pinMode(pinred, OUTPUT);
}

void loop() {
  digitalWrite(pinred, HIGH);
  delay(1000);
  digitalWrite(pinred, LOW);
  delay(1000);
}
