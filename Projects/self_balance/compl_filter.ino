double compAngleY;

int16_t gyroY;
uint32_t timer;

void compl_filter(bool set)
{
  int16_t accX = mpu.getAccelerationX();
  int16_t accZ = mpu.getAccelerationZ();
  gyroY = mpu.getRotationY();

  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
  double gyroYrate = gyroY / 131.0; // Convert to deg/s

  if (set)
  {
    compAngleY = pitch;
  }
  else
  {
    double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
    timer = micros();
    compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;
    Serial.print(compAngleY); Serial.print("\t");
    //pid();
  }
}
