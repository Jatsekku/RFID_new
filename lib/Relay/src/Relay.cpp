
#include <Arduino.h>
#include "Relay.hpp"

Relay::Relay(uint_fast8_t ctrl_pin, bool inverted_logic):
  ctrl_pin(ctrl_pin), inverted_logic(inverted_logic){

  digitalWrite(ctrl_pin, inverted_logic); // INFO(Jacek): Turn off the relay
  pinMode(ctrl_pin, OUTPUT);
};

void Relay::on(void){
  digitalWrite(ctrl_pin, !inverted_logic);
}

void Relay::off(void){
  digitalWrite(ctrl_pin, inverted_logic);
}

void Relay::setOnForMs(uint_fast32_t on_time_ms){
  on();
  timer_active = true;
  elapsed_time = 0;
  delay_time = on_time_ms;
}

void Relay::updateTimer(uint_fast32_t tick_ms){
  static uint_fast32_t last_timestamp;
  static uint_fast32_t last_elapsed_time;

  if(timer_active){
    if(tick_ms < last_timestamp){ // INFO(Jacek): Timer overflow detection;
      elapsed_time = (time_limit - last_timestamp) + tick_ms;
    }else{
      elapsed_time += (tick_ms - last_timestamp);
    }
    if((elapsed_time >= delay_time) || (elapsed_time < last_elapsed_time)){
      off();
      timer_active = false;
      elapsed_time = 0;
    }
  }
  last_timestamp = tick_ms;
  last_elapsed_time = elapsed_time;
}
