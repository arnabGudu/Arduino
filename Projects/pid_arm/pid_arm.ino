#include <Servo.h>
#include "I2Cdev.h"
#include "MPU6050.h"

double angle;

int16_t accY, accZ;
int16_t gyroX;
uint32_t timer;
int T = 10;
int setPoint = -30;

Servo bldc;
MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  bldc.attach(9);
  mpu.initialize();
  Wire.begin();
}

void loop() {
  accY = mpu.getAccelerationY();
  accZ = mpu.getAccelerationZ();
  gyroX = mpu.getRotationX();

  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();

  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double gyro = gyroX / 131.0; // Convert to deg/s

  angle = 0.93 * (angle + gyro * dt) + 0.07 * roll;

  Serial.println(angle);

  if (dt >= T)
  {
    pid();
  }
  delay(2);
}

float kp, kd, ki;
double integ = 0, lastError = 0;

void pid()
{
  double error = angle - setPoint;
  integ += error;
  integ = constrain(integ, 0, 180);
  double deriv = error - lastError;
  double balance = kp * error + ki * integ * T + kd * deriv / T;
  balance = constrain(balance, 0, 180);
  bldc.write(balance);
}
