#ifndef _RELAY_HPP
#define _RELAY_HPP

#include <limits>
#include <stdint.h>

class Relay{
  private:
    static constexpr uint_fast32_t time_limit =
      std::numeric_limits<uint_fast32_t>::max();
    const uint_fast8_t ctrl_pin;
    const bool inverted_logic;
    uint_fast32_t elapsed_time;
    uint_fast32_t delay_time;
    bool timer_active;

  public:
    Relay(uint_fast8_t ctrl_pin, bool inverted_logic = false);
    void on(void);
    void off(void);
    void setOnForMs(uint_fast32_t on_time_ms);
    void updateTimer(uint_fast32_t ms_ticks);
};

#endif /* _RELAY_HPP */
