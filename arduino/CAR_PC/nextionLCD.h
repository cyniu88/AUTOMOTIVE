#ifndef NEXTION_LCD_H
#define NEXTION_LCD_H
#include <Arduino.h>
#include "useful.h"
enum  TEMPERATURELEVEL {
  COLD = 5,
  NORMAL = 7,
  HOT = 6};

class NEXTION_LCD
{
    HardwareSerial & nextionLCD_RS232 = Serial2;
    void setCoolantIcon(TEMPERATURELEVEL i);
  public:
    TEMPERATURELEVEL levelCoolant = COLD;
    NEXTION_LCD() ;
    void sendEndMSG();
    void displayMainPage();
    void displayVoltage(String str);
    void displayFuel(String str);
    void displayTemp(String str);
    void displayCoolant(String str);
    void displayLoad(String str);
    void displayOdometer(String str);
    void displayRuntime(String str);
    void displayFuelBar(String i);
    void displayCoolantBar(String str);
};
#endif
