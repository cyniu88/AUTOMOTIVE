#define BluetoothRS232 Serial1


String st = "kupa";

void setup()
{
  Serial.begin(9600);
  BluetoothRS232.begin(38400);
  Serial.println("setup done");
}

void loop()
{
  if (Serial.available()) {
    st = Serial.readStringUntil(';');

    Serial.println("bangla sobie");
    BluetoothRS232.flush();
    BluetoothRS232.print(st);
    BluetoothRS232.print("\r\n");

 

    st = BluetoothRS232.readStringUntil("OK");
    delay(100);
    Serial.println(st);
  }
}

