#ifndef ELM327_H
#define ELM327_H
#include <Arduino.h>
#include "useful.h"

class ELM327
{
    byte m_statePin;
    byte m_ATpin;
    void sendATCommand(String command);
    String recvATCommand();
    void sendATCommandToOBDII(String cmd);
    String recvFromOBDII();
    
  public:
    ELM327();
    ~ELM327();
    void init(unsigned int bitrate, byte statePin, byte ATpin);
    bool isConnectedToBluetooth();
    bool isELM327Connected();
    void connectingToELM327BT(String MAC_ELM327);
    int engineCoolantTemperature();
    double fuelTankLevel();
    float getVoltage();
    int engineLoad();
};
#endif
