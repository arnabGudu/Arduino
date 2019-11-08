#include <Wire.h>

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMpu6050Registers();
  calibrateMpu6050();

}

void loop() {
  readSensor();
  calculateAngles();
}
