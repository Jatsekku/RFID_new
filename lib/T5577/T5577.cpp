#include "Arduino.h"

#include "T5577.hpp"

T5577::T5577(RFIDInterface& rfid_interface)
  : rfid_interface(rfid_interface){};

void T5577::setCurrentDownlink(T5577Downlink* current_downlink){
  this->current_downlink = current_downlink;
}

void T5577::sendStandardWriteCmd(uint_fast8_t page,
                                 bool lock_bit,
                                 uint_fast32_t data,
                                 uint_fast8_t addr){
  //TODO(Jacek): Add asserts
  current_downlink->startWithOp(page);
  current_downlink->sendBits(lock_bit, 1);
  current_downlink->sendBits(data, 32);
  current_downlink->sendBits(addr, 3);
  constexpr uint_fast16_t programming_gap_tc = programming_gap_ms * 125;
  rfid_interface.rfOnFor(programming_gap_tc);
}

void T5577::sendProtectedWriteCmd(uint_fast8_t page,
                                  bool lock_bit,
                                  uint_fast32_t data,
                                  uint_fast8_t addr,
                                  uint_fast32_t password){
  current_downlink->startWithOp(page);
  current_downlink->sendBits(lock_bit, 1);
  current_downlink->sendBits(data, 32);
  current_downlink->sendBits(addr, 3);
}

void T5577::sendAORCmd(uint_fast32_t password){

}

void T5577::sendDirectAccesCmd(uint_fast8_t addr, uint32_t password){

}

void T5577::sendDirectAccesCmd(uint_fast8_t addr){

}

void T5577::sendPageRegualrReadCmd(void){

}

void T5577::sendResetCmd(void){

}
