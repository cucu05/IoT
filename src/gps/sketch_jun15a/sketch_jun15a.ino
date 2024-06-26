#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define RXP 5
#define TXP 18
HardwareSerial neogps(2);

TinyGPSPlus gps;

//MQTT
const char* ssid = "Redmi Note 9S"; //da vedere
const char* password = "casa1234"; //da vedere

//broker conf MQTT
const char* topic = "GpsInfo/P1";
const char* mqtt_server = "192.168.62.173"; //da vedere
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}

void reconnect() {
  Serial.print("Attempting MQTT connection...");
  while (!client.connected()) {
    if (client.connect("esp32")) {
      Serial.println("");
      Serial.println("connected to broker.");
      // Subscribe
      client.subscribe(topic);
      Serial.print("Subscribe to the topic: ");
      Serial.println(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void  setup(){
  Serial.begin(115200);
  neogps.begin(9600, SERIAL_8N1, RXP, TXP);
  //Wifi connection
  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("ESP IP address: ");
  Serial.println(WiFi.localIP());
  //mqtt connection
  Serial.println("");
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  long lastMsg = 0;
  char msg[50];
  int value = 0;

  if(!client.connected()) {
    reconnect();
  }
}

void loop(){
  //For Json
  StaticJsonBuffer<300> JSONbuffer;
  JsonObject& JSONencoder = JSONbuffer.createObject();
  //data
  boolean newData = false;

  for(unsigned long start = millis(); millis() - start <1000;){
    while(neogps.available()){
      if(gps.encode(neogps.read())){
        newData = true;
      }
    }
  }

  if(newData == true){
    newData = false;
    //Serial.println(gps.satellites.value());
/*     Serial.println("Current position: " + String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6));
    Serial.println("Distance: " + String(gps.distanceBetween(gps.location.lat(), gps.location.lng(), 0, 0)));
    Serial.println("Altitude: " + String(gps.altitude.meters()));
    Serial.println("Failed Checksum: " + String(gps.failedChecksum())); */

/*     String lat = String(gps.location.lat(), 6);
    String lon = String(gps.location.lng(), 6);
    Serial.println(lat); */
    //Formatt Json
   JSONencoder["name"] = "Position";
   JSONencoder["icon"] = "locate";
   JSONencoder["iconColor"] = "#FF0000";
   JSONencoder["lat"] = String(gps.location.lat(), 6);
   JSONencoder["lon"] = String(gps.location.lng(), 6);
   JsonObject& command = JSONencoder.createNestedObject("command");
   command["lat"] = String(gps.location.lat(), 6);
   command["lon"] = String(gps.location.lng(), 6);
    //JSON to MQTT
   char JSONmessageBuffer[200];
   JSONencoder.printTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));

   Serial.println(JSONmessageBuffer);
 
   if (client.publish(topic, JSONmessageBuffer) == true) {
     Serial.println("Success sending message");
   } else {
     Serial.println("Error sending message");
    }
 }

  
client.loop();

}