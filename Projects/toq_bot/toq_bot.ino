void setup() {
  // put your setup code here, to run once:
  attachInterrupt(0, ISR, RISING);
  attachInterrupt(1, ISR, RISING);
}

void loop() {
  count_total = (count_left + count_right) / 2;
  int input = 0;
  for (int i = 0; i < 6; i++)
    input = input | digitalRead(i) << i;

  track_detect(input);
  Serial.println();
}

void track_detect(int input)
{
  int current[5] = {0b110011, 0b000111, 0, 0b111000, 0b001100};
  switch (input ^ current[index])
  {
    case 0b111111:
      index = ((index - 2) * -1) + 2; break;
    case 0b110100:
      index =  (2 / (index - 2)) + 2; break;
    case 0b001011:
      index = (-2 / (index - 2)) + 2; break;
  }

  Serial.print(index);
  Serial.print("\t");

  error_calc(input ^ current[index]);
}

void error_calc(int input)
{
  int left = input >> 3;
  int right = input ^ left << 3;

  //swapping 0th and 2nd position
  int x = (right >> 0 & 1) ^ (right >> 2 & 1);
  x = (x << 0) | (x << 2);
  right = right ^ x;

  int error = right * -1 + left;

  Serial.print(input);
  Serial.print("\t");
  Serial.print(error);

  pid(error);
}

unsigned long last_time = 0;
int integral = 0, lastError = 0;
float kp, kd, ki;
int T = 50;

void pid(int error)
{
  unsigned long current_time = millis();
  int dt = millis() - last_time;
  if (dt >= T)
  {
    integral += error;
    integral = constrain(integral, 0, 255);
    int derivative = error - lastError;
  }
  float balance = kp * error + ki * integral * T + kd * derivative / T;
  balance = constrain(balance, 0, 255);

  lastError = error;
  last_time = current_time;
}
