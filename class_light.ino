#include <Wire.h>

class Light {
  public:
    int number;
    
    Light(int n) {
      number = n;
    }

    void set_light(int value) {
      Wire.beginTransmission(number);
      Wire.write(value);
      Wire.endTransmission();
    }
};

void setup()
{
  Wire.begin();
}

// select i2c channel. In our case: 1&2;
Light lamp_1(1);  
Light lamp_2(2);

void loop()
{
  // set brightness in range 0 - 100%;

  // values from 0 to 100: normal light brightness in %;
  // values > 100: animated effects;
  // -------- 101: double color sine wave;
  
  lamp_1.set_light(100);
}
