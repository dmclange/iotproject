#include <Servo.h>

class Blinds: public Servo {
  public:

    void connect() {
      attach(0);  // connect to pin3
    }

    void close(int value) {
      if (value <= 100) {
          write(value/100.0*45);
        }      
    } 
};
