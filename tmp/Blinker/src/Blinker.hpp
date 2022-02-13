#include <Arduino.h>

class Blinker{
  public:
    void blink(void);
};

class FastBlinker : public Blinker {
  public:
    void blink(void);
    void fastBlink(void);
};

//Blinker my_blinker1 = Blinker();
//FastBlinker my_blinker2 = FastBlinker();

//That one invoke Blinker::Blink()
//my_blinker1.blink();

//That one won't run becouse Blinker::fastBlink() do not exist
//my_blinker1.fastBlink();

//That one invoke FastBlinker::blink()
//my_blinker2.blink();

//That one invoke FastBlinker::fastBlink()
//my_blinker2.fastBlink();

//All previous example where pretty obvious, so let's move to next case:
//FastBlinker my_blinker1 = FastBlinker();
//Blinker my_blinker2 = my_blinker1;

//That one invoke FastBlinker::blink()
//my_blinker1.blink();

//That one invoke FastBlinker::fastBlink()
//my_blinker1.fastBlink();

//That one invoke Blinker::blink()
//my_blinker2.blink();

//That one won't run
//my_blinker2.fastBlink();
