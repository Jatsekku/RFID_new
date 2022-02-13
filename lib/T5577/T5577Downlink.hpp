#ifndef _T5577DOWNLINK_HPP
#define _T5577DOWNLINK_HPP

#include <stdint.h>
#include "RFIDInterface.hpp"

class T5577Downlink{
  protected:
    RFIDInterface& rfid_interface;
  public:
    T5577Downlink(RFIDInterface& rfid_interface)
      : rfid_interface(rfid_interface) {};
    virtual void startWithOp(uint_fast8_t op_code);
    virtual void sendBits(uint_fast32_t tx_bits, uint_fast8_t bits_amount);
};

#endif /* _T5577DOWNLINK_HPP */
