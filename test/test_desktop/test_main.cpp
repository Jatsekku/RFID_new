#include <unity.h>


//################################## Pulse #####################################
extern void test_Pulse_isHalfSymbol(void);
extern void test_Pulse_isFullSymbol(void);
extern void test_Pulse_isInvalidSymbol(void);

//############################### EM4100Utils ##################################
extern void test_EM4100Utils_calculateNybbleParity(void);
extern void test_EM4100Utils_alignHeader(void);

//############################### TEST RUNNER ##################################
int main(int argc, char** argv){
  UNITY_BEGIN();

  //RUN_TEST(test_Pulse_isHalfSymbol);
  //RUN_TEST(test_Pulse_isFullSymbol);
  //RUN_TEST(test_Pulse_isInvalidSymbol);

  RUN_TEST(test_EM4100Utils_calculateNybbleParity);
  RUN_TEST(test_EM4100Utils_alignHeader);

  UNITY_END();
}
