#include <Wire.h>
//pins
#define CS 2   //I2C/SPI enable pin
#define SDO 3  //IMU address LSB select
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
  int16_t pitch;
  int16_t roll;
  int16_t yaw;
};
struct acc {  //accelerometer states
  int16_t x;
  int16_t y;
  int16_t z;
};
struct imu {  //combined IMU states
  acc acc;
  gyr gyr;
};


unsigned long t0 = millis();  //delay timer variable
imu IMU;                      //imu struct

void setup() {
  Wire.begin();             //join I2C bus as controller
  Serial.begin(115200);     //open serial port to computer
  pinMode(CS, OUTPUT);      //set CS pinMode to output
  digitalWrite(CS, HIGH);   //enable I2C
  pinMode(SDO, OUTPUT);     //set SDO pnmode to output
  digitalWrite(SDO, HIGH);  //set SDO to high --> LSB of ASM addr is 1
  delay(100);
  //set ODR_XL to 0110 (416 Hz), FS_XL to 00 (+-2g),
  //and LPF2_XL_EN to 0 (LPF2 bypass)
  writeRegister(&Wire, CTRL1_XL, 0b0110000);
  //set ODR_G to 0110 (416 Hz), FS_G to 00 (+- 250 dpd),
  //FS_125 to 0 (bypass), and FS_4000 to 0 (bypass)
  writeRegister(&Wire, CTRL2_G, 0b01100000);
}

void loop() {
  if ((millis() - t0) > 5) {
    t0 = millis();
    IMU = getIMU(&Wire);
    printIMU(&IMU);
  }
}


void printIMU(imu* imu) {
  Serial.print(millis());
  Serial.print(",");
  Serial.print(imu->acc.x);
  Serial.print(",");
  Serial.print(imu->acc.y);
  Serial.print(",");
  Serial.print(imu->acc.z);
  Serial.print(",");
  Serial.print(imu->gyr.roll);
  Serial.print(",");
  Serial.print(imu->gyr.pitch);
  Serial.print(",");
  Serial.print(imu->gyr.yaw);
  Serial.println("");
}