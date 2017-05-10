#ifndef ELM327_H
#define ELM327_H
#include <Arduino.h>

class ELM327
{
  byte m_statePin;
  byte m_ATpin;
  void sendATCommand(String command);
  String recvATCommand();
  public:
  ELM327();
  ~ELM327();
  void init(int bitrate, byte statePin, byte ATpin);
  bool isConnectedToBluetooth();
  bool isELM327Connected();
  void connectingToELM327BT(String MAC_ELM327);
};
#endif
