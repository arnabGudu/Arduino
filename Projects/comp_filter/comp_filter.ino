#include "I2Cdev.h"
#include "MPU6050.h"

double compAngleX, compAngleY;

int16_t accX, accY, accZ;
int16_t gyroX, gyroY, gyroZ;
uint32_t timer;

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  mpu.initialize();
  Wire.begin();
}

void loop() {
  mpu.getMotion6(&accX, &accY, &accZ, &gyroX, &gyroY, &gyroZ);

  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;

  double gyroXrate = gyroX / 131.0; // Convert to deg/s
  double gyroYrate = gyroY / 131.0; // Convert to deg/s

  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll;
  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;
  
  Serial.println(String(compAngleX) + "," + String(compAngleY));
  delay(2);
}
