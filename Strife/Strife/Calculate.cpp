#include "Arduino.h"
#include "Calculate.h"

double Calculate::calcThrust(float vehicleMass, float accel) {
  thrust = vehicleMass * (g * accel) - (vehicleMass * g);
  return thrust;
}

float Calculate::calcMin(float normalMinPos, float otherAxicsAngle, float otherMinPos, float otherMaxPos) {  
  //1. Convert the other axics angle on the other MinPos to MaxPos range to a 0,90 range Value for the cos function doing liniar regresion
  //m =
  //y2 - y1
  //-------
  //x2 - x1

  m = (otherMinPos - 0)/(otherMaxPos - 90);

  //t = y2 - m*x2
  float t = 90 - m*otherMaxPos;

  //conV = m*otherAxicsAngle + t the second part is a liniar Plot that converts a min - max Pos value to a 0, 90 pos value 
  conVal = m*otherAxicsAngle + t;
  //Return the normal min pos multiplied by the cos of the convertet value
  //(the cos of the convertet value function returns a value from 0 - 1 being 0 when otheraxics angle is at its maximum)
  //Because the airframe is perfectly round the dynamic Max pos wuld be midPos + (midPos - dynamicMinPos)
  //but i dont know how to return two values so we will just do this for max again 
  return normalMinPos * (cos(conVal)); 
}

float Calculate::calcMax(float normalMaxPos, float otherAxicsAngle, float otherMaxPos, float otherMinPos) {  
  //1. Convert the other axics angle on the other MinPos to MaxPos range to a 0,90 range Value for the cos function doing liniar regresion
  //m =
  //y2 - y1
  //-------
  //x2 - x1

  m = (otherMinPos - 0)/(otherMaxPos - 90);

  //t = y2 - m*x2
  float t = 90 - m*otherMaxPos;

  //conV = m*otherAxicsAngle + t the second part is a liniar Plot that converts a min - max Pos value to a 0, 90 pos value 
  conVal = m*otherAxicsAngle + t;
  //Return the normal min pos multiplied by the cos of the convertet value
  return normalMaxPos * (cos(conVal)); 
}
