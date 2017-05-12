#include "ELM327.h"

ELM327 elm327;
const byte stateHC05pin = 3;
const byte ATpin = 4;
void setup()
{
  Serial.begin(9600);
  elm327.init(38400, stateHC05pin, ATpin);
  Serial.println("wait for connection");
  while (!elm327.isConnectedToBluetooth()) {
    Serial.print('.');
  }

  //elm327.connectingToELM327BT("303A,64,D36B2E");
  Serial.println("setup done");
}

void loop()
{
  if (Serial.available()>0){
    USEFUL::freeMode();
  }
  Serial.println("working");
  delay(1000);
}

