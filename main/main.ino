#include "sensor.cpp"
#include "light.cpp"
#include "blinds.cpp"
#include "mqtt.cpp"

Sensor sensor;
Light light;
Blinds blinds;
//MQTT mqtt;

void setup() {
  Serial.begin(9600);
  sensor.connect();
  light.connect();
  blinds.connect();
  //mqtt.connect();
  //mqtt.onMessage(onMqttMessage);

  //pinMode(3, INPUT);  // connect to RX
  //pinMode(5, INPUT);  // connect to D1
}

int profile = 3;

void loop() {

  //mqtt.poll();

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
  case 4:
    all_on();
  case 5:
    all_off();
  }

  delay(1000);
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
  else if (value < 150) {
    blinds.close(50);
    light.set(1, 10);
    light.set(2, 10);
  }
  else if (value > 150) {
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

void all_on() {
    light.set(1, 100);
    light.set(2, 100);
}

void all_off() {
    light.set(1, 0);
    light.set(2, 0);
}

/*void onMqttMessage(int messageSize) {
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
}*/
