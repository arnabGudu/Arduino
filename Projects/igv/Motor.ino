void motor(int balance)
{
  analogWrite(pwmL, base + balance);
  analogWrite(pwmR, base - balance);
}

void forward()
{
  digitalWrite(dirL, HIGH);
  digitalWrite(dirR, HIGH);
}

void backward()
{
  digitalWrite(dirL, LOW);
  digitalWrite(dirR, LOW);
}
