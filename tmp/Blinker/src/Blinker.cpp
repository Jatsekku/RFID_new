#include <Arduino.h>
#include "Blinker.hpp"

void Blinker::blink(void) const{
  Serial.println("Blinker::blink()");
  while(true){
    digitalWrite(2, !digitalRead(2));
    delay(2000);
  }
}

void FastBlinker::blink(void) const{
  Serial.println("FastBlinker::blink()");
  while(true){
    digitalWrite(2, !digitalRead(2));
    delay(1000);
  }
}

void FastBlinker::fastBlink(void) const{
  Serial.println("FastBlinker::fastBlink()");
  while(true){
    digitalWrite(2, !digitalRead(2));
    delay(500);
  }
}
