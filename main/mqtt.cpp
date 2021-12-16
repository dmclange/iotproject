#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>

class MQTT: public MqttClient {
  public:

    WiFiClient wifiClient;

    MQTT():MqttClient(wifiClient){}

    void connect() {
      const char broker[] = "test.mosquitto.org";
      int        port     =  1883;
      const char topic1[] = "building/floorone";
      const char topic2[] = "building/floortwo";
      
      WiFi.begin("SSID", "PASS");

      Serial.println();
      Serial.println("Connecting...");
    
      while (WiFi.status() != WL_CONNECTED) {
        yield();
      }
      
      Serial.print("Connected to: ");
      Serial.println(WiFi.localIP());
    
      Serial.print("Attempting to connect to the MQTT broker: ");
      Serial.println(broker);
    
      if (!MqttClient::connect(broker, port)) {
        Serial.print("MQTT connection failed! Error code = ");
        Serial.println(connectError());
        return;
      }
    
      Serial.println("You're connected to the MQTT broker!");
    
      Serial.print("Subscribing to topic: ");
      Serial.println();
    
      subscribe(topic1);
      subscribe(topic2);
    
      Serial.print("Topic: ");
      Serial.println(topic1);
      Serial.print("Topic: ");
      Serial.println(topic2); 
    }

};
