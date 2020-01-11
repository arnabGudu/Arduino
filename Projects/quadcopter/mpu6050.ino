#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 mpu;

void setup_mpu()
{
  Wire.begin();
  mpu.initialize();
}

int16_t* readSensor()
{
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  int16_t motion[] = {ax, ay, az, gx, gy, gz};
  return motion;
}

void calcAngles()
{
  readSensor();
  int16_t* motion = readSensor();

}

void calcMotion()
{
  
}
