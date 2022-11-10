byte writeRegister(TwoWire* i2c, byte reg, byte data) {
  i2c->beginTransmission(WRITE + SAD);
  i2c->write(reg);
  i2c->write(data);
  byte error = i2c->endTransmission();
  return error;
}

byte readRegister(TwoWire* i2c, byte reg) {
  i2c->beginTransmission(WRITE + SAD);
  i2c->write(reg);
  byte error = i2c->endTransmission();
  if (error > 0) {
    return error;
  }
  i2c->requestFrom(READ + SAD, 1);
  unsigned long t0 = millis();
  while (!i2c->available() || millis() - t0 > 1000) {}
  if (i2c->available()) {
    return i2c->read();
  } else {
    return -1;
  }
}