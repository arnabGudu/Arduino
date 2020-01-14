#include <PinChangeInterrupt.h>

bool state = LOW;
unsigned int prev_time = 0;
unsigned int pwm = 0;

void isr()
{
  if (state = LOW)
    prev_time = micros();
  else
    pwm = micros() - prev_time;
    
  state = !state;
}

void setup()
{
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  analogWrite(6, 125);
  attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(5), isr, CHANGE);
}

void loop()
{
  Serial.println(float(pwm) / 1000);
}
