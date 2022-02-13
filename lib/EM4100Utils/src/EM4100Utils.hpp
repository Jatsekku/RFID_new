#ifndef _EM4100UTILS_HPP
#define _EM4100UTILS_HPP

#include <stdint.h>

class EM4100Utils{
  private:
    static constexpr bool parity_table[16] = {
      0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    };
    static constexpr uint_fast64_t header_mask = 0xFF80000000000000;
    static constexpr uint_fast64_t ms_bit_mask = 0x8000000000000000;
    static constexpr uint_fast8_t  ls_bit_mask = 0x0000000000000001;

  public:
    static bool calculateTetradeParity(uint_fast8_t tetrade);
    static bool alignHeader(uint_fast64_t& frame_buffer);
    static bool checkHorizontalParity(uint_fast64_t raw_frame);
    static bool checkVerticalParity(uint_fast64_t raw_frame);
    static bool checkHorizontalAndVerticalParity(uint_fast64_t raw_frame);
    static bool completeProcessing(uint_fast64_t& frame_buffer);
};

#endif /* _EM4100UTILS_HPP */
