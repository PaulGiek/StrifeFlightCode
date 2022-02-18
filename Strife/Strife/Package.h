#ifndef Package_h
#define Package_h

#include "Arduino.h"

struct Package {
  float state;
  float altitude;
  float temperature;
  float rotX;
  float rotY;
  float rotZ;
  float accelX;
  float accelY;
  float accelZ;
  float uY;
  float uZ;
};

#endif
