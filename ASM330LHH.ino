#include <Wire.h>
#include "ASM330LHH.h"
#define CS 2
#define SDO 3

ASM330LHH IMU(&Wire, CS, SDO);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  IMU.begin();
}

void loop() {
  unsigned long t = millis();
  IMU.getIMU();
  printIMU();
  while ((millis() - t) < 10) {}
}


void printIMU() {
  Serial.print(String(millis()) + ",");
  Serial.print(String(IMU.acc.x) + ",");
  Serial.print(String(IMU.acc.y) + ",");
  Serial.print(String(IMU.acc.z) + ",");
  Serial.print(String(IMU.gyr.roll) + ",");
  Serial.print(String(IMU.gyr.pitch) + ",");
  Serial.println(String(IMU.gyr.yaw));
}