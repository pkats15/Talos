#include <Wire.h>

void setup() {
  Wire.begin(0x08);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
  Serial.begin(9600);
  Serial.println("OK");
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write(25); // respond with message of 6 bytes
  Serial.println("TALKED");
  // as expected by master
}
