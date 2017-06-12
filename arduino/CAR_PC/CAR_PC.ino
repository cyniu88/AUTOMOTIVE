#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ELM327.h"
#include "nextionLCD.h"

#define OLED_RESET 40
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


ELM327 elm327;
NEXTION_LCD lcd;
Adafruit_SSD1306 display( OLED_RESET );

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

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.display();

  sensors.begin();
  sensors.setResolution(insideThermometer , TEMPERATURE_PRECISION);

  elm327.init(38400, stateHC05pin, ATpin);
  Serial.println("wait for connection");

  while (!elm327.isConnectedToBluetooth()) {
    Serial.print('.');
  }
  elm327.elm327WaitForReady();
  elm327.setupELM327();
  elm327.setPcmHeader();
  lcd.displayMainPage();

  displayText("cyniu");
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

  odometer();
  engineLoad();
  brakeUse();
  coolant();
  engineLoad();
  brakeUse();
  fuel();
  engineLoad();
  brakeUse();
  temperatureInsideCar();
  engineLoad();
  brakeUse();
  runtime();
  engineLoad();
  brakeUse();
  engineLoad();
  brakeUse();
  voltage();
  engineLoad();
  brakeUse();
  delay(50);
}

void coolant() {
  String buf = String(elm327.engineCoolantTemperature());
  lcd.displayCoolantBar(buf);
  lcd.displayCoolant( buf);
}
void voltage() {
  String voltBuf = String(elm327.getVoltage());
  //Serial.println (voltBuf);
  lcd.displayVoltage( voltBuf );
}
void fuel() {
  String buf = String (elm327.fuelTankLevel());
  lcd.displayFuelBar(buf);
  lcd.displayFuel(buf);
}
void temperatureInsideCar() {
  double t = temperatureInside();
  String txt = String(t);
  txt.remove(txt.length() - 1, txt.length());
  lcd.displayTemp(txt);
  displayTemperature(txt);
}
void odometer() {
  String odo = String(elm327.odometerCurrent());
  lcd.displayOdometer(odo);
}
void runtime() {
  long time1 = elm327.runTimeEngineStart();
  String str = USEFUL::convertSecToHMstring(time1);
  lcd.displayRuntime(str);
}
void engineLoad() {
  int load = elm327.engineLoad();
  lcd.displayLoad(String(load) + "%");
}
void brakeUse() {
  CAR_BRAKE statusNow = elm327.brakeON();
  static bool parkingBrakeStatus = false;
  static bool brakeStatus = false;

  static unsigned int counter  = 0;
  if ((statusNow == CAR_BRAKE::ON || statusNow == CAR_BRAKE::BOTH_BRAKE) && brakeStatus == false) {
    lcd.displayBrakeStat("BRAKE!");
    counter++;
    lcd.displayBrakeCounter(counter);
    brakeStatus = true;
  }
  else if ((statusNow == CAR_BRAKE::OFF || statusNow == CAR_BRAKE::PARKING_BRAKE) && brakeStatus == true) {
    lcd.displayBrakeStat("---");
    brakeStatus = false;
  }
  else if ((statusNow == CAR_BRAKE::BOTH_BRAKE || statusNow == CAR_BRAKE::PARKING_BRAKE) && parkingBrakeStatus == false) {
    lcd.displayParkingBrake(true);
    parkingBrakeStatus = true;
  }
  else if ((statusNow == CAR_BRAKE::OFF || statusNow == CAR_BRAKE::ON) && parkingBrakeStatus == true) {
    lcd.displayParkingBrake(false);
    parkingBrakeStatus = false;
  }

}
void displayTemperature(String str) {
  // Clear the buffer.
  display.clearDisplay();
  display.setCursor(0, 25);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("INSIDE TEMPERATURE");

  display.setCursor(0, 0);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(str + (char)247 + 'c');
  display.display();
}

void displayText(String str) {
  // Clear the buffer.
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(str);
  display.display();
}
