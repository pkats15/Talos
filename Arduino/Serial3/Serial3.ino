int strength, curr_strength;
int led=10;
void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(strength != curr_strength){
    analogWrite(led,strength);
    curr_strength = strength;
  }
}

void serialEvent(){
  //Serial event
  String s;
  int a;
  if(Serial.available()){
    delay(10);
    s=Serial.readStringUntil('\n');
    delay(10);
  }
  a=s.toInt();
  if(a>=0 && a<=100){
    strength = map(a,0,100,0,255);
  }
}

