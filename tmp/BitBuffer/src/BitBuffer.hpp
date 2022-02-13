#include <stdint.h>

class BitBuffer{
//  using uint_reg_t = uint_fast8_t;
  private:
    uint64_t buffer;

    static const uint64_t ms_bit_mask = 0x8000000000000000;
    static const uint64_t ls_bit_mask = 0x0000000000000001;

  protected:
  public:
    BitBuffer(void);
    BitBuffer(const BitBuffer &original_object);
    void setBit(uint_fast16_t index, bool bit_value);
    bool getBit(uint_fast16_t index);
    void shiftLeft(uint_fast16_t shift_value);
    void rollLeft(uint_fast16_t roll_value);
    void shiftRight(uint_fast16_t shift_value);
    uint64_t getRaw(void);
    void clear(void);
    void print(void);
};
