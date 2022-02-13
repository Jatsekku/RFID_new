#ifndef _PCF7991_HPP
#define _PCF7991_HPP

#include <stdint.h>
#include <functional>

#include "RFIDInterface.hpp"

class PCF7991 : public RFIDInterface{
  using rx_callback_t = std::function<void(void)>;

  private:
    const uint8_t sclk_pin;
    const uint8_t din_pin;
    const uint8_t dout_pin;
    rx_callback_t rx_callback;

  protected:
    void interface_init(void);
    void start_transmission(void);
    void send_bits(uint_fast8_t tx_bits, uint_fast8_t bits_amount = 8);
    uint8_t receive_byte(void);
    void send_command(uint_fast8_t command, uint_fast8_t bits_amount);
    //void send_data(uint_fast8_t* data, uint_fast8_t da)
    uint8_t get_sampling_time(void);
    uint8_t get_config_page(uint_fast8_t page);
    uint8_t read_phase(void);


    void write_tag_mode(void);
    void set_config_page(uint_fast8_t page, uint_fast8_t config);
    void set_sampling_time(uint_fast8_t sampling_time);
    void default_init(void);

  public:
    void read_tag_mode(void);
    void write_tag_n_mode(uint_fast8_t n);
    PCF7991(uint_fast8_t sclk_pin, uint_fast8_t din_pin, uint_fast8_t dout_pin);
    void begin();
    void defaultInit(void);
    void registerRxCallback(rx_callback_t rx_callback);
    bool selfTest(void);
    void adaptSamplingTime(uint_fast8_t rf_offset);
    void rfOn(void);
    void rfOff(void);
    void rfOnFor(uint_fast32_t time_tc);
    void rfOffFor(uint_fast32_t time_tc);
};

#endif /* _PCF7991_HPP */
