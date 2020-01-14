#include <Wire.h>

int accl_raw[3] = {0,0,0};
int gyro_raw[3] = {0,0,0};
int accl_angle[3] = {0,0,0};
int gyro_angle[3] = {0,0,0};

void setup()
{
  Wire.begin();
  TWBR = 24;      //set I2C clock to 400kHz

  for (int i = 4; i <= 10; i++)
    pinMode(i, OUTPUT);

  setupRegisters();

  calibrate();
}

void loop()
{
  readSensor();

  calcAngle();

  calcError();

  if (isStarted())
    pid();
}

void readSensor()
{
  Wire.beginTransmission(MPU_ADD);
  Wire.write(0x3B);
  Wire.endTransmission();

  Wire.requestFrom(MPU_ADD, 14);

  while (Wire.available() < 14);    //wait until all 14 bytes are recieved

  accl_raw[X] = Wire.read() << 8 | Wire.read();
  accl_raw[Y] = Wire.read() << 8 | Wire.read();
  accl_raw[Z] = Wire.read() << 8 | Wire.read();
  temp       = Wire.read() << 8 | Wire.read();
  gyro_raw[X] = Wire.read() << 8 | Wire.read();
  gyro_raw[Y] = Wire.read() << 8 | Wire.read();
  gyro_raw[Z] = Wire.read() << 8 | Wire.read();

}

void calcaccl()
{
  norm = sqrt(pow(accl_raw[X], 2) + pow(accl_raw[Y], 2) + pow(accl_raw[Z], 2));

  if (abs(accl_raw[X]) < norm)
    accl_angle[X] = asin((float)accl_raw[Y] / norm) * 180 / PI;

  if (abs(accl_raw[Y]) < norm)
    accl_angle[Y] = asin((float)accl_raw[X] / norm) * 180 / PI;
}

void calcGyro()
{
  gyro_raw[X] -= gyro_offset[X];
  gyro_raw[Y] -= gyro_offset[Y];
  gyro_raw[Z] -= gyro_offset[Z];

  gyro_angle[X] += (gyro_raw[X] / (FREQ * SSF_GYRO));
  gyro_angle[Y] += (-gyro_raw[Y] / (FREQ * SSF_GYRO));

  gyro_angle[Y] += gyro_angle[X] * sin(gyro_raw[Z] * (PI / (FREQ * SSF_GYRO * 180)));
  gyro_angle[X] -= gyro_angle[Y] * sin(gyro_raw[Z] * (PI / (FREQ * SSF_GYRO * 180)));
}

void calcAngle()
{

}
