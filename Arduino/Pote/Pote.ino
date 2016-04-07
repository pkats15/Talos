#define THRESHOLD 8
#define PORT 0
typedef enum {
  ABOVE,
  BELOW
} State;
State lastState = BELOW;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int v = analogRead(PORT);
  int mappedV = map(v, 0, 1024, 0, 100);
  if(mappedV >= THRESHOLD && lastState == BELOW){
    Serial.println("A");
    lastState = ABOVE;
  }else if(mappedV < THRESHOLD && lastState == ABOVE){
    Serial.println("B");
    lastState = BELOW;
  }
  delay(20);
}
