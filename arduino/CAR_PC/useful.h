#ifndef USEFUL_H
#define USEFUL_H
#include <Arduino.h>

class USEFUL
{
  public:
    static unsigned int hexToDec(String hexString);
    static void freeMode();
    static String convertSecToHMstring(int sec);
};
#endif
 
