#include "ELM327.h"
HardwareSerial & SerialBluetooth = Serial1;

ELM327::ELM327() {

}
ELM327::~ELM327() {

}
void ELM327::sendATCommand(String command) {
  SerialBluetooth.print(command);
  SerialBluetooth.write("\r\n");
}
String ELM327::recvATCommand() {
  String recvString;
  Serial.print("recv: ");
  delay(100);
  while (SerialBluetooth.available() > 0) {
    recvString += SerialBluetooth.readString();
  }
  return recvString;
}
void ELM327::sendATCommandToOBDII(String cmd) {
  SerialBluetooth.print(cmd);
  SerialBluetooth.write("\r\n");
}
String ELM327::recvFromOBDII() {
  String recvString;
  delay(100);
  while (SerialBluetooth.available() > 0) {
    recvString += SerialBluetooth.readString();
  }
  return recvString;
}

void ELM327::init(unsigned int bitrate, byte statePin, byte ATpin) {
  SerialBluetooth.begin(bitrate);
  m_statePin = statePin;
  pinMode(m_statePin, INPUT);
  m_ATpin = ATpin;
  pinMode(m_ATpin, OUTPUT);
}

bool ELM327::isConnectedToBluetooth() {
  //SerialBluetooth.flush();
  if (digitalRead(m_statePin) == HIGH) {
    sendATCommand("ATI");
    String buf  = SerialBluetooth.readStringUntil('\n');
    Serial.print("odebralem w low: ");
    Serial.println(buf);
    return true;
  }
  digitalWrite(m_ATpin,HIGH);
  sendATCommand("AT");
  String buf  = SerialBluetooth.readStringUntil('\n');
  Serial.print("odebralem: ");
  Serial.println(buf);
  if (buf[0] == 'O' && buf[1] == 'K')
  {
    digitalWrite(m_ATpin,LOW);
    return true;
  }
  return false;
}
bool  ELM327::isELM327Connected() {
  sendATCommand("ATI");
  if ( recvATCommand() == "OK" && digitalRead(m_statePin) == HIGH)
  {
    return true;
  }
  return false;
}
void ELM327::connectingToELM327BT(String MAC_ELM327) {

  isConnectedToBluetooth();
  //sendATCommand("AT+RESET");

  delay(1000);
  isConnectedToBluetooth();
  Serial.println("version");
  sendATCommand("AT+VERSION"  );
  Serial.print(recvATCommand());
  //  Serial.println("ROLE=1");
  //  sendATCommand("AT+ROLE=1");
  //  Serial.println(recvATCommand());
  //  Serial.println("CMODE");
  //  sendATCommand("AT+CMODE=0");
  //  Serial.println(recvATCommand());
  //  Serial.println("INIT");
  //  sendATCommand("AT+INIT");
  //  Serial.println(recvATCommand());
  //  delay(1000);
  Serial.println("BIND");
  sendATCommand("AT+BIND=" + MAC_ELM327);
  Serial.println(recvATCommand());
  delay(3000);
  Serial.println("PAIR");
  sendATCommand("AT+PAIR=" + MAC_ELM327 + ",10");
  Serial.println(recvATCommand());
  delay(3000);
  Serial.println("LINK");
  sendATCommand("AT+LINK=" + MAC_ELM327);
  Serial.println(recvATCommand());
  Serial.println("SP");
  sendATCommand("AT SP 0");
  Serial.println(recvATCommand());
  Serial.println("done");
}

int ELM327::engineCoolantTemperature() {
  int temperature = 0;
  String temp;
  sendATCommandToOBDII("0105");
  temp = recvFromOBDII();
  temperature = USEFUL::hexToDec(temp.substring(6,8));
  return temperature - 40;
}
double ELM327::fuelTankLevel() {
  double level;
  String temp;
  sendATCommandToOBDII("012F");
  temp = recvFromOBDII();
  level = USEFUL::hexToDec(temp.substring(6,8));
  return (level * 100) / 255;
}

float ELM327::getVoltage() {
  float level;
  String temp="cyniu";
   sendATCommandToOBDII("AT RV");
  //sendATCommandToOBDII("AT+pswd");
  temp = recvFromOBDII();
  Serial.println("odebralem voltage:" + temp);
  temp=temp.substring(0,6);
  level = temp.toFloat();
  return level;
}
int ELM327::engineLoad(){
   int load = 0;
  String temp;
  sendATCommandToOBDII("0104");
  temp = recvFromOBDII();
  load = USEFUL::hexToDec(temp.substring(6,8));
  return (load / 255)*100;
}

