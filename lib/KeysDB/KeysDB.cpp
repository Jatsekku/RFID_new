#include <LittleFS.h>
#include <Arduino.h>
#include <stdint.h>

#include "KeysDB.hpp"

KeysDB::KeysDB(char file_path[32]){
  memcpy( this->file_path, file_path, strlen(file_path) + 1);
};

void KeysDB::begin(void){
  if(!LittleFS.exists(file_path)){
    Serial.print(file_path);
    Serial.print(" not exist!");
    file_handler = LittleFS.open(file_path, "a+");
    if(file_handler){
      Serial.print(file_path);
      Serial.println(" created!");
      keys_amount = 0;
    }
  }else{
    Serial.print(file_path);
    Serial.print(" exist!");
  }
}

uint_fast64_t KeysDB::writeData(const uint8_t* data,
                                uint_fast64_t size){
  return file_handler.write(data, size);
}

uint_fast64_t KeysDB::readData(uint_fast64_t offset,
                               uint8_t* buffer,
                               uint_fast64_t size){
  file_handler.seek(offset, SeekSet);
  return file_handler.read(buffer, size);
}
