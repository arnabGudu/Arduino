int16_t ypr[] = {0, 0, 0};
int YPRT[] = {0, 0, 0, 0};

void setup() {
  Serial.begin(115200);
  setup_PCINT();
  setup_mpu();
}

void loop() {
  calcMotion();
  calcErrors();
  pidControl();
  motorSpeed();
}

void calcErrors()
{
  
}

void pidControl()
{
  
}

void motorSpeed()
{
  
}
