#ifndef _EM4100_HPP
#define _EM4100_HPP

#include <stdint.h>
#include <functional>

#include "Pulse.hpp"

class T5577{
  private:
    Pulse pulse;
    uint8_t buffer[300];

  public:
    T5577(uint_fast32_t min_time, uint_fast32_t max_time);
    void rxEdgeCallback(void);
};

#endif /* _EM4100_HPP */
