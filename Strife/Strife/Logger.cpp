#include "Logger.h"
#include <SD.h>
#include <SPI.h>

File logger_file;
File config_file;

void Logger::init() {
    pinMode(pinCS, OUTPUT);
  
    // SD Card Initialization
    if (SD.begin()) {
        digitalWrite(LEDG, HIGH);
        sd = true;
        //Serial.println("SD card is ready to use.");
    } 
    else {
        sd = false;
        //Serial.println("SD card initialization failed");
    }
}


void Logger::writePackage(Package package, String filePath) {
    // CreateOpen file 
    logger_file = SD.open(filePath, FILE_WRITE);
    // if the file opened okay, write to it:
    if (logger_file) {
        String data = (String)millis() + ";" + (String)package.state + ";" + (String)package.altitude + ";" + (String)package.rotX + ";" + (String)package.rotY + ";" + (String)package.rotZ + ";" + (String)package.accelX + ";" + (String)package.accelY + ";" + (String)package.accelZ + ";" + (String)package.uY + ";" + (String)package.uZ;
        logger_file.println(data);
        logger_file.close(); // close the file
    }
    // if the file didn't open, print an error:
    else {
      digitalWrite(LEDG, LOW);
    }
}

void Logger::readConfig(){
  config_file = SD.open("CONFIG.txt");
  if (config_file) {
    while (config_file.available() && i <=5) {
      for (int i = 0; i <= 5; i++){
        values[i] = config_file.parseFloat();
      }
    }
    config_file.close();
  } 
  else {
    // if the file didn't open, print an error:
    //Serial.println("error opening test.txt");
    configReadSucces = false;
  }

  KpYlogger = values[0];
  KiYlogger = values[1];
  KdYlogger = values[2];
    
  KpZlogger = values[3];
  KiZlogger = values[4];
  KdZlogger = values[5];
  configReadSucces = true;
 }  
