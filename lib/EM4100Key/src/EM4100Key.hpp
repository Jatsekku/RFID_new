#ifndef _EM4100KEY_HPP
#define _EM4100KEY_HPP

#include <stdint.h>

class EM4100Key{
  private:
    uint64_t data_be;

  public:
    EM4100Key(uint_fast64_t raw_data);
    void print(void);
};

#endif /* _EM4100KEY_HPP */
