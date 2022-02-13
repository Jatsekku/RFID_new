#ifndef PCF7991_H_
#define PCF7991_H_

#ifdef __cplusplus
extern "C" {
#endif

extern volatile uint8_t PCF7991_frame_ok;
extern volatile uint64_t PCF7991_RFID_raw_data;

void PCF7991_InterfaceInit(void);
void PCF7991_Init(void);
void PCF7991_SendData(uint8_t tx_bits, uint8_t bits_amount);
uint8_t PCF7991_ReadReg(uint8_t reg_addr);
void PCF7991_EnterReadTagMode(void);
void PCF7991_SetOscilatorFrequency(uint8_t crystal);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* PCF7991_CONFIG_H_ */
