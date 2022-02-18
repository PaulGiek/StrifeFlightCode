#ifndef Altitude_h
#define Altitude_h

#include "Arduino.h"
#include <Adafruit_BMP085.h>

class BMP {
  public:
    float altitude;
    void init();
    void filterValues(); 
    bool BMPInitSC = false;
    
  private:
    Adafruit_BMP085 Bmp;
    float baseline = 0;
    float addedbaseline = 0;
    float altitudeRaw;
    float altitudeOld = 0;
    float calCount = 100;

    
 
};
#endif Altitude_h
