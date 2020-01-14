#include <PinChangeInterrupt.h>

volatile int pwm = 0;
volatile int prev_time = 0;

void rising()
{
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(5), falling, FALLING);
  prev_time = micros();
}

void falling()
{
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(5), rising, RISING);
  pwm = micros() - prev_time;
  Serial.println(pwm);
}

void setup()
{
  pinMode(5, INPUT);
  digitalWrite(5, HIGH);
  
  pinMode(6, OUTPUT);
  analogWrite(6, 10);
  
  Serial.begin(115200);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(5), rising, RISING);
}

void loop()
{
  
}
