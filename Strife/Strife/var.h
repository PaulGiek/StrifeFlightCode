#ifndef var_h
#define var_h

#include <WiFiNINA.h>
/*Needed for the RGB LED because: 
The Nano RP2040 Connect uses the u-blox NINA-W102 module for Wi-Fi connectivity. 
But this module is also just a standard ESP32 microcontroller. 
No reason to let those precious GPIO pins go to waste. 
So the RGB LED is connected to the NINA module, 
rather than taking up the RP2040 pins. 
So in order to blink these LEDs it's necessary for the RP2040 to communicate with the NINA module. 
That communication is handled by the WiFiNINA library.
*/


#include "BMP.h"
#include "IMU.h"
#include "Logger.h"
#include "Calculate.h"
#include "StateMachine.h"
#include "TVC.h"
#include "TLM.h"
#include "Package.h"


TVC tvc;
BMP bmp;
IMU mpu;

TLM telemetry;
Logger logger;
Package package;

StateMachine stateMachine;
Calculate calc;


  
//Value Variables
float altitude;
 
float accelX;
float accelY;
float accelZ;

float rotX;
float rotY;
float rotZ;

float driftY = -0.53;
float driftZ = -0.08;

float temp = 0;

//Pin assignments
const int LED = 8;
const int powerSupplyPin = 7;

//Other Variables
float startTime = 0.0;

//File Log
const String LOG_FILE = "LOGGER.csv";

bool loggerSetupDone = false;

#endif 
