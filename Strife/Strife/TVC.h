#ifndef TVC_h
#define TVC_h

#include "Arduino.h"
#include <Servo.h>


class TVC {
  public:
    void updateY(float rotY);
    void updateZ(float rotZ);

    void startUpTVC();

    float KpY = 1.0;
    float KiY = 0.0;
    float KdY = 0.2;
  
    float KpZ = 0.8;
    float KiZ = 0.0;
    float KdZ = 0.2;

    float uY;
    float uZ;

  private:
    //Servos
    Servo ServoY;
    Servo ServoZ;
    
    float CenterPosY = 90;
    float CenterPosZ = 90;

    float maxY = 100;
    float minY = 80;
  
    float maxZ = 100;
    float minZ = 80;


    float PIDy(float AngleY);
    float PIDz(float AngleZ);
    
    float TotalErrorY = 0;
    float TotalErrorZ = 0;

    const float GoalY = 0.0;
    const float GoalZ = 0.0;


    float ErrorY = 0;
    float ErrorZ = 0;

    float oldErrorY = 0;
    float oldErrorZ = 0;

    float oldTimeY = 0;
    float oldTimeZ = 0; 
};


#endif
