#include <unity.h>
#include <iostream>
#include <bitset>
#include <random>

#include <EM4100Utils.hpp>


//################################# Helpers ####################################
std::random_device rd;
std::mt19937_64 e2(rd());
std::uniform_int_distribution<long long int>
dist(0, std::llround(std::pow(2,64)));

uint_fast64_t generate_valid_header(uint_fast8_t offset, uint_fast64_t noise){
  offset = offset % 64;
  uint_fast64_t valid_header = 0xFF80000000000000;
  return (valid_header >> offset) | (valid_header << (64 - offset)) | noise;
}

uint_fast64_t generate_invalid_header(uint_fast8_t offset,
                                      uint_fast64_t noise,
                                      uint_fast8_t ones_count){
  offset = offset % 64;
  uint_fast64_t valid_header = (uint_fast64_t)(std::pow(2,ones_count) - 1);
  return (valid_header >> offset) | (valid_header << (64 - offset)) | noise;
}


//################### EM4100Utils::calculateNybbleParity() #####################
void test_EM4100Utils_calculateNybbleParity(void){
  /* |-----------------------|
     |  BIN   | DEC | result |
     | 0b0000 |  0  |   0    |
     | 0b0001 |  1  |   1    |
     | 0b0010 |  2  |   1    |
     | 0b0011 |  3  |   0    |
     |-----------------------|
     | 0b0100 |  4  |   1    |
     | 0b0101 |  5  |   0    |
     | 0b0110 |  6  |   0    |
     | 0b0111 |  7  |   1    |
     |-----------------------|
     | 0b1000 |  8  |   1    |
     | 0b1001 |  9  |   0    |
     | 0b1010 |  10 |   0    |
     | 0b1011 |  11 |   1    |
     |-----------------------|
     | 0b1100 |  12 |   0    |
     | 0b1101 |  13 |   1    |
     | 0b1110 |  14 |   1    |
     | 0b1111 |  16 |   0    |
     |-----------------------|
  */

  #if DBG_LVL > 0
    std::cout << "EM4100::calculateNybbleParity() Test @range: "
              << "<"
              << 0 << ";" << 15
              << ">"
              << std::endl;
  #endif

  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(0));
  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(1));
  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(2));
  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(3));

  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(4));
  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(5));
  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(6));
  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(7));

  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(8));
  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(9));
  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(10));
  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(11));

  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(12));
  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(13));
  TEST_ASSERT_EQUAL(true,  EM4100Utils::calculateNybbleParity(14));
  TEST_ASSERT_EQUAL(false, EM4100Utils::calculateNybbleParity(15));
}

//################### EM4100Utils::calculateNybbleParity() #####################
void test_EM4100Utils_alignHeader(void){

//---------------------------- Pure valid header -------------------------------
  #if DBG_LVL > 0
    std::cout << "EM4100::alignHeader() Test: @Pure valid header"
              << std::endl;
  #endif

  // Pure header -> true
  for(uint_fast8_t offset = 0; offset <= 64; offset++){
    uint64_t buffer = generate_valid_header(offset, 0);
    TEST_ASSERT_EQUAL(true, EM4100Utils::alignHeader(buffer));
    TEST_ASSERT_EQUAL_UINT64(0xFF80000000000000, buffer);
  }

//------------------------ Valid header + rand noise ---------------------------
  #if DBG_LVL > 0
    std::cout << "EM4100::alignHeader() Test: @Valid header + rand noise"
              << std::endl;
  #endif
  // Valid header + some noise -> true
  for(uint_fast64_t steps = 0; steps < 100000; steps++){
    for(uint_fast8_t offset = 0; offset <= 64; offset++){
      uint64_t buffer = generate_valid_header(offset, dist(e2));
      TEST_ASSERT_EQUAL(true, EM4100Utils::alignHeader(buffer));
      TEST_ASSERT_EQUAL_UINT64(0xFF80000000000000, buffer & 0xFF80000000000000);
    }
  }

//--------------------------- Pure invalid header ------------------------------
  #if DBG_LVL > 0
    std::cout << "EM4100::alignHeader() Test: @Pure invalid header"
              << std::endl;
  #endif
  // Pure invalid header -> false
  for(uint_fast8_t ones_counter = 0; ones_counter < 9; ones_counter ++){
    for(uint_fast8_t offset = 0; offset <= 64; offset++){
      uint64_t buffer = generate_invalid_header(offset, 0, ones_counter);
      TEST_ASSERT_EQUAL(false, EM4100Utils::alignHeader(buffer));
    }
  }
}

//################### EM4100Utils::checkHorizontalParity() #####################
void test_EM4100Utils_checkHorizontalParity(void){

}

//#################### EM4100Utils::checkVerticalParity() ######################
void test_EM4100Utils_checkVerticalParity(void){

}

//############ EM4100Utils::checkHorizontalAndVerticalParity ###################
void test_EM4100Utils_checkHorizontalAndVerticalParity(void){

}
