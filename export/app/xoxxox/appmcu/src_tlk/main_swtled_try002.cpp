#include <Arduino.h>
#include <M5Stack.h>
#include "params.h"

void setup() {
  pinMode(pinred, OUTPUT);
  pinMode(pinblu, OUTPUT);
  pinMode(pingrn, OUTPUT);
}

void loop() {
  digitalWrite(pinred, HIGH);
  digitalWrite(pinblu, LOW);
  digitalWrite(pingrn, LOW);
  delay(1000);
  digitalWrite(pinred, LOW);
  digitalWrite(pinblu, HIGH);
  digitalWrite(pingrn, LOW);
  delay(1000);
  digitalWrite(pinred, LOW);
  digitalWrite(pinblu, LOW);
  digitalWrite(pingrn, HIGH);
  delay(1000);
  digitalWrite(pinred, HIGH);
  digitalWrite(pinblu, HIGH);
  digitalWrite(pingrn, HIGH);
  delay(1000);
  digitalWrite(pinred, LOW);
  digitalWrite(pinblu, LOW);
  digitalWrite(pingrn, LOW);
  delay(1000);
}
