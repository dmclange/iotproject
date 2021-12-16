#include <Wire.h>

class Light {
  public:
  
    void connect() {
      Wire.begin();
    }

    void set(int light, int value) {
      Wire.beginTransmission(light);
      Wire.write(value);
      Wire.endTransmission();
    }
};
