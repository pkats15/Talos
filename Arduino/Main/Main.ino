#include <Wire.h>
int slaveAddress = 0x04;  //Address of the arduino
int metalDetector = 0x00; //Metal detector pin
int waitRobot = 8;  //Time to wait between 2 runs of the bin
void handleEV3();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin(slaveAddress);
  Wire.onRequest(handleEV3);
}

void loop() {
  // put your main code here, to run repeatedly:

}

bool hasMetal() {
  return analogRead(metalDetector);
}

int getWeight() {
  //Handle the weight measurement
  
}

void handleEV3() {
  //Handle the request from EV3
  bool metal = hasMetal();
  int weight1 = getWeight();
  int weight2;
  double totalWeight;
  Wire.write(metal);
  if(metal) {
    delay(waitRobot*1000);
    totalWeight = map(weight2-weight1,0,1024,0,500)/1000.0; //The weight difference before and after 2 runs in gramms (double)
    Serial.print(String(totalWeight)+"\n"); //Send the weight difference over serial
  }
}

