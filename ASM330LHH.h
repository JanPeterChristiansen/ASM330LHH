#ifndef ASM330LHH_H
#define ASM330LHH_H

#include <Arduino.h>
#include <Wire.h>

//addresses
#define SAD 0b1101011  //IMU I2C addresss. LSB is set by SDO to 1 (HIGH)
#define READ 0x80      //added to SAD to get read address
#define WRITE 0x00     //added to SAD to get write addresss
//startup registers
#define CTRL1_XL 0x10  //acc odr and range register
#define CTRL2_G 0x11   //gyr odr and range register
//gyro registers
#define OUTX_L_G 0x22  //pitch low
#define OUTX_H_G 0x23  //pitch high
#define OUTY_L_G 0x24  //roll low
#define OUTY_H_G 0x25  //roll high
#define OUTZ_L_G 0x26  //yaw low
#define OUTZ_H_G 0x27  //yaw high
//accel registers
#define OUTX_L_A 0x28  //ax low
#define OUTX_H_A 0x29  //ax high
#define OUTY_L_A 0x2A  //ay low
#define OUTY_H_A 0x2B  //ay high
#define OUTZ_L_A 0x2C  //az low
#define OUTZ_H_A 0x2D  //az high

struct gyr {  //gyroscope states
  int pitch;
  int roll;
  int yaw;
};
struct acc {  //accelerometer states
  int x;
  int y;
  int z;
};

class ASM330LHH {
public:
  ASM330LHH(TwoWire* i2c, int cs, int sdo);
  void begin();
  void getAcc();
  void getGyr();
  void getIMU();
  acc acc;
  gyr gyr;
private:
  byte readReg(byte reg);
  void writeReg(byte reg, byte data);
  int getAxes(byte LO_ADDR, byte HI_ADDR);
  TwoWire* i2c;
  int cs;
  int sdo;
  unsigned long timeOut = 1000;
};


#endif