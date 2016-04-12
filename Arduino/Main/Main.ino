#include <Wire.h>
int slaveAddress = 0x04;
int metalDetector = 0x00;
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
  
}

void handleEV3() {
  bool metal = hasMetal();
  int weight1 = getWeight();
  int weight2;
  double totalWeight;
  Wire.write(metal);
  if(metal) {
    delay(8000);
    totalWeight = map(weight2-weight1,0,1024,0,500)/1000.0;
    Serial.print(String(totalWeight)+"\0");
  }
}

