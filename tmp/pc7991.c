#include <Arduino.h>

#include "pcf7991_commands.h"
#include "pcf7991_config.h"

ICACHE_RAM_ATTR void PCF7991_InterruptHandler(void);

volatile uint8_t PCF7991_frame_ok = 0;
volatile uint64_t PCF7991_RFID_raw_data = 0;

void PCF7991_InterfaceInit(void){
  pinMode(PCF7991_PIN_DOUT, INPUT);
  pinMode(PCF7991_PIN_SCLK, OUTPUT);
  pinMode(PCF7991_PIN_DIN, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(PCF7991_PIN_DOUT), PCF7991_InterruptHandler, CHANGE);
}

void PCF7991_SendStart(void){
  digitalWrite(PCF7991_PIN_DIN, LOW);
  digitalWrite(PCF7991_PIN_SCLK, HIGH);
  delayMicroseconds(20);
  digitalWrite(PCF7991_PIN_DIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(PCF7991_PIN_SCLK, LOW);
}

void PCF7991_SendBits(uint8_t tx_bits, uint8_t bits_amount){
  for(uint8_t bit_idx = 0; bit_idx < bits_amount; bit_idx++){
    digitalWrite(PCF7991_PIN_DIN, (tx_bits & (0x80 >> bit_idx))? HIGH : LOW);
    digitalWrite(PCF7991_PIN_SCLK, HIGH);
    delayMicroseconds(20);
    digitalWrite(PCF7991_PIN_SCLK, LOW);
    delayMicroseconds(20);
  }
}

uint8_t PCF7991_ReceiveByte(void){
  uint8_t bits_amount = 8;
  uint8_t rx_byte = 0;
  while(bits_amount--){
    digitalWrite(PCF7991_PIN_SCLK, HIGH);
    delayMicroseconds(20);
    rx_byte |= (digitalRead(PCF7991_PIN_DOUT) << bits_amount);
    digitalWrite(PCF7991_PIN_SCLK, LOW);
    delayMicroseconds(20);
  }
  return rx_byte;
}

void PCF7991_SendData(uint8_t tx_bits, uint8_t bits_amount){
  PCF7991_SendStart();
  PCF7991_SendBits(tx_bits, bits_amount);
}

uint8_t PCF7991_ReadReg(uint8_t reg_addr){
  PCF7991_SendData(reg_addr, 8);
  return PCF7991_ReceiveByte();
}

///API///

uint8_t PCF7991_GetSamplingTime(void){
  return PCF7991_ReadReg(PCF7991_CMD_GET_SAMPLING_TIME);
}

uint8_t PCF7991_GetConfigPage(uint8_t page){
  page = page & 0x03;
  return PCF7991_ReadReg(PCF7991_CMD_GET_CONFIG_PAGE | page);
}

uint8_t PCF7991_ReadPhase(void){
  return PCF7991_ReadReg(PCF7991_CMD_READ_PHASE);
}

void PCF7991_EnterReadTagMode(void){
  PCF7991_SendData(PCF7991_CMD_READ_TAG, 3);
}

void PCF7991_EnterWriteTagModePWM(void){
  PCF7991_SendData(PCF7991_CMD_WRITE_TAG_N, 3);
}

void PCF7991_EnterWriteTagMode(void){
  PCF7991_SendData(PCF7991_CMD_WRITE_TAG, 3);
}

uint8_t PCF7991_SetConfigPage(uint8_t page, uint8_t config){
  page = (page & 0x03) << 4;
  config = config & 0x0F;
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | page | config, 8);
}

void PCF7991_SetSamplingTime(uint8_t sampling_time){
  PCF7991_SendData((PCF7991_CMD_SET_SAMPLING_TIME | (sampling_time & 0x1F)), 8);
}

void PCF7991_SetOscilatorFrequency(uint8_t crystal){
  uint8_t config = PCF7991_GetConfigPage(3);
  config |= (crystal & 0x03);
  PCF7991_SetConfigPage(3, config);
}

void PCF7991_Init(void)
{
//  PCF7991_SetOscilatorFrequency(2);
//  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 0 | 0b00001011,8); //Wake-up? SetConfigPage0 -> all bits to 0
//  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 1 | 0b00000000,8); //Wake-up? SetConfigPage0 -> all bits to 0
//  delay(1);
//  uint8_t phase = PCF7991_ReadPhase();
//  PCF7991_SetSamplingTime(phase + 2);
//  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 2 | 0b00001001,8); //Wake-up? SetConfigPage0 -> all bits to 0
//  delay(5);
//  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 2 | 0b00001000,8); //Wake-up? SetConfigPage0 -> all bits to 0
//  delay(1);
//  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 2 | 0b00000000,8); //Wake-up? SetConfigPage0 -> all bits to 0

  PCF7991_InterfaceInit();
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 1<<4 | 0b00000101,8);
  delay(75);
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 3<<4 | 0b00000010,8);
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 0<<4 | 0b00001011,8);
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 1<<4 | 0b00000000,8);
  delay(1);
  uint8_t phase = PCF7991_ReadPhase();
  PCF7991_SetSamplingTime(phase + 1);
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 2<<4 | 0b00001001,8);
  delay(5);
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 2<<4 | 0b00001000,8);
  delay(1);
  PCF7991_SendData(PCF7991_CMD_SET_CONFIG_PAGE | 2<<4 | 0b00000000,8);
  PCF7991_EnterReadTagMode();
}

///INTERRUPTS///

ICACHE_RAM_ATTR void PCF7991_InterruptHandler(void){
  static uint8_t edge_counter;
  static uint8_t bit_counter;
  static uint8_t current_bit_value;
  static uint32_t last_interrupt_timestamp;
  static uint64_t bit_buffer, bit_buffer_tmp;

  uint32_t current_interrupt_timestamp = micros();
  uint32_t current_pulse_width = current_interrupt_timestamp - last_interrupt_timestamp;
  last_interrupt_timestamp = current_interrupt_timestamp;

  if(edge_counter == 0){
    bit_counter = 0;
    current_bit_value = 0;
    bit_buffer = 0;
  }

  //Check if pulse is too short OR too long
  if((PCF7991_CONST_MIN_PULSE_WIDTH > current_pulse_width) || (current_pulse_width > 2*PCF7991_CONST_MAX_PULSE_WIDTH)){
    edge_counter = 0;
  }

  //Short pulse
  if((PCF7991_CONST_MIN_PULSE_WIDTH <= current_pulse_width ) && (current_pulse_width <= PCF7991_CONST_MAX_PULSE_WIDTH)){
    if((edge_counter % 2) == 0){
      bit_buffer <<= 1;
      bit_buffer |= (uint64_t)current_bit_value;
      bit_counter++;
    }
    edge_counter++;
  }

  //Long pulse
  if((PCF7991_CONST_MAX_PULSE_WIDTH <= current_pulse_width) && (current_pulse_width <= 2*PCF7991_CONST_MAX_PULSE_WIDTH)){
    current_bit_value ^= 0x01;
    bit_buffer <<= 1;
    bit_buffer |= (uint64_t)current_bit_value;
    bit_counter++;
    edge_counter += 2;
  }

  //The entire bitstream has been read
  if(bit_counter > 64){
      edge_counter = 0;
      if(PCF7991_frame_ok == 0){
        bit_buffer_tmp = bit_buffer;
        if(RFID_UNIQUE_FrameProcessing(&bit_buffer_tmp)){
          PCF7991_RFID_raw_data = bit_buffer_tmp;
          PCF7991_frame_ok = 1;
        }
      }
  }
}
