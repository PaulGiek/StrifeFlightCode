#include "stateMachine.h"

void StateMachine::detectLiftoff(float accelX) {
  if(fabs((accelX / g)) > 1.6 && state == 0) {   
    state = 1;    //POWERED FLIGHT 
    statusMessage = 1;
    digitalWrite(LED,LOW);
    alpha = 1;
  }
}

void StateMachine::detectApogee(float totalAccelVector) {
  if(fabs((totalAccelVector / g)) < 0.05 && state == 1) {
    state = 2;      //RAPID DESCEND
    statusMessage = 2;
    digitalWrite(LED,HIGH);
  }
}

void StateMachine::detectParachuteHeight(double altitude_m) {
  if(altitude_m < parachuteHeight && state == 2) {
    recovery.deploy(1);
    state = 3;      //Deploying Chutes 
    statusMessage = 3;
  }
}

void StateMachine::detectParachuteOpening(float totalAccelVector) {
  if (fabs((totalAccelVector / g) < 0.7) && state == 3) {
    state = 4; //Falling with Chutes
  }
  
}

void StateMachine::detectTouchdown(float totalAccelVector) {
  if(fabs((totalAccelVector / g)) > 0.8 && state == 3) {
    state = 5;      //(SAFE) ON GROUND
    statusMessage = 5;
  }
}

void StateMachine::update(float accelX, float accelY, float accelZ, float altitude_m) {
  totalAccelVector = accelX + accelY + accelZ;
  detectLiftoff(accelX);
  detectApogee(totalAccelVector);
  detectParachuteHeight(altitude_m);
  detectParachuteOpening(totalAccelVector);
  detectTouchdown(totalAccelVector);
}
