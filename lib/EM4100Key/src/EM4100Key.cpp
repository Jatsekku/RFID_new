#include "EM4100Key.hpp"
#include "Arduino.h"

EM4100Key::EM4100Key(uint_fast64_t raw_data){
  data_be = 0;
  uint_fast64_t byte_tmp = 0;

  raw_data >>= 1;
  for(uint_fast8_t byte_idx = 0; byte_idx < 5; byte_idx++){
    raw_data >>= 5;
    byte_tmp |= (raw_data & 0x0F);
    raw_data >>= 5;
    byte_tmp |= ((raw_data & 0x0F) << 4);
    data_be |= (byte_tmp << (byte_idx * 8));
    byte_tmp = 0;
  }
}

void EM4100Key::print(void){
    Serial.println(data_be, HEX);
}
