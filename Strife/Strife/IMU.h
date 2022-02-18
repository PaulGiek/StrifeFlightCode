#ifndef IMU_h
#define IMU_h

#include "Arduino.h"
#include <Wire.h>

class IMU {
  public:
    //VARIABLES
    bool MPUInitSC = false;
    
    // Accel Oreientation Variables
    float gForceX, gForceY, gForceZ;
    float accAngleZ, accAngleY;
    float accelX, accelY, accelZ; //For Accel in m/s2

    float temperature;
    
    //Filtered values 
    float rotFilteredX, rotFilteredY, rotFilteredZ = 0;
    
    float alpha = 0.5;

    //FUNCTIONS
    void updateData();
    void printData();
    void init();

  private:     
    //VARIABLES 
    // Accel Oreientation Variables
    const float g = 9.80665;
    
    int16_t accelRawX, accelRawY, accelRawZ;

    const float rad2deg = 57.2957795;

    //Gyro Orient
    //Calibrate Gyro
    float rocketOffsetByAccelY = 0;
    float rocketOffsetByAccelZ = 0;

    int gyroCalCount = 2000;

    float driftX = 0.00;
    float driftY = -0.53;
    float driftZ = -0.08;
    //Orientation
    int16_t gyroRawX, gyroRawY, gyroRawZ;
    float gyroX, gyroY, gyroZ = 0;

    //Filter the values 
    float rotOldX, rotOldY, rotOldZ = 0;
    
    //Variables for time
    unsigned long millisOld;
    float dt;
    
    //FUNCTIONS 
    void getAccelData();
    void processAccelData();

    void getGyroData();
    void processGyroData();

    void getTemperatureData();

    void calibrateGyro();
};
#endif
