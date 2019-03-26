#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <EEPROM.h>

const char *ssid =  "Hathway";   // cannot be longer than 32 characters!
const char *pass =  "Water@World99";   //
const char *mqtt_server = "m16.cloudmqtt.com";
const int mqtt_port = 12893;
const char *mqtt_user = "xxxxxxxx";
const char *mqtt_pass = "XXXXXXXXXXXX";
const char *device_id = "esp8266";

int pinw = D1;

WiFiClient espClient;
PubSubClient client(espClient);

const byte ledPin5 = 16;
char message_buff[100];

void callback(char *led_control, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(led_control);
  Serial.println("] ");
  int i;
  for (i = 0; i < length; i++)
  {
    message_buff[i] = payload[i];
  }
  message_buff[i] = '\0';

  String msgString = String(message_buff);
  Serial.println(msgString);
  if (strcmp(led_control, "esp8266/led_control") == 0)
  { 
    if (msgString == "0")
    {
      digitalWrite(pinw, LOW); // PIN HIGH will switch OFF the relay
      digitalWrite(ledPin5, HIGH);
    }
    if (msgString == "1")
    {
      digitalWrite(pinw, HIGH); // PIN LOW will switch ON the relay
      digitalWrite(ledPin5, LOW);
    }
  }
}

void reconnect()
{
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(device_id, mqtt_user, mqtt_pass))
    { 
    Serial.println("connected");
    client.subscribe("esp8266/led_control"); // write your unique ID here
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  pinMode(ledPin5, OUTPUT);
  
  delay(10);
  Serial.println("\n");

  WiFi.begin(ssid,pass);
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(".");

  int i = 0;
  while( WiFi.status() != WL_CONNECTED ) {
    Serial.println(WiFi.macAddress());
    delay(1000);
    Serial.println(++i); Serial.println(" ");
  }

  Serial.println("\n");
  Serial.println("Connection Established..");
  Serial.print("IP Address \t");
  Serial.println(WiFi.localIP());
  pinMode(pinw, OUTPUT);
}

void loop()
{
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}
