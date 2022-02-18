#ifndef TLM_h
#define TLM_h

#include "Arduino.h"
#include "Package.h"

//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
extern RF24 Radio;  // CE, CSN

class TLM {
  public: 
    bool TLMInitSC = false;
    const byte address[6];
    
    TLM();

    void sendPackage(Package package);
    void init();
    void sendInitState(bool bmp, bool imu, bool sd, bool sdr);
};

#endif 
