#include "Arduino.h"
#include "IMU.h"

#include <Wire.h>

void IMU::init(){
  Wire.beginTransmission(0b1101000); //This is the I2C address of the MPU (b1101000/b1101001 for AC0 low/high datasheet sec. 9.2)
  Wire.write(0x6B); //Accessing the register 6B - Power Management (Sec. 4.28)
  Wire.write(0b00000000); //Setting SLEEP register to 0. (Required; see Note on p. 9)
  Wire.endTransmission();  
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1B); //Accessing the register 1B - Gyroscope Configuration (Sec. 4.4) 
  Wire.write(0x00000000); //Setting the gyro to full scale +/- 250deg./s 
  Wire.endTransmission(); 
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x1C); //Accessing the register 1C - Acccelerometer Configuration (Sec. 4.5) 
  Wire.write(0b00010000); //Setting the accel to +/- 8g and activate Selftest
  //Bits :    76543210
  Wire.endTransmission();
  
  calibrateGyro();
  MPUInitSC = true;
}

void IMU::getAccelData() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x3B); //Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Accel Registers (3B - 40)
  while(Wire.available() < 6);
  accelRawX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  accelRawY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  accelRawZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  gForceX = (((float) accelRawX) / 4096);
  gForceY = (((float) accelRawY) / 4096);
  gForceZ = (((float) accelRawZ) / 4096);
}

void IMU::processAccelData() {
  getAccelData();
   
  //Get m/s2 from g's
  accelX = gForceX * g;
  accelY = gForceY * g;
  accelZ = gForceZ * g;
  
  //TOTAL ACCEL 
  //Multipliing with it self to get rid of negativ Numbers
  float totalAccel = sqrt((accelX*accelX) + (accelY*accelY) + (accelZ*accelZ));
  //Calculate Angles from Acceleration
  // Y rotation with x
  accAngleY = asin(accelZ/totalAccel);
  //Deviding by totalAccel and not by g bc in case we read more than 1g we also devide by more that 1g
  
  // Z rotation with x and y
  accAngleZ = asin(accelY/totalAccel);
  //Deviding by totalAccel and not by g bc in case we read more than 1g we also devide by more that 1g
  //NOTE:
  //You Can't calculate x usind this methode --> x is Roll and not needed

  //Calculated angles from rad to degrees
  accAngleY *= rad2deg;
  accAngleZ *= rad2deg;

  //accAngleY -= 90;
  //Subtract 90 because 90 degrees is upright and supposed to be 0
}

void IMU::getGyroData() {
  Wire.beginTransmission(0b1101000); //I2C address of the MPU
  Wire.write(0x43); //Starting register for Gyro Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6); //Request Gyro Registers (43 - 48)
  while(Wire.available() < 6);
  gyroRawX = Wire.read()<<8|Wire.read(); //Store first two bytes into accelX
  gyroRawY = Wire.read()<<8|Wire.read(); //Store middle two bytes into accelY
  gyroRawZ = Wire.read()<<8|Wire.read(); //Store last two bytes into accelZ
  dt = (millis() - millisOld)/1000.0;
  millisOld = millis();
}

void IMU::processGyroData() {
  getGyroData();
  
  //Complimentary Filter
  gyroX = (rotOldY + ((float) gyroRawX)/131.0 * dt);
  gyroY = (rotOldY + ((float) gyroRawY)/131.0 * dt);
  gyroZ = (rotOldZ + ((float) gyroRawZ)/131.0 * dt);

  //Gyro adds to up to the old filtered value so when we switch from accel to gyro orientation the measured accel angle gets taken over and added on.
  rotOldX = gyroX;
  rotOldY = gyroY;
  rotOldZ = gyroZ;

  //Subtract the drift 
  //The drift is give in deg/ms so multipling with millis() will return how far we drifted in deg.
  //This value then needs to be subtracted from rotY/Z
  gyroX -= (driftX * millis()/1000);
  gyroY -= (driftY * millis()/1000);
  gyroZ -= (driftZ * millis()/1000);
    
}

void IMU::getTemperatureData() {
  temperature = Wire.read()<<8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
}

void IMU::updateData() {
  processGyroData();
  processAccelData();
  getTemperatureData();

  //printData();
  //Write either teh accel or gyro calculatet orientation in the filtered variables
  rotFilteredX = gyroX;
  rotFilteredY = alpha * gyroY + (1 - alpha) * accAngleY;
  rotFilteredZ = alpha * gyroZ + (1 - alpha) * accAngleZ;
}


void IMU::calibrateGyro() {
  //REQUIRES SETUP_MPU TO BE COMPLETED
  
  for(int i = 1; i < gyroCalCount + 1; i++) {
    processAccelData();

    rocketOffsetByAccelY += accAngleY;          
    rocketOffsetByAccelZ += accAngleZ;
  }

  rocketOffsetByAccelY /= gyroCalCount;
  rocketOffsetByAccelZ /= gyroCalCount;
  
  gyroY += rocketOffsetByAccelY;
  gyroZ += rocketOffsetByAccelZ;
}


void IMU::printData() {
  //Serial.print("Filtered: ");     //Comment this out in case you want to plot 
  Serial.print(rotFilteredX);
  Serial.print(",");
  Serial.print(rotFilteredY);
  Serial.print(",");
  Serial.println(rotFilteredZ);
}
