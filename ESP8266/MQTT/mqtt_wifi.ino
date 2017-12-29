#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <PubSubClient.h>

ESP8266WiFiMulti wifiMulti;

const char* mqttServer = "192.168.0.61";
const int mqttPort = 12948;
const char* mqttUser = "prabu";
const char* mqttPassword = "redhat";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    delay(10);

    wifiMulti.addAP("Prabhu_wifi", "xxxxxxxxx");
    wifiMulti.addAP("Prabhu_mobile", "xxxxxxxx");

    Serial.println("Connecting Wifi...");
    
    while(wifiMulti.run() != WL_CONNECTED) {
      delay(500);
      Serial.println("Connecting to WiFi..");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    }

    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);

    while (!client.connected()) {
      Serial.println("Connecting to MQTT...");
      if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
        Serial.println("MQTT connected"); 
      }else {
        Serial.print("failed with state ");
        Serial.print(client.state());
        delay(2000);
      }
    }
    client.publish("esp/test", "Hello from ESP8266");
    client.subscribe("esp/test");
}

void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}

void loop() {
    client.loop();
}
