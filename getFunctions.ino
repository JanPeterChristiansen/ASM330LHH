imu getIMU(TwoWire* i2c) {
  imu imu;
  imu.gyr = getGyr(i2c);
  imu.acc = getAcc(i2c);
  return imu;
}

acc getAcc(TwoWire* i2c) {
  acc acc;
  acc.x = getAxes(i2c, OUTX_L_A, OUTX_H_A);
  acc.y = getAxes(i2c, OUTY_L_A, OUTY_H_A);
  acc.z = getAxes(i2c, OUTZ_L_A, OUTZ_H_A);
  return acc;
}

gyr getGyr(TwoWire* i2c) {
  gyr gyr;
  gyr.pitch = getAxes(i2c, OUTX_L_G, OUTX_H_G);
  gyr.roll = getAxes(i2c, OUTY_L_G, OUTY_H_G);
  gyr.yaw = getAxes(i2c, OUTZ_L_G, OUTZ_H_G);
  return gyr;
}

uint16_t getAxes(TwoWire* i2c, byte LO_ADDR, byte HI_ADDR) {
  byte high = readRegister(i2c, HI_ADDR);
  byte low = readRegister(i2c, LO_ADDR);
  return high << 8 + low;
}