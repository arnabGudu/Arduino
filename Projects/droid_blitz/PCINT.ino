#include "PinChangeInterrupt.h"

int prev_time[] = {0, 0, 0, 0, 0, 0, 0, 0};
bool state[] = {0, 0, 0, 0, 0, 0, 0, 0};

void ch1()
{
  state[0] = !state[0];
  if (state[0])
    prev_time[0] = micros();
  else
    pwm[0] = micros() - prev_time[0];
}

void ch2()
{
  state[1] = !state[1];
  if (state[1])
    prev_time[1] = micros();
  else
    pwm[1] = micros() - prev_time[1];
}

void ch3()
{
  state[2] = !state[2];
  if (state[2])
    prev_time[2] = micros();
  else
    pwm[2] = micros() - prev_time[2];
}

void ch4()
{
  state[3] = !state[3];
  if (state[3])
    prev_time[3] = micros();
  else
    pwm[3] = micros() - prev_time[3];
}

void ch5()
{
  state[4] = !state[4];
  if (state[4])
    prev_time[4] = micros();
  else
    pwm[4] = micros() - prev_time[4];
}

void ch6()
{
  state[5] = !state[5];
  if (state[5])
    prev_time[5] = micros();
  else
    pwm[5] = micros() - prev_time[5];
}

void setup_PCINT() {
  attachPCINT(digitalPinToPCINT(4), ch1, CHANGE);
  attachPCINT(digitalPinToPCINT(5), ch2, CHANGE);
  attachPCINT(digitalPinToPCINT(6), ch3, CHANGE);
  attachPCINT(digitalPinToPCINT(7), ch4, CHANGE);
  attachPCINT(digitalPinToPCINT(8), ch5, CHANGE);
  attachPCINT(digitalPinToPCINT(9), ch6, CHANGE);
}
