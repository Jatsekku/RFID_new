#include <unity.h>
#include <iostream>
#include <limits>
#include <Pulse.hpp> // Module under test


const uint32_t min_time = 200;
const uint32_t max_time = 600;

const uint32_t half_symbol_min_time = min_time;
const uint32_t half_symbol_max_time = (min_time + max_time)/2;
const uint32_t full_symbol_max_time = max_time;

const uint32_t u32_max = std::numeric_limits<uint32_t>::max();

// TODO(Jacek): Consider last case: u32_max
Pulse pulse(min_time, max_time);

//########################### Pulse.isHalfSymbol() #############################
void test_Pulse_isHalfSymbol(void){

//------------------------ <0; half_symbol_min_time) ---------------------------
  #if DBG_LVL > 0
    std::cout << "Pulse.isHalfSymbol() Test @range: "
              << "<"
              << 0 << ";" << (half_symbol_min_time - 1)
              << ">"
              << std::endl;
  #endif

  for(uint_fast32_t symbol_time = 0;
      symbol_time < half_symbol_min_time;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isHalfSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isHalfSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(false, result);
  }

//--------------- <half_symbol_min_time; half_symbol_max_time) -----------------
  #if DBG_LVL > 0
  std::cout << "Pulse.isHalfSymbol() Test @range: "
            << "<"
            << half_symbol_min_time << ";" << (half_symbol_max_time - 1)
            << ">"
            << std::endl;
  #endif

  for(uint_fast32_t symbol_time = half_symbol_min_time;
      symbol_time < half_symbol_max_time;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isHalfSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isHalfSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(true, result);
      }

//--------------------- <half_symbol_max_time; u32_max) ------------------------
  #if DBG_LVL > 0
  std::cout << "Pulse.isHalfSymbol() Test @range: "
            << "<"
            << half_symbol_max_time << ";" << (u32_max - 1)
            << ">"
            << std::endl;
  #endif

  for(uint_fast32_t symbol_time = half_symbol_max_time;
      symbol_time < u32_max;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isHalfSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isHalfSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(false, result);
      }
}

//########################### Pulse.isFullSymbol() #############################
void test_Pulse_isFullSymbol(void){
//------------------------ <0; half_symbol_max_time) ---------------------------
  #if DBG_LVL > 0
    std::cout << "Pulse.isFullSymbol() Test @range: "
              << "<"
              << 0 << ";" << (half_symbol_max_time - 1)
              << ">"
              << std::endl;
  #endif

  for(uint_fast32_t symbol_time = 0;
      symbol_time < half_symbol_max_time;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isFullSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isFullSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(false, result);
  }

//--------------- <half_symbol_max_time; full_symbol_max_time) -----------------
  #if DBG_LVL > 0
  std::cout << "Pulse.isFullSymbol() Test @range: "
            << "<"
            << half_symbol_max_time << ";" << (full_symbol_max_time  - 1)
            << ">"
            << std::endl;
  #endif

  for(uint_fast32_t symbol_time = half_symbol_max_time;
      symbol_time < full_symbol_max_time ;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isFullSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isFullSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(true, result);
      }

//--------------------- <full_symbol_max_time; u32_max) ------------------------
  #if DBG_LVL > 0
  std::cout << "Pulse.isFullSymbol() Test @range: "
            << "<"
            << full_symbol_max_time << ";" << (u32_max - 1)
            << ">"
            << std::endl;
  #endif

  for(uint_fast32_t symbol_time = full_symbol_max_time;
      symbol_time < u32_max;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isFullSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isFullSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(false, result);
      }
}

//######################### Pulse.isInvalidSymbol() ############################
void test_Pulse_isInvalidSymbol(void){

//------------------------ <0; half_symbol_min_time) ---------------------------
  #if DBG_LVL > 0
    std::cout << "Pulse.isInvalidSymbol() Test @range: "
              << "<"
              << 0 << ";" << (half_symbol_min_time - 1)
              << ">"
              << std::endl;
  #endif

  for(uint_fast32_t symbol_time = 0;
      symbol_time < half_symbol_min_time;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isInvalidSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isInvalidSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(true, result);
  }

//--------------- <half_symbol_min_time; full_symbol_max_time) -----------------
  #if DBG_LVL > 0
  std::cout << "Pulse.isInvalidSymbol() Test @range: "
            << "<"
            << half_symbol_min_time << ";" << (full_symbol_max_time  - 1)
            << ">"
            << std::endl;
  #endif

  for(uint_fast32_t symbol_time = half_symbol_min_time;
      symbol_time < full_symbol_max_time;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isInvalidSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isInvalidSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(false, result);
      }

//--------------------- <full_symbol_max_time; u32_max) ------------------------
  #if DBG_LVL > 0
  std::cout << "Pulse.isInvalidSymbol() Test @range: "
            << "<"
            << full_symbol_max_time << ";" << (u32_max - 1)
            << ">"
            << std::endl;
  #endif

  for(uint_fast32_t symbol_time = full_symbol_max_time;
      symbol_time < u32_max;
      symbol_time++){
        pulse.loadWidth(symbol_time);
        bool result = pulse.isInvalidSymbol();
        #if DBG_LVL > 1
          std::cout << "Pulse.isInvalidSymbol(" << symbol_time << ")"
          << "->" << result << std::endl;
        #endif
        TEST_ASSERT_EQUAL(true, result);
      }
}
