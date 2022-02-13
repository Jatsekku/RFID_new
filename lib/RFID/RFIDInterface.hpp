#ifndef _RFIDINTERFACE_HPP
#define _RFIDINTERFACE_HPP

#include <stdint.h>

class RFIDInterface{
  public:
     virtual void rfOnFor(uint_fast32_t time_tc);
     virtual void rfOffFor(uint_fast32_t time_tc);
};

#endif /* _RFIDINTERFACE */
