void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
void numToBytes(int n, byte *bytes){
  //bytes[0] = (n >> 24) & 0xFF;
  //bytes[1] = (n >> 16) & 0xFF;
  bytes[0] = (n >> 8) & 0xFF;
  bytes[1] = n & 0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:
  byte a[2];
  numToBytes(69903, a);
  Serial.write(a,2);
  delay(500);
}
