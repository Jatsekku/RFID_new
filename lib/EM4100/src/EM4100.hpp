#ifndef _EM4100_HPP
#define _EM4100_HPP

#include <stdint.h>
#include <functional>

#include "Pulse.hpp"
#include "EM4100Key.hpp"

class EM4100{
  using new_key_callback_t = std::function<void(EM4100Key)>;
  private:
    Pulse pulse;
    uint_fast64_t buffer;
    new_key_callback_t new_key_callback;

  public:
    EM4100(uint_fast32_t min_time, uint_fast32_t max_time);
    void rxEdgeCallback(void);
    void registerNewKeyCallback(new_key_callback_t new_key_callback);
};

#endif /* _EM4100_HPP */
