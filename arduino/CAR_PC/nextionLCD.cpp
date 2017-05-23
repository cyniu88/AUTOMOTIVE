#include "nextionLCD.h"

NEXTION_LCD::NEXTION_LCD() {
  nextionLCD_RS232.begin(9600);
}
void NEXTION_LCD::sendEndMSG(){
  nextionLCD_RS232.write(0xFF);
  nextionLCD_RS232.write(0xFF);
  nextionLCD_RS232.write(0xFF);
}
void NEXTION_LCD::displayMainPage(){
  nextionLCD_RS232.write("page 1");
  sendEndMSG();
}
