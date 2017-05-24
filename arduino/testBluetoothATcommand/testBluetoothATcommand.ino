#include <SoftwareSerial.h>
SoftwareSerial gps(D2,D3);

void setup() {
  Serial.begin(9600);
  gps.begin(9600);
  delay(1000);
  Serial.println("done");
}

void loop() {
 if (Serial.available()){
  Serial.print(".");
  gps.write(Serial.read());
 }

if (gps.available()){
  Serial.write(gps.read());
 }
 delay(1);
}
