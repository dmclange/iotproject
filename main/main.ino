#include "sensor.cpp"
#include "light.cpp"
#include "blinds.cpp"

Sensor sensor;
Light light;
Blinds blinds;

void setup() {
  Serial.begin(9600);
  sensor.connect();
  light.connect();
  blinds.connect();
}

void loop() {

  int value = sensor.read();

  if (value < 50) {
    blinds.close(100);
    light.set(1, 100);
    light.set(2, 100);
  }
  else if (value < 200) {
    blinds.close(50);
    light.set(1, 10);
    light.set(2, 10);
  }
  else if (value > 200) {
    blinds.close(0);
    light.set(1, 0);
    light.set(2, 0);
  }

  delay(100);
}
