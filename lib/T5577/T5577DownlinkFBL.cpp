#include "T5577DownlinkFBL.hpp"
#include "Arduino.h"

T5577DownlinkFBL::T5577DownlinkFBL(RFIDInterface& rfid_interface)
  : T5577Downlink(rfid_interface) {};

void T5577DownlinkFBL::send_start_gap(void){
  rfid_interface.rfOffFor(timing.start_gap_tc);
}

void T5577DownlinkFBL::send_bit(bool bit_value){
  //Jacek(TODO): Think about assertion ?
  rfid_interface.rfOnFor(symbols_timing_array[bit_value]);
  rfid_interface.rfOffFor(timing.write_gap_tc);
}

void T5577DownlinkFBL::startWithOp(uint_fast8_t op_code){
  //TODO(Jacek): Add assert for op_code > 3
  send_start_gap();
  send_bit(op_code & 0x01);
  //Warning(Jacek) check it out ?
  send_bit((op_code & 0x02));
}

void T5577DownlinkFBL::sendBits(uint_fast32_t tx_bits,
                                uint_fast8_t bits_amount){
  //TODO(Jacek): Add assert for bits_amount > 32
  while(bits_amount--){
    send_bit(tx_bits & (1 << bits_amount));
  }
}
