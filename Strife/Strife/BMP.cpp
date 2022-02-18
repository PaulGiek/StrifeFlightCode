#include "Arduino.h"
#include <Adafruit_BMP085.h>
#include "BMP.h"

void BMP::init() {
  if (!Bmp.begin()) {
    while (1) {}
  }
  for (int i = 0; i < calCount; i++) {
    addedbaseline += Bmp.readAltitude(101500);
  }
  baseline = addedbaseline / calCount;
  BMPInitSC = true;
}

  
void BMP::filterValues() {
    altitudeRaw = Bmp.readAltitude(101500) - baseline;
    altitude = (altitudeOld / 2) + (altitudeRaw / 2);
    altitudeOld = altitudeRaw;
}
