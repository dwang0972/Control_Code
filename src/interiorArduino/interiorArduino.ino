// Control code for arduino talking with i2c sensors
// Removes need for bit banging on cRIO
//

#include "I2Cdev.h"
#include "MPU6050.h"
#include "SFE_BMP180.h"
#include "Wire.h"

// MPU6050's
MPU6050 MPU6050_1(0x68);

// MPU6050 Data
int16_t MD_1[6];
int t16 = sizeof(int16_t);

// BMP180 i2c addresses
SFE_BMP180 BMP180_1;

// BMP180 Data
double BD_1[2];
char st;

// Analog Outs
int ap[] = {9, 10, 11, 12};

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Initialize devices
  Serial.println("Initializing I2C devices...");
  
  while (!BMP180_1.begin()) {
    Serial.println("BMP180 init fail");
    delay(500);
  }
  Serial.println("BMP180 init success");
  
  MPU6050_1.initialize();
  while (!MPU6050_1.testConnection()) {
    Serial.println("MPU6050_1 init fail");
    delay(500);
    MPU6050_1.initialize();
  }
  Serial.println("MPU6050_1 init success");
} 

void loop() {
  // Get BMP180 Temperature
  st = BMP180_1.startTemperature();
  if (st != 0) {
    delay(st);
    st = BMP180_1.getTemperature(BD_1[0]);
    if (st == 0) {
      Serial.println("error retrieving temperature measurement\n");
    }
  } else {
    Serial.println("error starting temperature measurement\n");
  }

  // Get BMP180 Pressure
  st = BMP180_1.startPressure(3);
  if (st != 0) {
    delay(st);
    st = BMP180_1.getPressure(BD_1[1],BD_1[0]);
    if (st == 0) {
      Serial.println("error retrieving pressure measurement\n");
    }
  } else {
    Serial.println("error starting pressure measurement\n");
  }

  // Get MPU6050 Data
  // Can also use getAcceleration(&ax, &ay, &az) and getRotation(&gx, &gy, &gz)
  // Or ax = getAccelerationX(), gx = getRotationX(), etc. etc.
  //MPU6050_1.getMotion6(MD_1, MD_1+t16, MD_1+(2*t16), MD_1+(3*t16), MD_1+(4*t16), MD_1+(5*t16));
  MD_1[0] = MPU6050_1.getAccelerationX();
  MD_1[1] = MPU6050_1.getAccelerationY();

  // Output Data
  analogWrite(ap[0], MD_1[0]);
  analogWrite(ap[1], MD_1[1]);
  analogWrite(ap[2], BD_1[0]);
  analogWrite(ap[3], BD_1[1]);

  // Pause
  delay(100);
}

