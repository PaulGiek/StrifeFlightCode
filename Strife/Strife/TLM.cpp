#include "TLM.h"

RF24 Radio(4, A0);  // CE, CSN

void TLM::init() {
  //Start the RF Module
  while (Radio.begin() == 0){
    Serial.println(Radio.begin());
    digitalWrite(8, HIGH);
    delay(300);
    digitalWrite(8, LOW);
    delay(300);
  }

  //Set the address
  Radio.openWritingPipe(address);

  //Set module as transmitter
  Radio.stopListening();
  
  TLMInitSC = true;
}

void TLM::sendPackage(Package package) {
  Radio.write(&package.state, sizeof(package.state));
  Radio.write(&package.altitude, sizeof(package.altitude));
  Radio.write(&package.temperature, sizeof(package.temperature));
  Radio.write(&package.rotX, sizeof(package.rotX));
  Radio.write(&package.rotY, sizeof(package.rotY));
  Radio.write(&package.rotZ, sizeof(package.rotZ));
  Radio.write(&package.accelX, sizeof(package.accelX));
  Radio.write(&package.accelY, sizeof(package.accelY));
  Radio.write(&package.accelZ, sizeof(package.accelZ));
  Radio.write(&package.uY, sizeof(package.uY));
  Radio.write(&package.uZ, sizeof(package.uZ));
  char sep = ';';
  Radio.write(&sep, sizeof(sep));
  

  Serial.println("Sent it all.");
}

void TLM::sendInitState(bool bmp, bool imu, bool sd, bool sdr) {
  String msg = "ST:" + (String)bmp + (String)imu + (String)sd + (String)sdr;
  Serial.println(msg);
  Radio.write(&msg, sizeof(msg));
}

TLM::TLM():address("00001") {
  
}
