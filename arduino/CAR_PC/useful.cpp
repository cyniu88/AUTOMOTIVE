#include "useful.h"
unsigned int USEFUL::hexToDec(String hexString) {
  unsigned int decValue = 0;
  int nextInt;

  for (int i = 0; i < hexString.length(); i++) {
    nextInt = int(hexString.charAt(i));
    if (nextInt >= 48 && nextInt <= 57)
      nextInt = map(nextInt, 48, 57, 0, 9);
    if (nextInt >= 65 && nextInt <= 70)
      nextInt = map(nextInt, 65, 70, 10, 15);
    if (nextInt >= 97 && nextInt <= 102)
      nextInt = map(nextInt, 97, 102, 10, 15);

    nextInt = constrain(nextInt, 0, 15);
    decValue = (decValue * 16) + nextInt;
  }
  return decValue;
}

void USEFUL::freeMode() {
  String bufor;
  Serial.println("start free mode");
  while (true) {
    if (Serial.available()) {
      while (Serial.available() > 0) {
        bufor += Serial.readString();
      }
      if (bufor[0] == 'E' && bufor[4] == '!') {
        break;
      }
      Serial.println("you send:" + bufor);
      Serial1.write(bufor.c_str());
      Serial1.write("\r\n");
      bufor = "";
    }
    if (Serial1.available()) {
      Serial.println("jest cos do odbioru");
      while (Serial1.available() > 0) {
        bufor += Serial1.readString();
      }
      Serial.println("recv: " + bufor);
      bufor = "";
    }
  }
  Serial.println("stop free mode");
}
String USEFUL::convertSecToHMstring(int sec){
  String h;
  String m;
  int hInt;
  int mInt;
  mInt = sec / 60;
  hInt = mInt / 60;
  mInt = mInt - hInt * 60;
  m  = String(mInt);
  h = String(hInt);
  return h+" h "+m+" m";
}

