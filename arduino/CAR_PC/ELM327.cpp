#include "ELM327.h"

ELM327::ELM327() {

}
ELM327::~ELM327() {

}
void ELM327::sendATCommand(String command){
  Serial1.print(command);
  Serial1.print("\r\n");
}
String ELM327::recvATCommand(){
  String recvString = "NULL";
   while (Serial1.available() > 0) {
    recvString += Serial.read();
   }
  return recvString;
}
void ELM327::init(int bitrate,byte statePin, byte ATpin) {
  Serial1.begin(bitrate);
  m_statePin = statePin;
  m_ATpin = ATpin;
}

bool ELM327::isConnectedToBluetooth() {
  Serial1.flush();
  Serial1.print("AT");
  Serial1.print("\r\n");
  String buf = Serial1.readString();
  if (buf == "OK")
  {
    return true;
  }
  return false;
}
bool  ELM327::isELM327Connected() {
  sendATCommand("AT");
   
  if ( recvATCommand() == "OK")
  {
    return true;
  }
  return false;
}
void ELM327::connectingToELM327BT(String MAC_ELM327){
  sendATCommand("AT+RESET");
  
  delay(1000);
  sendATCommand("AT+ROLE=1");
  recvATCommand();
  sendATCommand("AT+CMODE=0");
  recvATCommand();
  sendATCommand("AT+INIT");
  recvATCommand();
  delay(1000);
  sendATCommand("AT+BIND="+MAC_ELM327);
  recvATCommand();
  delay(3000);
  sendATCommand("AT+PAIR="+MAC_ELM327+",10");
  recvATCommand();
  delay(3000);
  sendATCommand("AT+LINK="+MAC_ELM327);
  recvATCommand();
}

