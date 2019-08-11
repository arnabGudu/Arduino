void motor(int motorSpeed)
{
  analogWrite(leftPwm, baseSpeed + motorSpeed);
  analogWrite(rightPwm, baseSpeed - motorSpeed);
}
