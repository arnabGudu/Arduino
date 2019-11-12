#define address 0x1E //0011110b, I2C 7bit address of HMC5883
#define X 0
#define Y 1
#define Z 2 

class Mag
{
  public:
    Mag();
    void begin();
    void readRegisters();
    float calc_heading();
  private:
    int mag_raw[3];  
};

Mag::begin()
{ 
  Wire.beginTransmission(address);
  Wire.write(0x02); //select mode register
  Wire.write(0x00); //continuous measurement mode
  Wire.endTransmission();  
}

void Mag::readRegisters()
{
  Wire.beginTransmission(address);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(address, 6);
  if (6 <= Wire.available())
  {
    mag_raw[0] = Wire.read() << 8 | Wire.read();
    mag_raw[2] = Wire.read() << 8 | Wire.read();
    mag_raw[1] = Wire.read() << 8 | Wire.read();
  }
}

float Mag::calc_heading()
{
  float heading = atan2(mag_raw[Y], mag_raw[X]);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / M_PI);
  heading += declinationAngle;

  if (heading < 0)
    heading += 2 * PI;

  if (heading > 2 * PI)
    heading -= 2 * PI;

  float headingDegrees = heading * 180 / M_PI;
  return headingDegrees;
}
