#include <Servo.h>

class Blinds: public Servo {
  public:

    void close(int value) {
      if (value <= 100) {
        write((value/100)*35);
      }        
    }
};

Blinds blinds;

void setup() {
  blinds.attach(5);  // for Wemos D1R1 connect signal cable to D1;
}

void loop() {

  // close blinds 0-100%;
  // set value in range 0-100;
  
  blinds.close(100);
  delay(1000);
  blinds.close(0);
  delay(1000);
}
