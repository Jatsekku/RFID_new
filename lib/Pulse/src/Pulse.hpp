#ifndef _PULSE_HPP
#define _PULSE_HPP

#include <stdint.h>

class Pulse{
  private:
    const uint_fast32_t half_symbol_min_time;
    const uint_fast32_t half_symbol_max_time;
    const uint_fast32_t full_symbol_max_time;
    uint_fast32_t symbol_time;
  protected:
    bool in_range(uint_fast32_t start, uint_fast32_t stop);
  public:
    Pulse(uint_fast32_t min_symbol_time, uint_fast32_t max_symbol_time);
    void loadWidth(uint_fast32_t symbol_time);
    bool isInvalidSymbol(void);
    bool isHalfSymbol(void);
    bool isFullSymbol(void);
};

#endif /* _PULSE_HPP */
