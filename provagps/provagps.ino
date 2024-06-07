#include <TinyGPS++.h>
#include <TinyGPSPlus.h>

#define RXP 18
#define TXP 19
HardwareSerial neogps(2);

TinyGPSPlus gps;

void  setup(){
  Serial.begin(115200);
  neogps.begin(9600, SERIAL_8N1, RXP, TXP);
}

void loop(){
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
    Serial.println(gps.satellites.value());
    Serial.println("Current position: " + String(gps.location.lat(), 6) + ", " + String(gps.location.lng(), 6));
    Serial.println("Distance: " + String(gps.distanceBetween(gps.location.lat(), gps.location.lng(), 0, 0)));
    Serial.println("Altitude: " + String(gps.altitude.meters()));
    Serial.println("Failed Checksum: " + String(gps.failedChecksum()));
  }
}
