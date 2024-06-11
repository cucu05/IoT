#include <TinyGPS++.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <PubSubClient.h>

#define RXP 18
#define TXP 19
HardwareSerial neogps(2);

TinyGPSPlus gps;

//MQTT
const char* ssid = "Redmi Note 9S"; //da vedere
const char* password = "casa1234"; //da vedere

//broker conf MQTT
const char* topic = "GpsInfo/P1";
const char* mqtt_server = "192.168.62.173"; //da vedere
const int mqtt_port = 1883;

//button
const int button = 2;
int buttonState = 0;

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
  // Loop until we're reconnected
  Serial.print("Attempting MQTT connection...");
  while (!client.connected()) {
    // Attempt to connect
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
  pinMode(button, INPUT);
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
  boolean newData = false;
  client.loop();
  buttonState = digitalRead(button);

  for(unsigned long start = millis(); millis() - start <1000;){
    while(neogps.available()){
      if(gps.encode(neogps.read())){
        newData = true;
      }
    }
  }

  if(newData == true && buttonState == HIGH){
    digitalWrite(19, LOW);
    newData = false;
    Serial.println(gps.satellites.value());
    Serial.println("Current position: " + String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6));
    Serial.println("Distance: " + String(gps.distanceBetween(gps.location.lat(), gps.location.lng(), 0, 0)));
    Serial.println("Altitude: " + String(gps.altitude.meters()));
    Serial.println("Failed Checksum: " + String(gps.failedChecksum()));
    //MQTT publishing
    String str = "";
    str = String(gps.location.lat(), 6) + " " + String(gps.location.lng(), 6);
    int str_len = str.length() + 1;
    char array[str_len];
    str.toCharArray(array, str_len);
    boolean rc = client.publish(topic, array);
  }
  else if(buttonState == LOW)
  {
    digitalWrite(19, HIGH);
  }
}
