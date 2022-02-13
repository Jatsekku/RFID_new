#include "T5577Downlink14.hpp"

void T5577Downlink14::send_start_gap(void){
  rfid_interface.rfOffFor(timing.start_gap_tc);
}

void T5577Downlink14::send_reference_pulse(void){
  rfid_interface.rfOnFor(timing.d00_pulse_tc);
  rfid_interface.rfOffFor(timing.write_gap_tc);
}

void T5577Downlink14::send_two_bits(uint_fast8_t bit_pair){
  //TODO(Jacek): Add assert for bits_pair > 3
  rfid_interface.rfOnFor(symbols_timing_array[bit_pair]);
  rfid_interface.rfOffFor(timing.write_gap_tc);
}

void T5577Downlink14::startWithOp(uint_fast8_t op_code){
  //TODO(Jacek): Add assert for op_code > 3
  send_start_gap();
  send_reference_pulse();
  send_two_bits(op_code);
}

void T5577Downlink14::sendBits(uint_fast32_t tx_bits,
                                uint_fast8_t bits_amount){
  //TODO(Jacek): Add assert for bits_amount > 32
  for(uint_fast32_t bit_idx = 0; bit_idx < bits_amount; bit_idx++){
    send_two_bits(tx_bits & (3 << bit_idx));
  }
}
