#include "sensor.cpp"
#include "light.cpp"
#include "blinds.cpp"
#include "mqtt.cpp"

Sensor sensor;
Light light;
Blinds blinds;
MQTT mqtt;

void setup() {
  Serial.begin(9600);
  sensor.connect();
  light.connect();
  blinds.connect();
  //mqtt.connect();
  //mqtt.onMessage(onMqttMessage);
}

void loop() {

  //mqtt.poll();

  int profile = 3;

  switch(profile) {
  case 0:
    automatic();
    break;
  case 1:
    lights_on_blinds_closed();
    break;
  case 2:
    lights_off_blinds_open();
    break;
  case 3:
    disco();
    break;
  default:
    idle();
}

  delay(100);
}

/////////////////////////////////////////////////////////////////////////////////////////////

void automatic() {
  int value = sensor.read();

  Serial.print("Sensor value: ");
  Serial.println(value);

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
}

void lights_on_blinds_closed() {
    blinds.close(100);
    light.set(1, 100);
    light.set(2, 100);
}

void lights_off_blinds_open() {
    blinds.close(0);
    light.set(1, 0);
    light.set(2, 0);
}

void disco() {
    blinds.close(100);
    light.set(1, 101);
    light.set(2, 101);
}

void idle() {
    blinds.close(0);
    light.set(1, 5);
    light.set(2, 5);
}

void onMqttMessage(int messageSize) {
  Serial.println("Received a message with topic '");
  Serial.print(mqtt.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  while (mqtt.available()) {
    Serial.print((char)mqtt.read());
  }
  
  Serial.println();
  Serial.println();
}
