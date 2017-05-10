#include "ELM327.h"
ELM327 elm327;
byte stateHC05pin = 3;
byte ATpin = 4;
void setup()
{
  Serial.begin(9600);
  elm327.init(38400, stateHC05pin, ATpin);
  Serial.println("setup done");
}

void loop()
{
  if (Serial.available()) {
    Serial.println("bangla sobie");
   // st = BluetoothRS232.readStringUntil("OK");
    delay(100);
   // Serial.println(st);
  }

if (elm327.isConnectedToBluetooth() == true){
  Serial.println("polaczony do bluetooth");
}

  
}

