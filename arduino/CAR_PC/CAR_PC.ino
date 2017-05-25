#include "ELM327.h"
#include "nextionLCD.h"
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
#define TEMPERATURE_PRECISION 8
// Ilość czujników
#define SENSORS_NUM 2
// Adresy czujników
// arrays to hold device addresses
DeviceAddress insideThermometer = {
  0x28, 0xFF, 0xAC, 0xBC, 0x80, 0x16, 0x05, 0xC2
};
volatile int buf =0;
volatile float voltBuf = 0;
ELM327 elm327;
NEXTION_LCD lcd;
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
  Serial2.begin(9600);

  sensors.begin();
  sensors.setResolution(insideThermometer , TEMPERATURE_PRECISION);

  elm327.init(38400, stateHC05pin, ATpin);
  Serial.println("wait for connection");

  while (!elm327.isConnectedToBluetooth()) {
    Serial.print('.');
  }
  elm327.setupELM327();
  //elm327.connectingToELM327BT("303A,64,D36B2E");
  lcd.displayMainPage();
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
  voltBuf = elm327.getVoltage();
  lcd.displayVoltage( String(voltBuf) );
  Serial.print(voltBuf);
  Serial.println(" VOLT");
  buf = elm327.engineCoolantTemperature();
  lcd.displayCoolant( String(buf));
  Serial.print(buf);
  Serial.println(" temperature");
  buf = elm327.fuelTankLevel();
  lcd.displayFuel(String(buf));
  Serial.print(buf);
  Serial.println(" paliwo");
  Serial.print(elm327.engineLoad());
  Serial.println(" obciazenie silnika");
  double t = temperatureInside();
  Serial.print(t);
  Serial.println(" temperatura");
  lcd.displayTemp(String (t));
  delay(1000);
}

