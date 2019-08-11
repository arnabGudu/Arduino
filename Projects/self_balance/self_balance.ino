#include "I2Cdev.h"
#include "MPU6050.h"

#define setPoint 0
#define T 10

MPU6050 mpu;

void setup() {

  Serial.begin(115200);
  mpu.initialize();
  Wire.begin();

  pinmode();
  compl_filter(1);

  test();
}

void loop() {
  compl_filter(0);
  Serial.println();
  delay(2);
}
