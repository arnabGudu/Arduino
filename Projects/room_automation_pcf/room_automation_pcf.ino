#include <pcf8574_esp.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

TwoWire testWire;
PCF857x pcf(0x20, &testWire);

void setup() {
  Serial.begin(115200);

  testWire.begin(4, 5);
  testWire.setClock(100000L);
  pcf.begin();
}

void loop() {
  pcf.write(2, LOW);
  delay(1000);
  pcf.write(2, HIGH);
  delay(1000);
}
