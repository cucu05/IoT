#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "name";
const char* password = "password";

const char* topic = "sensore/sens1";
const char* mqtt_server = "";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, password); delay(3000);

  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED){
    delay(5); Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to the WiFi network.");
  Serial.print("ESP IP_Address: ");
  Serial.println(WiFi.localIP());

  Serial.println();
  client.setServer(mqtt_server,mqtt_port);
  client.setCallback(callback);
  long lastMsg = 0; char msg[50]; int value = 0;
  if(!client.connected()){
    reconnect();
  }
}

void loop(){
  client.loop();

  if(Serial.available()){
    String str = "";
    str Serial.readString();
    int str_len = str.length() +1;
    char char_array[str_len];
    str.toCharArray(char_array, str_len);
    boolean rc = client.publish(topic,char_array);
  }
}

void reconnect(){
  Serial.print("Attempting MQTT connection...");
  while(!client.connected()){
    Serial.print("...");

    if(client.connect("esp32")){
      Serial.println();
      Serial.println("Connected to the mosquitto Broker.");

      client.subscribe(topic);
      Serial.print("Subscribed to the topic: ");
      Serial.print("topic");
    }else{
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

voif callback(char* topic, byte* message, unsigned int lenght){
  Serial.print("Message arrived on topic: ");
  Serial.println(topic);

  Serial.print("- Message: ");
  String messageTemp;

  for(int i = 0; i<lenght; i++){
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}
