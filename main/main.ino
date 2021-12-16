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
  mqtt.connect();
  mqtt.onMessage(onMqttMessage);
}

void loop() {

  mqtt.poll();

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
