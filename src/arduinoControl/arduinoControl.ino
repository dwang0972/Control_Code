// Control code for arduino talking with i2c sensors
// Removes need for bit banging on cRIO

#include <Wire.h>

// MPU6050 i2c addresses
const int MPU6050_ADDR_1 = 0x68;
const int MPU6050_ADDR_2 = 0x68;

// MPU6050 Registers
typedef enum {
//  MPU6050_ADDRESS 0b11010010 // Address with end write bit
  MPU6050_RA_XG_OFFS_TC         = 0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
  MPU6050_RA_YG_OFFS_TC         = 0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
  MPU6050_RA_ZG_OFFS_TC         = 0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
  MPU6050_RA_X_FINE_GAIN        = 0x03 //[7:0] X_FINE_GAIN
  MPU6050_RA_Y_FINE_GAIN        = 0x04 //[7:0] Y_FINE_GAIN
  MPU6050_RA_Z_FINE_GAIN        = 0x05 //[7:0] Z_FINE_GAIN
  MPU6050_RA_XA_OFFS_H          = 0x06 //[15:0] XA_OFFS
  MPU6050_RA_XA_OFFS_L_TC       = 0x07
  MPU6050_RA_YA_OFFS_H          = 0x08 //[15:0] YA_OFFS
  MPU6050_RA_YA_OFFS_L_TC       = 0x09
  MPU6050_RA_ZA_OFFS_H          = 0x0A //[15:0] ZA_OFFS
  MPU6050_RA_ZA_OFFS_L_TC       = 0x0B
  MPU6050_RA_XG_OFFS_USRH       = 0x13 //[15:0] XG_OFFS_USR
  MPU6050_RA_XG_OFFS_USRL       = 0x14
  MPU6050_RA_YG_OFFS_USRH       = 0x15 //[15:0] YG_OFFS_USR
  MPU6050_RA_YG_OFFS_USRL       = 0x16
  MPU6050_RA_ZG_OFFS_USRH       = 0x17 //[15:0] ZG_OFFS_USR
  MPU6050_RA_ZG_OFFS_USRL       = 0x18
  MPU6050_RA_SMPLRT_DIV         = 0x19
  MPU6050_RA_CONFIG             = 0x1A
  MPU6050_RA_GYRO_CONFIG        = 0x1B
  MPU6050_RA_ACCEL_CONFIG       = 0x1C
  MPU6050_RA_FF_THR             = 0x1D
  MPU6050_RA_FF_DUR             = 0x1E
  MPU6050_RA_MOT_THR            = 0x1F
  MPU6050_RA_MOT_DUR            = 0x20
  MPU6050_RA_ZRMOT_THR          = 0x21
  MPU6050_RA_ZRMOT_DUR          = 0x22
  MPU6050_RA_FIFO_EN            = 0x23
  MPU6050_RA_I2C_MST_CTRL         = 0x24
  MPU6050_RA_I2C_SLV0_ADDR        = 0x25
  MPU6050_RA_I2C_SLV0_REG         = 0x26
  MPU6050_RA_I2C_SLV0_CTRL        = 0x27
  MPU6050_RA_I2C_SLV1_ADDR        = 0x28
  MPU6050_RA_I2C_SLV1_REG         = 0x29
  MPU6050_RA_I2C_SLV1_CTRL        = 0x2A
  MPU6050_RA_I2C_SLV2_ADDR        = 0x2B
  MPU6050_RA_I2C_SLV2_REG         = 0x2C
  MPU6050_RA_I2C_SLV2_CTRL        = 0x2D
  MPU6050_RA_I2C_SLV3_ADDR        = 0x2E
  MPU6050_RA_I2C_SLV3_REG         = 0x2F
  MPU6050_RA_I2C_SLV3_CTRL        = 0x30
  MPU6050_RA_I2C_SLV4_ADDR        = 0x31
  MPU6050_RA_I2C_SLV4_REG         = 0x32
  MPU6050_RA_I2C_SLV4_DO          = 0x33
  MPU6050_RA_I2C_SLV4_CTRL        = 0x34
  MPU6050_RA_I2C_SLV4_DI          = 0x35
  MPU6050_RA_I2C_MST_STATUS       = 0x36
  MPU6050_RA_INT_PIN_CFG          = 0x37
  MPU6050_RA_INT_ENABLE           = 0x38
  MPU6050_RA_DMP_INT_STATUS       = 0x39
  MPU6050_RA_INT_STATUS           = 0x3A
  MPU6050_RA_ACCEL_XOUT_H         = 0x3B
  MPU6050_RA_ACCEL_XOUT_L         = 0x3C
  MPU6050_RA_ACCEL_YOUT_H         = 0x3D
  MPU6050_RA_ACCEL_YOUT_L         = 0x3E
  MPU6050_RA_ACCEL_ZOUT_H         = 0x3F
  MPU6050_RA_ACCEL_ZOUT_L         = 0x40
  MPU6050_RA_TEMP_OUT_H           = 0x41
  MPU6050_RA_TEMP_OUT_L           = 0x42
  MPU6050_RA_GYRO_XOUT_H          = 0x43
  MPU6050_RA_GYRO_XOUT_L          = 0x44
  MPU6050_RA_GYRO_YOUT_H          = 0x45
  MPU6050_RA_GYRO_YOUT_L          = 0x46
  MPU6050_RA_GYRO_ZOUT_H          = 0x47
  MPU6050_RA_GYRO_ZOUT_L          = 0x48
  MPU6050_RA_EXT_SENS_DATA_00     = 0x49
  MPU6050_RA_EXT_SENS_DATA_01     = 0x4A
  MPU6050_RA_EXT_SENS_DATA_02     = 0x4B
  MPU6050_RA_EXT_SENS_DATA_03     = 0x4C
  MPU6050_RA_EXT_SENS_DATA_04     = 0x4D
  MPU6050_RA_EXT_SENS_DATA_05     = 0x4E
  MPU6050_RA_EXT_SENS_DATA_06     = 0x4F
  MPU6050_RA_EXT_SENS_DATA_07     = 0x50
  MPU6050_RA_EXT_SENS_DATA_08     = 0x51
  MPU6050_RA_EXT_SENS_DATA_09     = 0x52
  MPU6050_RA_EXT_SENS_DATA_10     = 0x53
  MPU6050_RA_EXT_SENS_DATA_11     = 0x54
  MPU6050_RA_EXT_SENS_DATA_12     = 0x55
  MPU6050_RA_EXT_SENS_DATA_13     = 0x56
  MPU6050_RA_EXT_SENS_DATA_14     = 0x57
  MPU6050_RA_EXT_SENS_DATA_15     = 0x58
  MPU6050_RA_EXT_SENS_DATA_16     = 0x59
  MPU6050_RA_EXT_SENS_DATA_17     = 0x5A
  MPU6050_RA_EXT_SENS_DATA_18     = 0x5B
  MPU6050_RA_EXT_SENS_DATA_19     = 0x5C
  MPU6050_RA_EXT_SENS_DATA_20     = 0x5D
  MPU6050_RA_EXT_SENS_DATA_21     = 0x5E
  MPU6050_RA_EXT_SENS_DATA_22     = 0x5F
  MPU6050_RA_EXT_SENS_DATA_23     = 0x60
  MPU6050_RA_MOT_DETECT_STATUS    = 0x61
  MPU6050_RA_I2C_SLV0_DO          = 0x63
  MPU6050_RA_I2C_SLV1_DO          = 0x64
  MPU6050_RA_I2C_SLV2_DO          = 0x65
  MPU6050_RA_I2C_SLV3_DO          = 0x66
  MPU6050_RA_I2C_MST_DELAY_CTRL   = 0x67
  MPU6050_RA_SIGNAL_PATH_RESET    = 0x68
  MPU6050_RA_MOT_DETECT_CTRL      = 0x69
  MPU6050_RA_USER_CTRL            = 0x6A
  MPU6050_RA_PWR_MGMT_1           = 0x6B
  MPU6050_RA_PWR_MGMT_2           = 0x6C
  MPU6050_RA_BANK_SEL             = 0x6D
  MPU6050_RA_MEM_START_ADDR       = 0x6E
  MPU6050_RA_MEM_R_W              = 0x6F
  MPU6050_RA_DMP_CFG_1            = 0x70
  MPU6050_RA_DMP_CFG_2            = 0x71
  MPU6050_RA_FIFO_COUNTH          = 0x72
  MPU6050_RA_FIFO_COUNTL          = 0x73
  MPU6050_RA_FIFO_R_W             = 0x74
  MPU6050_RA_WHO_AM_I             = 0x75
}

// MPU6050 Data
int16_t MPU6050_DATA_1[7];
int16_t MPU6050_DATA_2[7];

// BMP180 i2c addresses
const int BMP180_ADDR_1 = 0x77;
const int BMP180_ADDR_2 = 0x77;

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
int8_t BMP180_DATA_T_2[3];
int8_t BMP180_DATA_P_2[3];

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

  //SETUP 1st MPU6050
  // Reset MPU6050 device, reset registers
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_PWR_MGMT_1, 0b10000000); //bit 7 set to 1 resets device
  delay(100);
  //Sets clock source to gyro reference w/ PLL
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_PWR_MGMT_1, 0b00000010);
  //Controls frequency of wakeups in accel low power mode plus the sensor standby modes
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_PWR_MGMT_2, 0x00);
  //Sets sample rate to 8000/1+7 = 1000Hz
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_SMPLRT_DIV, 0x07);
  //Disable FSync, 256Hz DLPF
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_CONFIG, 0x00);
  //Disable gyro self tests, scale of 500 degrees/s
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_GYRO_CONFIG, 0b00001000);
  //Disable accel self tests, scale of +-4g, no DHPF
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_ACCEL_CONFIG, 0x01);
  //Freefall threshold of |0mg|
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_FF_THR, 0x00);
  //Freefall duration limit of 0
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_FF_DUR, 0x00);
  //Motion threshold of 0mg
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_MOT_THR, 0x00);
  //Motion duration of 0s
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_MOT_DUR, 0x00);
  //Zero motion threshold
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_ZRMOT_THR, 0x00);
  //Zero motion duration threshold
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_ZRMOT_DUR, 0x00);
  //Disable sensor output to FIFO buffer
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_FIFO_EN, 0x00);

  //Setup INT pin and AUX I2C pass through
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_INT_PIN_CFG, 0x00);
  //Enable data ready interrupt
  i2c_write(MPU6050_ADDR_1, MPU6050_RA_INT_ENABLE, 0x00);

//  //AUX I2C setup
//  //Sets AUX I2C to single master control, plus other config
//  i2c_write(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, 0x00);
//  //Setup AUX I2C slaves
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV0_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV0_REG, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV0_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV1_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV1_REG, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV1_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV2_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV2_REG, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV2_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV3_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV3_REG, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV3_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV4_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV4_REG, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV4_DO, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV4_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV4_DI, 0x00);

//  //Slave out, dont care
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV0_DO, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV1_DO, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV2_DO, 0x00);
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_SLV3_DO, 0x00);
//  //More slave config
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
//  //Reset sensor signal paths
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
//  //Motion detection control
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_MOT_DETECT_CTRL, 0x00);
//  //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_USER_CTRL, 0x00);
//  //Data transfer to and from FIFO buffer
//  i2c_write(MPU6050_ADDR_1, MPU6050_RA_FIFO_R_W, 0x00);

  // ---------------------------- // 

  //Setup 2nd MPU6050
  // Reset MPU6050 devie, reset registers
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_PWR_MGMT_1, 0b10000000); //bit 7 set to 1 resets device
  delay(100);
  //Sets clock source to gyro reference w/ PLL - defaults to internal 8MHz oscillator
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_PWR_MGMT_1, 0b00000010);
  //Controls frequency of wakeups in accel low power mode plus the sensor standby modes - this can be adjusted (see RM for MPU6050)
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_PWR_MGMT_2, 0x00);
  //Sets sample rate to 8000/1+7 = 1000Hz
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_SMPLRT_DIV, 0x07);
  //Disable FSync, 256Hz DLPF
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_CONFIG, 0x00);
  //Disable gyro self tests, scale of 500 degrees/s
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_GYRO_CONFIG, 0b00001000);
  //Disable accel self tests, scale of +-4g, no DHPF
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_ACCEL_CONFIG, 0x01);
  //Freefall threshold of |0mg|
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_FF_THR, 0x00);
  //Freefall duration limit of 0
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_FF_DUR, 0x00);
  //Motion threshold of 0mg
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_MOT_THR, 0x00);
  //Motion duration of 0s
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_MOT_DUR, 0x00);
  //Zero motion threshold
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_ZRMOT_THR, 0x00);
  //Zero motion duration threshold
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_ZRMOT_DUR, 0x00);
  //Disable sensor output to FIFO buffer
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_FIFO_EN, 0x00);

  //Setup INT pin and AUX I2C pass through
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_INT_PIN_CFG, 0x00);
  //Enable data ready interrupt
  i2c_write(MPU6050_ADDR_2, MPU6050_RA_INT_ENABLE, 0x00);

//  //AUX I2C setup
//  //Sets AUX I2C to single master control, plus other config
//  i2c_write(MPU6050_ADDRESS, MPU6050_RA_I2C_MST_CTRL, 0x00);
//  //Setup AUX I2C slaves
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV0_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV0_REG, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV0_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV1_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV1_REG, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV1_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV2_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV2_REG, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV2_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV3_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV3_REG, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV3_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV4_ADDR, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV4_REG, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV4_DO, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV4_CTRL, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV4_DI, 0x00);
//
//  //Slave out, dont care
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV0_DO, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV1_DO, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV2_DO, 0x00);
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_SLV3_DO, 0x00);
//  //More slave config
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_I2C_MST_DELAY_CTRL, 0x00);
//  //Reset sensor signal paths
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_SIGNAL_PATH_RESET, 0x00);
//  //Motion detection control
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_MOT_DETECT_CTRL, 0x00);
//  //Disables FIFO, AUX I2C, FIFO and I2C reset bits to 0
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_USER_CTRL, 0x00);
//  //Data transfer to and from FIFO buffer
//  i2c_write(MPU6050_ADDR_2, MPU6050_RA_FIFO_R_W, 0x00);
  
  Serial.begin(9600);
} 

void loop() {
  i2c_read2(MPU6050_ADDR_1, MPU6050_REG::MPU6050_RA_ACCEL_XOUT_H, MPU6050_DATA_1, 7);
  i2c_read2(MPU6050_ADDR_2, MPU6050_REG::MPU6050_RA_ACCEL_XOUT_H, MPU6050_DATA_2, 7);
  i2c_read(BMP180_ADDR_1, BMP180_REG::BMP180_COMMAND_TEMPERATURE, BMP180_DATA_T_1, 2);
  i2c_read(BMP180_ADDR_2, BMP180_REG::BMP180_COMMAND_TEMPERATURE, BMP180_DATA_T_2, 2);
  i2c_read(BMP180_ADDR_1, BMP180_REG::BMP180_COMMAND_PRESSURE0, BMP180_DATA_P_1, 3);
  i2c_read(BMP180_ADDR_2, BMP180_REG::BMP180_COMMAND_PRESSURE0, BMP180_DATA_P_2, 3);
  delay(500);
}

