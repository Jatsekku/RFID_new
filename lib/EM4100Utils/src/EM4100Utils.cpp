#include "EM4100Utils.hpp"

constexpr bool EM4100Utils::parity_table[16];

inline bool EM4100Utils::calculateTetradeParity(uint_fast8_t tetrade){
  return parity_table[tetrade];
}

bool EM4100Utils::alignHeader(uint_fast64_t& frame_buffer){
  uint_fast8_t ms_bit;

  for(uint_fast8_t bit_idx = 0; bit_idx < 64; bit_idx++){
    if((frame_buffer & header_mask) == header_mask){
      return true;
    }

    // Roll left
    ms_bit = frame_buffer & ms_bit_mask ? 1 : 0;
    frame_buffer <<= 1;
    frame_buffer |= ms_bit;
  }
  return false;
}

bool EM4100Utils::checkHorizontalParity(uint_fast64_t raw_frame){
  bool parity_bit;
  uint_fast8_t tetrade;

  for(uint_fast8_t tetrade_idx = 0; tetrade_idx < 10; tetrade_idx++){
    raw_frame >>= 5;
    parity_bit = raw_frame & ls_bit_mask;
    tetrade = (raw_frame & 0x1E) >> 1;

    if(calculateTetradeParity(tetrade) != parity_bit){
      return false;
    }
  }
  return true;
}

bool EM4100Utils::checkVerticalParity(uint_fast64_t raw_frame){
  uint8_t calculated_parity_bits = 0x00;
  uint_fast8_t read_parity_bits = raw_frame & 0x1E;

  for(uint_fast8_t tetrade_idx = 0; tetrade_idx < 10; tetrade_idx++){
    raw_frame >>= 5;
    calculated_parity_bits ^= raw_frame;
  }

  return ((calculated_parity_bits & 0x1E) == read_parity_bits);
}

bool EM4100Utils::checkHorizontalAndVerticalParity(uint_fast64_t raw_frame){
  bool read_horizontal_parity_bit;
  uint_fast8_t tetrade;

  uint8_t calculated_vertical_parity_bits = 0x00;
  uint_fast8_t read_vertical_parity_bits = raw_frame & 0x1E;

  for(uint8_t tetrade_idx = 0; tetrade_idx < 10; tetrade_idx++){
    raw_frame >>= 5;
    read_horizontal_parity_bit = raw_frame & ls_bit_mask;
    tetrade = (raw_frame & 0x1E) >> 1;
    calculated_vertical_parity_bits ^= raw_frame;

    if(calculateTetradeParity(tetrade) != read_horizontal_parity_bit){
      return false;
    }
  }
  return (calculated_vertical_parity_bits & 0x1E) == read_vertical_parity_bits;
}

bool EM4100Utils::completeProcessing(uint_fast64_t& frame_buffer){
  bool header_valid = alignHeader(frame_buffer);
  if(!header_valid){
    frame_buffer = ~frame_buffer;
    header_valid = alignHeader(frame_buffer);
  }

  if(header_valid){
    return checkHorizontalAndVerticalParity(frame_buffer);
  }

  return false;
}
