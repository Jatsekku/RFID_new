#include <Arduino.h>
#include <LittleFS.h>

#include "PCF7991.hpp"
#include "EM4100.hpp"
#include "EM4100Key.hpp"
#include "T5577.hpp"
#include "Relay.hpp"
#include "KeysDB.hpp"
#include "RFIDInterface.hpp"
#include "T5577DownlinkFBL.hpp"
#include "WiFiWrapper.hpp"

PCF7991 rfid_reader(14,13,12);
T5577DownlinkFBL downlink_fbl(rfid_reader);
T5577 rfid_proto(rfid_reader);

EM4100 rfid_protocol(200, 600);
Relay lock(2, true);
KeysDB regular_keys_db("/test.bin");

void print_mem(uint8_t* buffer, uint8_t size){
  for(uint8_t i = 0; i < size; i++){
    Serial.print(buffer[i], HEX);
    Serial.print(" ");
    if(i%10 == 0){
      Serial.print("\n");
    }
  }
}
void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  if(!LittleFS.begin()){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }
  LittleFS.format();

  rfid_proto.setCurrentDownlink(&downlink_fbl);

  // std::function<void()> EM4100_callback = std::bind(&EM4100::rxEdgeCallback, &rfid_protocol);
  // rfid_reader.registerRxCallback(EM4100_callback);

  //rfid_protocol.registerNewKeyCallback(callback_test);

  rfid_reader.begin();
  rfid_reader.defaultInit();



  uint8_t some_keys[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A,
                         0x0B, 0x0C, 0x0D, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15};

  uint8_t buffer[40] = {0};


  regular_keys_db.begin();




//  lock.setOnForMs(5000);

//------------------------------------------------------------------------------

rfid_reader.rfOn();

}




void loop() {
  rfid_reader.rfOn();
  delay(50);
  Serial.println("start");
  //downlink_fbl.startWithOp(0);
  rfid_proto.sendStandardWriteCmd(1, false, 0xABCD, 1);
  rfid_proto.sendStandardWriteCmd(1, false, 0xEF12, 2);
  rfid_reader.rfOn();
  delay(1000);
  Serial.println("done");
  delay(1000);
}
