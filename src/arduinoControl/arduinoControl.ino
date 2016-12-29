// Control code for arduino talking with i2c sensors
// Removes need for bit banging on cRIO

#include <Wire.h>

const int MPU6050_i2c_addr1 = 0x68;

struct MPU6050_reg {
  byte MPU6050_RA_ACCEL_XOUT_H     0x3B
  byte MPU6050_RA_ACCEL_XOUT_L     0x3C
  byte MPU6050_RA_ACCEL_YOUT_H     0x3D
  byte MPU6050_RA_ACCEL_YOUT_L     0x3E
  byte MPU6050_RA_ACCEL_ZOUT_H     0x3F
  byte MPU6050_RA_ACCEL_ZOUT_L     0x40
  byte MPU6050_RA_TEMP_OUT_H       0x41
  byte MPU6050_RA_TEMP_OUT_L       0x42
  byte MPU6050_RA_GYRO_XOUT_H      0x43
  byte MPU6050_RA_GYRO_XOUT_L      0x44
  byte MPU6050_RA_GYRO_YOUT_H      0x45
  byte MPU6050_RA_GYRO_YOUT_L      0x46
  byte MPU6050_RA_GYRO_ZOUT_H      0x47
  byte MPU6050_RA_GYRO_ZOUT_L      0x48
};

// Write val to reg
void i2c_write(int addr, int reg, int val) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission(true);
}

// Read int8_t into data[]
void i2c_read(uint8_t addr, uint8_t startReg, int8_t data[], uint8_t numReads) {
  Wire.beginTransmission(addr);
  Wire.write(startReg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, numReads, true);
  for (int i = 0; i < numReads; i++) {
    data[i] = Wire.read();
  }
}

// Reads two int8_t's into a single int16_t data[]
void i2c_read2(uint8_t addr, uint8_t startReg, int16_t data[], uint8_t numReads) {
  Wire.beginTransmission(addr);
  Wire.write(startReg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, numReads, true);
  for (int i = 0; i < numReads; i++) {
    data[i] = (Wire.read() << 8) | Wire.read();
  }
}

void setup() {
  Wire.begin();
  i2c_write(MPU6050_i2c_addr1, 0x6B, 0); // Set MPU6050 Power Register
  Serial.begin(9600);
}

