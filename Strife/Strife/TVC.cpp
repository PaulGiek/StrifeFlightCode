#include "TVC.h"

float TVC::PIDy(float AngleY) {
  float uy;
  unsigned long nowy;
  
  ErrorY = GoalY - AngleY; //Calculate the error
 
  TotalErrorY += ErrorY; //Calculate the Total offset of the entire run and add it to the Total i y 

  nowy = millis();

  if (oldTimeY == nowy) {
    nowy += 1;
  }
  
  //Add the Error multiplied by Kp to the total error and to the rotational speed of thr rocket multiplied by Kd  
  uy = KpY * ErrorY + KiY * TotalErrorY * (nowy - oldTimeY) + KdY * ((ErrorY - oldErrorY)/(nowy - oldTimeY));

  oldErrorY = ErrorY;
  oldTimeY = nowy;

  return uy;
}


float TVC::PIDz(float AngleZ) {
  float uz;
  unsigned long nowZ;
  
  ErrorZ = GoalZ - AngleZ; //Calculate the error
 
  TotalErrorZ += ErrorZ; //Calculate the Total offset of the entire run and add it to the Total i z 

  nowZ = millis();

  if (oldTimeZ == nowZ) {
    nowZ += 1;
  }
  
  //Add the Error multiplied by Kp to the total error and to the rotational speed of thr rocket multiplied by Kd  
  uz = KpZ * ErrorZ + KiZ * TotalErrorZ * (nowZ - oldTimeZ) + KdZ * ((ErrorZ - oldErrorZ)/(nowZ - oldTimeZ));

  oldErrorZ = ErrorZ;
  oldTimeZ = nowZ;

  return uz;
}

/*Do the Corrections 
Calculate the pid value and add/subtract the middle pos so the PID Value is going from the center POS*/
   
void TVC::updateY(float rotY) {
    uY = PIDy(rotY) + CenterPosY;    

    uY = constrain(uY, minY, maxY);
    ServoY.write(uY);
}

void TVC::updateZ(float rotZ) {
    uZ = PIDz(rotZ) + CenterPosZ;    

    uZ = constrain(uZ, minZ, maxZ);
    ServoZ.write(uZ);
}


void TVC::startUpTVC() {
  ServoY.attach(3);
  ServoZ.attach(5);
  
  ServoY.write(CenterPosY);
  ServoZ.write(CenterPosZ);

  delay(1000);
 
  ServoY.write(minY);
  delay(200);
  ServoY.write(CenterPosY);
  delay(200);
  
  ServoY.write(maxY);
  delay(200);
  ServoY.write(CenterPosY);
  delay(200);
  
  ServoZ.write(minZ);
  delay(200);
  ServoZ.write(CenterPosZ);
  delay(200);
  ServoZ.write(maxZ);
  delay(200);
  ServoZ.write(CenterPosZ);
  delay(600);

  ServoY.write(CenterPosY);
  ServoZ.write(CenterPosZ);
}
