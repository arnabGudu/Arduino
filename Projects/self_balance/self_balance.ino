#include "I2Cdev.h"
#include "MPU6050.h"
#include <ros.h>
#include <std_msgs/Empty.h>

#define setPoint 0
#define T 10

MPU6050 mpu;

void setup() {

  Serial.begin(115200);
  mpu.initialize();
  Wire.begin();

  pinmode();
  compl_filter(1);
  ros_setup();

  test();
}

void loop() {
  compl_filter(0);
  ros_loop();
  Serial.println();
  delay(2);
}
