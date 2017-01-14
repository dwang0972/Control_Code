// Control code for arduino talking with i2c sensors
// Removes need for bit banging on cRIO
//

#include <Wire.h>

// MPU6050 i2c addresses
const int MPU6050_ADDR_1 = 0x68;
const int MPU6050_ADDR_2 = 0x68;

// MPU6050 Registers
typedef enum {
  MPU6050_RA_ACCEL_XOUT_H     = 0x3B,
  MPU6050_RA_ACCEL_XOUT_L     = 0x3C,
  MPU6050_RA_ACCEL_YOUT_H     = 0x3D,
  MPU6050_RA_ACCEL_YOUT_L     = 0x3E,
  MPU6050_RA_ACCEL_ZOUT_H     = 0x3F,
  MPU6050_RA_ACCEL_ZOUT_L     = 0x40,
  MPU6050_RA_TEMP_OUT_H       = 0x41,
  MPU6050_RA_TEMP_OUT_L       = 0x42,
  MPU6050_RA_GYRO_XOUT_H      = 0x43,
  MPU6050_RA_GYRO_XOUT_L      = 0x44,
  MPU6050_RA_GYRO_YOUT_H      = 0x45,
  MPU6050_RA_GYRO_YOUT_L      = 0x46,
  MPU6050_RA_GYRO_ZOUT_H      = 0x47,
  MPU6050_RA_GYRO_ZOUT_L      = 0x48,
  MPU6050_RA_PWR_MGMT_1       = 0x6B,
  MPU6050_RA_PWR_MGMT_2       = 0x6C
} MPU6050_REG;

// MPU6050 Data
int16_t MPU6050_DATA_1[7];
int16_t MPU6050_DATA_2[7];

// BMP180 i2c addresses
const int BMP180_ADDR_1 = 0x77;
// const int BMP180_ADDR_2 = 0x77; // Only using one

// BMP180 Registers
typedef enum {
  BMP180_REG_CONTROL          = 0xF4,
  BMP180_REG_RESULT           = 0xF6,
  BMP180_COMMAND_TEMPERATURE  = 0x2E,
  BMP180_COMMAND_PRESSURE0    = 0x34,
  BMP180_COMMAND_PRESSURE1    = 0x74, // Oversampling pressure (1)
  BMP180_COMMAND_PRESSURE2    = 0xB4, // Oversampling pressure (2)
  BMP180_COMMAND_PRESSURE3    = 0xF4  // Oversampling pressure (3)
} BMP180_REG;

// BMP180 Data
int8_t BMP180_DATA_T_1[2];
int8_t BMP180_DATA_P_1[2];
//int8_t BMP180_DATA_T_2[3];
//int8_t BMP180_DATA_P_2[3];

// Write val to reg
void i2c_write(int addr, int reg, int val) {
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission(true);
}

// Read int8_t into data[]
void i2c_read(int addr, int startReg, int8_t data[], int numReads) {
  Wire.beginTransmission(addr);
  Wire.write(startReg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, numReads, true);
  for (int i = 0; i < numReads; i++) {
    data[i] = Wire.read();
  }
}

// Reads two int8_t registers (bytes) into a single int16_t data[]
// For MPU6050 reads the high bits register then the low bits register
void i2c_read2(int addr, int startReg, int16_t data[], int numReads) {
  Wire.beginTransmission(addr);
  Wire.write(startReg);
  Wire.endTransmission(false);
  Wire.requestFrom(addr, 2*numReads, true);
  for (int i = 0; i < numReads; i++) {
    data[i] = (Wire.read() << 8) | Wire.read();
  }
}

void setup() {
  Wire.begin();
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_PWR_MGMT_1, 0); // Set MPU6050 at ADDR 1 Power Register
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_PWR_MGMT_1, 0); // Set MPU6050 at ADDR 2 Power Register
  Serial.begin(9600);
} 

void loop() {
  i2c_read2(MPU6050_ADDR_1, MPU6050_REG::MPU6050_RA_ACCEL_XOUT_H, MPU6050_DATA_1, 7);
  i2c_read2(MPU6050_ADDR_2, MPU6050_REG::MPU6050_RA_ACCEL_XOUT_H, MPU6050_DATA_2, 7);
  
  i2c_read(BMP180_ADDR_1, BMP180_REG::BMP180_COMMAND_TEMPERATURE, BMP180_DATA_T_1, 2);
  i2c_read(BMP180_ADDR_1, BMP180_REG::BMP180_COMMAND_PRESSURE0, BMP180_DATA_P_1, 3);
  
  //i2c_read(BMP180_ADDR_2, BMP180_REG::BMP180_COMMAND_TEMPERATURE, BMP180_DATA_T_2, 2);
  //i2c_read(BMP180_ADDR_2, BMP180_REG::BMP180_COMMAND_PRESSURE0, BMP180_DATA_P_2, 3);

  for (int i = 0; i < 7; i++) {
    Serial.print("MPU1: ");
    Serial.println(MPU6050_DATA_1[i]);
    Serial.print("MPU2: ");
    Serial.println(MPU6050_DATA_2[i]);
  }

  for (int i = 0; i < 2; i++) {
    Serial.print("BMPT: ");
    Serial.println(BMP180_DATA_T_1[i]);
  }

  for (int i = 0; i < 3; i++) {
    Serial.print("BMPP: ");
    Serial.println(BMP180_DATA_P_1[i]);
  }
  
  delay(500);
}

