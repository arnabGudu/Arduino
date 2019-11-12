#define address 0x68
#define X 0
#define Y 1
#define Z 2

#define YAW      0
#define PITCH    1
#define ROLL     2
#define SSF_GYRO    65.5
#define FREQ        250

class mag
{
  public:
    mpu();
    void begin();
    void readRegisters();
    float ();
  private:
    int acc_raw[3], gyro_raw[3], temperature;
    float measures[3];
};

mpu::begin()
{

}

void mpu::comp_filter()
{
  readRegisters();
  caclAccelAngles();
  
  gyro_angle[X] = gyro_angle[X] * 0.9996 + acc_angle[X] * 0.0004;
  gyro_angle[Y] = gyro_angle[Y] * 0.9996 + acc_angle[Y] * 0.0004;

  measures[ROLL]  = measures[ROLL]  * 0.9 + gyro_angle[X] * 0.1;
  measures[PITCH] = measures[PITCH] * 0.9 + gyro_angle[Y] * 0.1;
  measures[YAW]   = -gyro_raw[Z] / SSF_GYRO;
}

void mpu::caclAccelAngles()
{
  norm = sqrt(pow(acc_raw[X], 2) + pow(acc_raw[Y], 2) + pow(acc_raw[Z], 2));
  if (abs(acc_raw[X]) < norm)
    acc_angle[X] = asin((float)acc_raw[Y] / norm) * (180 / PI);

  if (abs(acc_raw[Y] < norm)
    acc_angle[Y] = asin((float)acc_raw[X] / norm) * (180 / PI);
}

void mpu::caclGyroAngles()
{
  gyro_raw[X] -= gyro_offset[X];
  gyro_raw[Y] -= gyro_offset[Y];
  gyro_raw[Z] -= gyro_offset[Z];

  gyro_angle[X] += (gyro_raw[X] / (FREQ * SSF_GYRO));
  gyro_angle[Y] += (-gyro_raw[Y] / (FREQ * SSF_GYRO)); 
  
  gyro_angle[Y] += gyro_angle[X] * sin(gyro_raw[Z] * (PI / (FREQ * SSF_GYRO * 180)));
  gyro_angle[X] -= gyro_angle[Y] * sin(gyro_raw[Z] * (PI / (FREQ * SSF_GYRO * 180)));
}

void mpu::readRegisters()
{
  Wire.beginTransmission(address);
  Wire.write(0x3B);
  Wire.endTransmission();

  Wire.requestFrom(address, 14);
  if (Wire.available() < 14)
  {
    acc_raw[X]  = Wire.read() << 8 | Wire.read();
    acc_raw[Y]  = Wire.read() << 8 | Wire.read();
    acc_raw[Z]  = Wire.read() << 8 | Wire.read();
    temperature = Wire.read() << 8 | Wire.read();
    gyro_raw[X] = Wire.read() << 8 | Wire.read();
    gyro_raw[Y] = Wire.read() << 8 | Wire.read();
    gyro_raw[Z] = Wire.read() << 8 | Wire.read();
  }
}
