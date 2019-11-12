#include <Wire.h>

Mag mag;
//Mpu mpu;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.begin();
  mag.begin();
}


void loop() {
  float headingDegrees = mag.calc_heading();

  Serial.print("x: ");
  Serial.print(mag_raw[X]);
  Serial.print("  y: ");
  Serial.print(mag_raw[Y]);
  Serial.print("  z: ");
  Serial.print(mag_raw[Z]);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();

  delay(100);
}
