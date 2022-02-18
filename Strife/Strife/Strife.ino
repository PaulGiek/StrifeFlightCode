#include "var.h"

void setup() { 
  Serial.begin(115200);
  while(!Serial);
  
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(powerSupplyPin, OUTPUT);

  
  digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(powerSupplyPin, LOW);
  digitalWrite(LED, LOW);

  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);

  
  //5min delay to get away from the rocket 
  //delay(300000);

  //Enable the power supply to supply power to the actuators and data logging module
  digitalWrite(powerSupplyPin, HIGH);

  telemetry.init();
  Serial.println("TLM Done");
  delay(200);
  
  
  bmp.init();
  
  mpu.init();
  mpu.alpha = 0;
  
   //SD Check
  logger.init();
     
  logger.readConfig();
  if (logger.configReadSucces) {
  //Transfer read values 
  tvc.KpY = logger.KpYlogger;
  tvc.KiY = logger.KiYlogger;
  tvc.KdY = logger.KdYlogger;
  
  tvc.KpZ = logger.KpZlogger; 
  tvc.KiZ = logger.KiZlogger;
  tvc.KpZ = logger.KdZlogger; 
  }
  
  tvc.startUpTVC();

  telemetry.sendInitState(bmp.BMPInitSC, mpu.MPUInitSC, logger.sd, logger.configReadSucces);
  Serial.println("All done");
  //If Rocket is ready turn Status LED on 
  if (bmp.BMPInitSC && mpu.MPUInitSC && logger.sd && logger.configReadSucces && telemetry.TLMInitSC) {
    digitalWrite(LED, HIGH);
  }
}


void loop() {
  getValues();
  
  if (stateMachine.state == 1) {
    tvc.updateY(rotY);
    tvc.updateZ(rotZ);
  }

  stateMachine.update(accelX,accelY,accelZ,altitude);
  mpu.alpha = stateMachine.alpha;
  
  //Log the current package and send it
  telemetry.sendPackage(package);
  logger.writePackage(package, "LOGGER.CSV");
}


void getValues() {
  //Get all the values and write them in the Corresponding Variables
  //filterData gets the new values and filters them
  mpu.updateData();

  accelX = mpu.accelX;
  accelY = mpu.accelY;
  accelZ = mpu.accelZ;

  rotX = mpu.rotFilteredX;
  rotY = mpu.rotFilteredY;
  rotZ = mpu.rotFilteredZ;

  temp = mpu.temperature;

  //getValues gets the new values and filters them
  startTime = millis();
  bmp.filterValues();
  altitude = bmp.altitude;

  package = {
    (float) stateMachine.state,
    altitude,
    temp,
    rotX,
    rotY,
    rotZ,
    accelX,
    accelY,
    accelZ,
    tvc.uY,
    tvc.uZ
    };
}
