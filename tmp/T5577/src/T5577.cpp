#include <Arduino.h>

T5577::T5577(uint_fast32_t min_time, uint_fast32_t max_time)
  : pulse(min_time, max_time),
    buffer(0){}

ICACHE_RAM_ATTR void T5577::rxEdgeCallback(void){

  static uint_fast32_t last_timestamp;
  static uint_fast32_t edge_counter;
  static uint_fast16_t bit_index;
  static bool bit_value;

  uint_fast32_t current_timestamp = micros();
  pulse.loadWidth(current_timestamp - last_timestamp);
  last_timestamp = current_timestamp;

  if(edge_counter == 0){
    buffer = 0;
    bit_index = 0;
    bit_value = 0;
  }

  if(pulse.isHalfSymbol()){       // Short pulse
    if((edge_counter % 2) == 0){
      buffer <<= 1;
      buffer |= bit_value;
      bit_index++;
    }
    edge_counter ++;
  }else if(pulse.isFullSymbol()){ // Long pulse
    bit_value = !bit_value;
    buffer <<= 1;
    buffer |= bit_value;
    bit_index++;
    edge_counter += 2;
  }else{                          // Invalid pulse
    edge_counter = 0;
  }

  if(bit_index > 64){
    edge_counter = 0;
    if(T5577Utils::completeProcessing(buffer)){
      new_key_callback(T5577Key(buffer));
    }
  }
}

void T5577::registerNewKeyCallback(new_key_callback_t new_key_callback){
  this->new_key_callback = new_key_callback;
}
