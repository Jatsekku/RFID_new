#include "Pulse.hpp"

Pulse::Pulse(uint_fast32_t min_time, uint_fast32_t max_time)
  : half_symbol_min_time(min_time),
    half_symbol_max_time((min_time + max_time)/2),
    full_symbol_max_time(max_time){}

bool Pulse::in_range(uint_fast32_t start, uint_fast32_t stop){
    return ((start <= symbol_time) && ( symbol_time < stop));
}

void Pulse::loadWidth(uint_fast32_t symbol_time){
  this->symbol_time = symbol_time;
}

bool Pulse::isInvalidSymbol(void){
  return (!in_range(half_symbol_min_time, full_symbol_max_time));
}

bool Pulse::isHalfSymbol(void){
  return (in_range(half_symbol_min_time, half_symbol_max_time));
}

bool Pulse::isFullSymbol(void){
  return (in_range(half_symbol_max_time, full_symbol_max_time));
}
