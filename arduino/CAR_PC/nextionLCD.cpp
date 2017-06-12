#include "nextionLCD.h"

NEXTION_LCD::NEXTION_LCD() {
  nextionLCD_RS232.begin(9600);
}
void NEXTION_LCD::sendEndMSG() {
  nextionLCD_RS232.write(0xFF);
  nextionLCD_RS232.write(0xFF);
  nextionLCD_RS232.write(0xFF);

  if (nextionLCD_RS232.available() > 0) {
    while (nextionLCD_RS232.available() > 0) {
      Serial.print(nextionLCD_RS232.read());
    }
    Serial.println("");
  }
}
void NEXTION_LCD::displayMainPage() {
  nextionLCD_RS232.write("page 1");
  sendEndMSG();
}

void NEXTION_LCD::displayVoltage(String str) {
  nextionLCD_RS232.write("main.vol.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("\"");
  sendEndMSG();
}
void NEXTION_LCD::displayFuelBar(String i) {
  nextionLCD_RS232.write("main.fuelLevel.val=");
  nextionLCD_RS232.write(i.c_str());
  sendEndMSG();
}
void NEXTION_LCD::displayFuel(String str) {
  nextionLCD_RS232.write("main.fue.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("%\"");
  sendEndMSG();
}
void NEXTION_LCD::displayTemp(String str) {
  nextionLCD_RS232.write("main.temp.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("\"");
  sendEndMSG();
}
void NEXTION_LCD::displayCoolantBar(String str) {
  int temp = str.toInt();
  if (temp > 40 && temp < 91 && levelCoolant != NORMAL) {
    setCoolantIcon(NORMAL);
    levelCoolant = NORMAL;
  }
  else if (temp >= 91 && levelCoolant != HOT) {
    levelCoolant = HOT;
    setCoolantIcon(HOT);
  }
  else if (temp <= 40 && levelCoolant != COLD) {
    levelCoolant = COLD;
    setCoolantIcon(COLD);
  }
  if (temp < -10 ) {
    temp = -10;
  }
  else if (temp > 110) {
    temp = 110;
  }
  str = String(map(temp, -10, 110, 0, 100   ));
  nextionLCD_RS232.write("main.tempBar.val=");
  nextionLCD_RS232.write(str.c_str());
  sendEndMSG();
}
void NEXTION_LCD::displayCoolant(String str) {
  nextionLCD_RS232.write("main.wat.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("\"");
  sendEndMSG();
}
void NEXTION_LCD::displayLoad(String str) {
  nextionLCD_RS232.write("main.loa.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("\"");
  sendEndMSG();
}
void NEXTION_LCD::displayOdometer(String str) {
  nextionLCD_RS232.write("main.odom.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write(" KM\"");
  sendEndMSG();
}
void NEXTION_LCD::displayRuntime(String str) {
  nextionLCD_RS232.write("main.time.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("\"");
  sendEndMSG();
}
void NEXTION_LCD::setCoolantIcon(TEMPERATURELEVEL i) {
  nextionLCD_RS232.write("main.watIcon.pic=");
  nextionLCD_RS232.write(String(i).c_str());
  sendEndMSG();
}
void NEXTION_LCD::displayBrakeStat(String str) {
  nextionLCD_RS232.write("main.brake.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("\"");
  sendEndMSG();
}
void NEXTION_LCD::displayBrakeCounter(int i) {
  nextionLCD_RS232.write("main.counter.val=");
  nextionLCD_RS232.write(String(i).c_str());
  sendEndMSG();
}

void NEXTION_LCD::displayParkingBrake(bool s) {
  if (s == true) {
    nextionLCD_RS232.write("page parking");
    sendEndMSG();
  }
  else
  {
    nextionLCD_RS232.write("page main");
    sendEndMSG();
  }
}

