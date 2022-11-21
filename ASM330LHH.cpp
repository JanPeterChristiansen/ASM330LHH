#include <Arduino.h>
#include "ASM330LHH.h"

ASM330LHH::ASM330LHH(TwoWire* i2c, int cs, int sdo) {
  ASM330LHH::i2c = i2c;
  ASM330LHH::cs = cs;
  ASM330LHH::sdo = sdo;
}

void ASM330LHH::begin() {
  pinMode(cs, OUTPUT);      //set CS pinMode to output
  digitalWrite(cs, HIGH);   //enable I2C
  pinMode(sdo, OUTPUT);     //set SDO pnmode to output
  digitalWrite(sdo, HIGH);  //set SDO to high --> LSB of ASM addr is 1
  delay(100);
  //set ODR_XL to 0110 (416 Hz), FS_XL to 00 (+-2g),
  //and LPF2_XL_EN to 0 (LPF2 bypass)
  writeReg(CTRL1_XL, 0b0110000);
  //set ODR_G to 0110 (416 Hz), FS_G to 00 (+- 250 dpd),
  //FS_125 to 0 (bypass), and FS_4000 to 0 (bypass)
  writeReg(CTRL2_G, 0b01100000);
}

void ASM330LHH::writeReg(byte reg, byte data) {
  i2c->beginTransmission(WRITE + SAD);
  i2c->write(reg);
  i2c->write(data);
  i2c->endTransmission();
}

byte ASM330LHH::readReg(byte reg) {
  i2c->beginTransmission(WRITE + SAD);
  i2c->write(reg);
  i2c->endTransmission();
  i2c->requestFrom(READ + SAD, 1);
  unsigned long t0 = millis();
  while (!i2c->available() && ((millis() - t0) < timeOut)) {}
  return i2c->read();
}

void ASM330LHH::getIMU() {
  getGyr();
  getAcc();
}

void ASM330LHH::getAcc() {
  acc.x = getAxes(OUTX_L_A, OUTX_H_A);
  acc.y = getAxes(OUTY_L_A, OUTY_H_A);
  acc.z = getAxes(OUTZ_L_A, OUTZ_H_A);
}

void ASM330LHH::getGyr() {
  gyr.pitch = getAxes(OUTX_L_G, OUTX_H_G);
  gyr.roll = getAxes(OUTY_L_G, OUTY_H_G);
  gyr.yaw = getAxes(OUTZ_L_G, OUTZ_H_G);
}

int ASM330LHH::getAxes(byte LO_ADDR, byte HI_ADDR) {
  byte high = readReg(HI_ADDR);
  byte low = readReg(LO_ADDR);
  return (((uint16_t)high) << 8) | ((uint16_t)low);
}