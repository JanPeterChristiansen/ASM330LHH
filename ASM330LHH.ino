#include <Wire.h>

#define SAD 0b1101011  //IMU I2C addresss. LSB is set by SDO to 1 (HIGH)
#define CS 2           //I2C enable pin
#define SDO 3          //IMU address LSB select
#define READ 0x80
#define WRITE 0x00
#define WHO_AM_I 0x0F    // register containing device id
#define FIFO_CTRL4 0x0A  // FIFO control register 4
#define STATUS_REG 0x1E  //register containing availablility flags for data
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

struct gyr {
  uint16_t pitch;
  uint16_t roll;
  uint16_t yaw;
};
struct acc {
  uint16_t x;
  uint16_t y;
  uint16_t z;
};
struct imu {
  acc acc;
  gyr gyr;
};

void setup() {
  Wire.begin();             //join I2C bus as controller
  Serial.begin(115200);     //open serial port to computer
  pinMode(CS, OUTPUT);      //set CS pinMode to output
  digitalWrite(CS, HIGH);   //enable I2C
  pinMode(SDO, OUTPUT);     //set SDO pnmode to output
  digitalWrite(SDO, HIGH);  //set SDO to high --> LSB of ASM addr is 1
  delay(2000);
}

void loop() {
  byte e = -1;
  Serial.println("Start");

  writeRegister(&Wire, FIFO_CTRL4, 0x00);
  e = readRegister(&Wire, FIFO_CTRL4);
  Serial.println(e, BIN);

  writeRegister(&Wire, FIFO_CTRL4, 0x01);
  e = readRegister(&Wire, FIFO_CTRL4);
  Serial.println(e, BIN);

  writeRegister(&Wire, FIFO_CTRL4, 0x00);
  e = readRegister(&Wire, FIFO_CTRL4);
  Serial.println(e, BIN);

  writeRegister(&Wire, FIFO_CTRL4, 0xAA);
  e = readRegister(&Wire, FIFO_CTRL4);
  Serial.println(e, BIN);

  Serial.println("Done!\n");
  delay(2000);
}


