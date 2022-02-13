#ifndef _T5577DOWNLINKFBL_HPP
#define _T5577DOWNLINKFBL_HPP

#include <stdint.h>
#include "T5577Downlink.hpp"

struct T5577DownlinkFBLTiming{
  uint_fast8_t start_gap_tc;
  uint_fast8_t write_gap_tc;
  uint_fast8_t d0_pulse_tc;
  uint_fast8_t d1_pulse_tc;
  uint_fast8_t programming_gap_ms;
};

class T5577DownlinkFBL : public T5577Downlink{
  private:
    static constexpr T5577DownlinkFBLTiming timing = {
      .start_gap_tc = 15,
      .write_gap_tc = 10,
      .d0_pulse_tc = 24,
      .d1_pulse_tc = 56,
    };

    const uint_fast8_t symbols_timing_array[2] = {
      [0] = timing.d0_pulse_tc,
      [1] = timing.d1_pulse_tc,
    };

    inline void send_start_gap(void);
    inline void send_bit(bool bit_value);

  public:
    T5577DownlinkFBL(RFIDInterface& rfid_interface);
    void startWithOp(uint_fast8_t op_code);
    void sendBits(uint_fast32_t tx_bits, uint_fast8_t bits_amount);
};

#endif /* _T5577DOWNLINKFBL_HPP */
