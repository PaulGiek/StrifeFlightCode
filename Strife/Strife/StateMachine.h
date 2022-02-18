#ifndef StateMachine_h
#define StateMachine_h

#include "Arduino.h"
#include "Parachute.h"

class StateMachine {
  public:
    int state = 0;
    float alpha = 0;
    
    void update(float accelX, float accelY, float accelZ, float altitude_m);
    const float g = 9.80665;
    
  private:
    Parachute recovery;
    const int LED = 8;
    float totalAccelVector = 0;
    int parachuteHeight = 50;
    int statusMessage = 0; 

    //Liftoff Detection Variables
    const float initLiftoffThreshold = 1.5;
    float initAccelX;

    void detectLiftoff(float totalAccelVector);
    void detectApogee(float totalAccelVector);
    void detectParachuteHeight(double altitude_m);
    void detectParachuteOpening(float totalAccelVector);
    void detectTouchdown(float totalAccelVector);
};
#endif
