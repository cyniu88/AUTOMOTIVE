#ifndef NEXTION_LCD_H
#define NEXTION_LCD_H
#include <Arduino.h>
#include "useful.h"

class NEXTION_LCD
{
    HardwareSerial & nextionLCD_RS232 = Serial2;
  public:
    NEXTION_LCD() ;
    void sendEndMSG();
    void displayMainPage();
    void displayVoltage(String str);
    void displayFuel(String str);
    void displayTemp(String str);
    void displayCoolant(String str);
    void displayLoad(String str);
};
#endif
