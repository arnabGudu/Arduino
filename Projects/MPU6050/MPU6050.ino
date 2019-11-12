#include <Wire.h>
float measures[3] = {0, 0, 0};

void setup() {
  Serial.begin(115200);
  Wire.begin();
  setupMpu6050Registers();
  calibrateMpu6050();

}

void loop() {
  readSensor();
  calculateAngles();
//  Serial.print("Y");
//  Serial.print(measures[0]);
//  Serial.print("P");
//  Serial.print(measures[1]);
//  Serial.print("R");
//  Serial.print(measures[2]);
//  Serial.println();

  Serial.print(measures[0]);
  Serial.print(",");
  Serial.print(measures[0]);
  Serial.print(",");
  Serial.print(measures[0]);
  Serial.println();
}
