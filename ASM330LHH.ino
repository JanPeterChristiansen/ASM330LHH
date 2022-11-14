#include <Wire.h>
#include "ASM330LHH.h"
#define CS 2
#define SDO 3

ASM330LHH IMU(&Wire, CS, SDO);

void setup() {

}

void loop() {
  // put your main code here, to run repeatedly:

}
