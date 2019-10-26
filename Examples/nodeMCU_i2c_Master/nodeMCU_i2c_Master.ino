#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin(D1, D2);
}

void loop() {
  Wire.beginTransmission(8);
  Wire.write("Hello Arduino");
  Wire.endTransmission();
  delay(100);
}
