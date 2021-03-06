#ifndef ELM327_H
#define ELM327_H
#include <Arduino.h>
#include "useful.h"
enum class CAR_BRAKE{
  ON,
  OFF,
  PARKING_BRAKE,
  BOTH_BRAKE
};
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
    void elm327WaitForReady();
    void connectingToELM327BT(String MAC_ELM327);
    void setupELM327();
    void setPcmHeader();
    int engineCoolantTemperature();
    int fuelTankLevel();
    float getVoltage();
    int engineLoad();
    CAR_BRAKE brakeON();
    int ambientAirTemperature();
    long runTimeEngineStart();
    int odometerCurrent();
};
#endif
