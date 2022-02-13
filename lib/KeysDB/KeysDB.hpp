#include <LittleFS.h>
#include <stdint.h>

#include "EM4100Key.hpp"


class KeysDB{
  private:
    char file_path[32];
    File file_handler;
    uint_fast64_t keys_amount;
  public:
    KeysDB(char file_path[32]);
    void begin(void);
    uint_fast64_t readData(uint_fast64_t offset,
                           uint8_t* buffer,
                           uint_fast64_t size);
    uint_fast64_t writeData(const uint8_t* data,
                            uint_fast64_t size);
    bool isKeyInDB(void);
    void clearKeysDB(void);
};
