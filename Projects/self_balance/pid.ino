#define leftPwm 6
#define rightPwm 5

float kp = 3.64, kd = 0, ki = 0;
double integ = 0, lastError = 0;

void pid()
{  
  double error = compAngleY - setPoint;
  integ += error;
  integ = constrain(integ, -255, 255);
  double deriv = error - lastError;
  double balance = kp * error + ki * integ * T + kd * deriv / T;
  balance = constrain(balance, -255, 255);

  /*if (balance >= 0)
  {
    balance = map(balance, 0, 180, 35, 255);
    dir(HIGH);
  }
  else
  {
    balance = map(balance, -180, 0, -255, -35);
    dir(LOW);
  }*/
  
  Serial.print(balance);  //Serial.print("\t");
  //Serial.print(kp); Serial.print("\t");
  //Serial.print(ki); Serial.print("\t");
  //Serial.print(kd);

  analogWrite(leftPwm, balance);
  analogWrite(rightPwm, balance);
}

#define leftF 10
#define leftB 11
#define rightF 9
#define rightB 8


void pinmode()
{
  pinMode(leftF, OUTPUT);
  pinMode(leftB, OUTPUT);
  pinMode(rightF, OUTPUT);
  pinMode(rightB, OUTPUT);
}

void dir(bool dirn)
{
  digitalWrite(leftF, dirn);
  digitalWrite(leftB, !dirn);
  digitalWrite(rightF, dirn);
  digitalWrite(rightB, !dirn);
}

void test()
{
  analogWrite(leftPwm, 255);
  analogWrite(rightPwm, 255);
  
  digitalWrite(leftF, HIGH);
  digitalWrite(leftB, LOW);
  digitalWrite(rightF, HIGH);
  digitalWrite(rightB, LOW);
  delay(100);
  
  digitalWrite(leftF, LOW);
  digitalWrite(leftB, HIGH);
  digitalWrite(rightF, LOW);
  digitalWrite(rightB, HIGH);
  delay(100);

  digitalWrite(leftF, LOW);
  digitalWrite(leftB, LOW);
  digitalWrite(rightF, LOW);
  digitalWrite(rightB, LOW);
  delay(1000);
}
