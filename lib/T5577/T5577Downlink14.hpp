#ifndef _T5577DOWNLINK14_HPP
#define _T5577DOWNLINK14_HPP

#include <stdint.h>
#include "T5577Downlink.hpp"

struct T5577Downlink14Timing{
  uint_fast8_t start_gap_tc;
  uint_fast8_t write_gap_tc;
  uint_fast8_t d00_pulse_tc;
  uint_fast8_t d01_pulse_tc;
  uint_fast8_t d10_pulse_tc;
  uint_fast8_t d11_pulse_tc;
  uint_fast16_t programming_gap_tc;
};

class T5577Downlink14 : public T5577Downlink{
  private:
    static constexpr T5577Downlink14Timing timing = {
      .start_gap_tc = 15,
      .write_gap_tc = 10,
      .d00_pulse_tc = 30,
      .d01_pulse_tc = (30 + 16),
      .d10_pulse_tc = (30 + 32),
      .d11_pulse_tc = (30 + 48),
      .programming_gap_tc = 750,
    };

    const uint_fast8_t symbols_timing_array[4] = {
      [0] = timing.d00_pulse_tc,
      [1] = timing.d01_pulse_tc,
      [2] = timing.d10_pulse_tc,
      [3] = timing.d11_pulse_tc,
    };

    inline void send_start_gap(void);
    inline void send_reference_pulse(void);
    inline void send_two_bits(uint_fast8_t bit_pair);

  public:
    void startWithOp(uint_fast8_t op_code);
    void sendBits(uint_fast32_t tx_bits, uint_fast8_t bits_amount);
};

#endif /* _T5577DOWNLINK14_HPP */
