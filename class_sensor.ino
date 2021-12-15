#include <Arduino.h>
#include <hp_BH1750.h>

class Sensor: public hp_BH1750 {
  public:

    void connect() {
      begin(35);      
    }

    float read() {
      start();
      return getLux();
    }
};

Sensor sensor;

void setup()
{
  Serial.begin(9600);
  sensor.connect();
}

void loop()
{
  // sensor.read() return the value in range 0 - 100,000 lux. However normal home light brightness is about 0-300 lux.
  Serial.println(sensor.read());        
}
