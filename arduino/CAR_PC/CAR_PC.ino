#include "ELM327.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
#define TEMPERATURE_PRECISION 12
// Ilość czujników
#define SENSORS_NUM 2
// Adresy czujników
// arrays to hold device addresses
DeviceAddress insideThermometer = {
  0x28, 0x80, 0x3E, 0x64, 0x4, 0x0, 0x0, 0xD2
};

ELM327 elm327;
const byte stateHC05pin = 3;
const byte ATpin = 4;
String bufor;
double temperatureInside() {
  sensors.requestTemperatures(); // Send the command to get temperatures
  return sensors.getTempC(insideThermometer);
}
void setup()
{
  Serial.begin(9600);

  sensors.begin();
  sensors.setResolution(insideThermometer , TEMPERATURE_PRECISION);

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
  if (Serial.available() > 0) {
    while (Serial.available() > 0) {
      bufor += Serial.readString();
    }
    if (bufor[0] == 'f') {
      USEFUL::freeMode();
      bufor = "";
    }
    bufor = "";
  }
  //Serial.println("working");
  Serial.print(elm327.getVoltage());
  Serial.println(" VOLT");
  Serial.print(elm327.engineCoolantTemperature());
  Serial.println(" temperature");
  Serial.print(elm327.fuelTankLevel());
  Serial.println(" paliwo");
  Serial.print(temperatureInside());
  Serial.println(" temperatura");
  delay(100);
}

