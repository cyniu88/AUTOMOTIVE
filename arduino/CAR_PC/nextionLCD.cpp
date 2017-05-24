#include "nextionLCD.h"

NEXTION_LCD::NEXTION_LCD() {
  nextionLCD_RS232.begin(9600);
}
void NEXTION_LCD::sendEndMSG() {
  nextionLCD_RS232.write(0xFF);
  nextionLCD_RS232.write(0xFF);
  nextionLCD_RS232.write(0xFF);
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
void NEXTION_LCD::displayFuel(String str) {
  nextionLCD_RS232.write("main.fue.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("%\"");
  sendEndMSG();
}
void NEXTION_LCD::displayTemp(String str) {
  nextionLCD_RS232.write("main.loa.txt=\"");
  nextionLCD_RS232.write(str.c_str());
  nextionLCD_RS232.write("\"");
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

