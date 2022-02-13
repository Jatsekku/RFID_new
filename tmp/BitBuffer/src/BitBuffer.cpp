#include <Arduino.h>
#include "bitbuffer.hpp"

BitBuffer::BitBuffer(void)
  : buffer(0){}

BitBuffer::BitBuffer(const BitBuffer &original_object)
  : buffer(original_object.buffer){};

void BitBuffer::setBit(uint_fast16_t index, bool bit_value){
  if(bit_value == true){
    buffer |= (1<<index);
  }else{
    buffer &= ~(1<<index);
  }
}

bool BitBuffer::getBit(uint_fast16_t index){
  return buffer & (1<<index);
}

void BitBuffer::clear(void){
  buffer = 0;
}

void BitBuffer::shiftLeft(uint_fast16_t shift_value){
  buffer <<= shift_value;
}

void BitBuffer::rollLeft(uint_fast16_t roll_value){
  bool ms_bit = (buffer & ms_bit_mask) ? 1 : 0;
  buffer <<= roll_value;
  buffer |= ms_bit;
}

void BitBuffer::shiftRight(uint_fast16_t shift_value){
  buffer >>= shift_value;
}

void BitBuffer::print(void){
  Serial.println(buffer, BIN);
}

uint64_t BitBuffer::getRaw(void){
  return buffer;
}
