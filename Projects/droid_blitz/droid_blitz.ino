int pwm[] = {0, 0, 0, 0, 0, 0, 0, 0};
byte dMotor[] = {2, 4, 7, 8, 12, 13};
byte aMotor[] = {3, 5, 6, 9, 10, 11};

void setup() {
  Serial.begin(115200);
  setup_PCINT();
}

void loop() {
  for (int i = 0; i < 6; i++)
  {
    long pwm_out;
    bool directn = LOW;
    if (i == 0 || i == 1 || i == 3)
    {
      pwm_out = map(pwm[i], 900, 2000, -255, 255);
      directn = (pwm_out >= 0) ? LOW : HIGH;
    }
    else
      pwm_out = map(pwm[i], 900, 2000, 0, 255);

    analogWrite(aMotor[i], abs(pwm_out));
    digitalWrite(dMotor[i], directn);
  }  
}
