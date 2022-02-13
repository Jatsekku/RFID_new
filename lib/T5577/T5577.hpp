#ifndef _T5577_HPP
#define _T5577_HPP

/* Refer to Microchip ATA5577C documentation:
 http://ww1.microchip.com/downloads/en/DeviceDoc/ATA5577C
 -Read-Write-LF-RFID-IDIC-100-to-150-kHz-Data-Sheet-DS70005357B.pdf
*/

#include <stdint.h>
#include "T5577Downlink.hpp"
#include "RFIDInterface.hpp"

struct T5577ConfigMappingBasic{
  uint32_t init_delay:1;
  uint32_t _reserved3:2;
  uint32_t sterm_marker:1;
  uint32_t pwd:1;
  uint32_t max_block:3;
  uint32_t aor:1;
  uint32_t psk_cf:2;
  uint32_t modulation:5;
  uint32_t _reserved2:1;
  uint32_t data_bitrate:3;
  uint32_t _reserved1:7;
  uint32_t master_key:4;
  uint32_t lock_bit:1;
};

struct T5577ConfigMappingX{
  uint32_t init_delay:1;
  uint32_t inverse_data:1;
  uint32_t fast_downlink:1;
  uint32_t sstart_marker:1;
  uint32_t pwd:1;
  uint32_t max_block:3;
  uint32_t otp:1;
  uint32_t aor:1;
  uint32_t psk_cf:2;
  uint32_t modulation:5;
  uint32_t x_mode:1;
  uint32_t data_bitrate:6;
  uint32_t _reserved1:4;
  uint32_t master_key:4;
  uint32_t lock_bit:1;
};

struct T5577AFEOption{
  uint32_t _reservedfu:10;
  uint32_t downlink_protocol:2;
  uint32_t demod_delay:2;
  uint32_t write_damping:3;
  uint32_t gap_detection_threshold:2;
  uint32_t clock_detection_threshold:2;
  uint32_t modulation_voltage:2;
  uint32_t clamp_voltage:2;
  uint32_t soft_modulation:3;
  uint32_t option_key:4;
  uint32_t lock_bit:1;
};

class T5577{
  private:
    T5577Downlink* current_downlink;
    RFIDInterface& rfid_interface;
    static constexpr uint_fast8_t programming_gap_ms = 6;
  public:
    T5577(RFIDInterface& rfid_interface);
    void setCurrentDownlink(T5577Downlink* current_downlink);
    void sendStandardWriteCmd(uint_fast8_t page,
                              bool lock_bit,
                              uint_fast32_t data,
                              uint_fast8_t addr);
    void sendProtectedWriteCmd(uint_fast8_t page,
                               bool lock_bit,
                               uint_fast32_t data,
                               uint_fast8_t addr,
                               uint_fast32_t password);
    void sendAORCmd(uint_fast32_t password);
    void sendDirectAccesCmd(uint_fast8_t addr, uint32_t password);
    void sendDirectAccesCmd(uint_fast8_t addr);
    void sendPageRegualrReadCmd(void);
    void sendResetCmd(void);
};

#endif /* _T5577_HPP */
