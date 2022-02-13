#include <Arduino.h>
#include <FunctionalInterrupt.h>
#include "PCF7991.hpp"
#include "PCF7991_commands.h"


// ########################### Internal interface ##############################

void PCF7991::interface_init(void){
  pinMode(dout_pin, INPUT);
  pinMode(sclk_pin, OUTPUT);
  pinMode(din_pin, OUTPUT);
}

void PCF7991::start_transmission(void){
  digitalWrite(din_pin, LOW);
  digitalWrite(sclk_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(din_pin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sclk_pin, LOW);
}

void PCF7991::send_bits(uint_fast8_t tx_bits, uint_fast8_t bits_amount){
  for(uint_fast8_t bit_idx = 0; bit_idx < bits_amount; bit_idx++){
    digitalWrite(din_pin, (tx_bits & (0x80 >> bit_idx))? HIGH : LOW);
    digitalWrite(sclk_pin, HIGH);
    delayMicroseconds(5);
    digitalWrite(sclk_pin, LOW);
    delayMicroseconds(5);
  }
}

uint8_t PCF7991::receive_byte(void){
  uint_fast8_t bits_amount = 8;
  uint_fast8_t rx_byte = 0;
  while(bits_amount--){
    digitalWrite(sclk_pin, HIGH);
    delayMicroseconds(5);
    rx_byte |= (digitalRead(dout_pin) << bits_amount);
    digitalWrite(sclk_pin, LOW);
    delayMicroseconds(5);
  }
  return rx_byte;
}

void PCF7991::send_command(uint_fast8_t command, uint_fast8_t bits_amount){
  //TODO(Jacek): Add assert for bits_amount > 8
  start_transmission();
  send_bits(command, bits_amount);
}

uint8_t PCF7991::get_sampling_time(void){
  send_command(PCF7991_GET_SAMPLING_TIME_CMD,
               PCF7991_GET_SAMPLING_TIME_CMD_SIZE);
  return receive_byte();
}

uint8_t PCF7991::get_config_page(uint_fast8_t page){
  //TODO(Jacek): Add assert for page > 3
  send_command(PCF7991_GET_CONFIG_PAGE_CMD | page,
               PCF7991_GET_CONFIG_PAGE_CMD_SIZE);
  return receive_byte();
}

uint8_t PCF7991::read_phase(void){
  send_command(PCF7991_READ_PHASE_CMD,
               PCF7991_READ_PHASE_CMD_SIZE);
  return receive_byte();
}

void PCF7991::read_tag_mode(void){
  send_command(PCF7991_READ_TAG_CMD,
               PCF7991_READ_TAG_CMD_SIZE);
  // enable interrupts ?
}

void PCF7991::write_tag_n_mode(uint_fast8_t n){
  //TODO(Jacek): Add assert for n > 15
  send_command(PCF7991_WRITE_TAG_N_CMD | n,
               PCF7991_WRITE_TAG_N_CMD_SIZE);
}

void PCF7991::write_tag_mode(void){
  send_command(PCF7991_WRITE_TAG_CMD,
               PCF7991_WRITE_TAG_CMD_SIZE);
}

void PCF7991::set_config_page(uint_fast8_t page, uint_fast8_t config){
  //TODO(Jacek): Add assert for page > 3
  //TODO(Jacek): Add assert for config > 15
  send_command(PCF7991_SET_CONFIG_PAGE_CMD | page << 4 | config,
               PCF7991_GET_CONFIG_PAGE_CMD_SIZE);
}

void PCF7991::set_sampling_time(uint_fast8_t sampling_time){
  //Todo(Jacek): Add assert for sampling_time > 63
  send_command(PCF7991_SET_SAMPLING_TIME_CMD | sampling_time,
               PCF7991_SET_SAMPLING_TIME_CMD_SIZE);
}

void PCF7991::defaultInit(void){

  // PD_MODE: 0 -> Idle mode
  // PD: 1 -> Power-down mode,
  // HYSTERESIS: 0 -> Hysteresis OFF
  // TXDIS: 1 -> antenna driver inactive
  set_config_page(1, 0b00000101);

  // DISLP1: 0 -> low pass on
  // DISSMARTCOMP: 0 -> smart comparator on
  // FSEL1: 1, FSEL: 0 -> 8MHz ?????
  set_config_page(3, 0b00000001);

  // GAIN1: 1 -> 31.5,
  // GAIN0: 0 -> 16
  // FILTERL: 1 -> main low pass cutoff frequency 6khz
  // FILTERH: 1 -> main high pass cutoff frequency 160 Hz
  set_config_page(0, 0b00001011);

  // PD_MODE: 0 -> active device
  // PD: 0 -> n/a because PD_MODE: 0,
  // HYSTERESIS: 0 -> Hysteresis OFF
  // TXDIS: 0 -> antenna driver active
  set_config_page(1, 0b00000000);

  delay(75);
  uint8_t phase = read_phase();
  Serial.println(phase);
  set_sampling_time(41);

  // THRSET: 1 -> threshold generator is disabled
  // ACQAMP: 0 -> n/a because PD_MODE: 0,
  // FREEZE1: 0, FREEZE0: 1 -> main low pass is frozen and main high pass is initialized to QGND
  set_config_page(2, 0b00001001);

  // THRSET: 1 -> threshold generator is disabled
  // ACQAMP: 0 -> n/a because PD_MODE: 0,
  // FREEZE1: 0, FREEZE0: 0 -> normal operation according to configuration page 0
  set_config_page(2, 0b00001000);

  //delay(1);

  // THRSET: 0 -> ?
  // ACQAMP: 0 -> n/a because PD_MODE: 0,
  // FREEZE1: 0, FREEZE0: 0 -> normal operation according to configuration page 0
  set_config_page(2, 0b00000000);
  //read_tag_mode();
  write_tag_n_mode(0);
}

// ########################### External interface ##############################

PCF7991::PCF7991(uint_fast8_t sclk_pin,
                 uint_fast8_t din_pin,
                 uint_fast8_t dout_pin)
  : sclk_pin(sclk_pin), din_pin(din_pin), dout_pin(dout_pin){};

void PCF7991::begin(void){
  interface_init();
  attachInterrupt(digitalPinToInterrupt(dout_pin),
                  rx_callback,
                  CHANGE);
}

void PCF7991::registerRxCallback(rx_callback_t rx_callback){
  this->rx_callback = rx_callback;
}

bool PCF7991::selfTest(void){
  for(uint8_t page = 0; page < 4; page++){
    Serial.print("Page: ");
    Serial.println(page);
    for(uint8_t i = 0; i < 16; i++){
      set_config_page(page, i);
      Serial.print("WR: ");
      Serial.print(i);
      Serial.print(" RD: ");
      Serial.println(get_config_page(page) & 0x0F);
    }
  }
 return false;
}

void PCF7991::rfOff(void){
  digitalWrite(din_pin, HIGH);
}

void PCF7991::rfOn(void){
  digitalWrite(din_pin, LOW);
}

void PCF7991::rfOffFor(uint_fast32_t time_tc){
  rfOff();
  delayMicroseconds(time_tc * 8);
}

void PCF7991::rfOnFor(uint_fast32_t time_tc){
  rfOn();
  delayMicroseconds(time_tc * 8);
}

void PCF7991::adaptSamplingTime(uint_fast8_t rf_offset){
  uint_fast8_t phase = read_phase();
  Serial.print("Phase: ");
  Serial.println(phase);
  Serial.print("Sampling: ");
  Serial.println(get_sampling_time());
  uint_fast8_t new_sampling = (2*phase + rf_offset) & 0x63;
  set_sampling_time(new_sampling);
  Serial.print("New sampling: ");
  Serial.println(get_sampling_time());
}
