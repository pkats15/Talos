bool isOn,shouldBeOn;

void setup() {
  // put your setup code here, to run once:
  isOn=false;
  shouldBeOn=false;
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(isOn&&!shouldBeOn){
    digitalWrite(13, LOW);
    isOn=false;
  }else if(!isOn&&shouldBeOn){
    digitalWrite(13, HIGH);
    isOn=true;
  }
}

void serialEvent() {
  char c;
  while (Serial.available()) {
    c = Serial.read();
  }
  if(c=='O'){
    shouldBeOn=true;
  }else if(c=='C'){
    shouldBeOn=false;
  }
}
