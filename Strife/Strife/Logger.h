#ifndef Logger_h
#define Logger_h

#include "Arduino.h"
#include "Package.h"

#include <SD.h>
#include <SPI.h>

class Logger {
  public:
    bool sd = false;
    bool configReadSucces = false;
    int pinCS = 10;
  
    float KpYlogger;
    float KiYlogger;
    float KdYlogger;
    
    float KpZlogger;
    float KiZlogger;
    float KdZlogger;

    void readConfig();
    void writePackage(Package package, String filePath);
    void init();
  private:
     //Read Config
    int i = 0;
    byte buf[4];
    float values[6];
};
#endif
