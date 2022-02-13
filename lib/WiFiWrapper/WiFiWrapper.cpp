#include "WiFiWrapper.hpp"

bool WiFiWrapper::enableAP(void){
  return WiFi.softAP("RFID_devel", "rfid_password", 1, 1);
}
