#include <Adafruit_CharacterOLED.h>

#include <Wire.h>

#define SLAVE_ADDRESS 0x04
boolean has_metal = false;
boolean has_afm = false;
boolean is_robot_in_use = false;
String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;
Adafruit_CharacterOLED lcd(OLED_V2, 2, 3, 4, 5, 6, 7, 8);
String lcdString, pastLcdString="";


void setup(){
    Serial.begin(9600); // start serial for output
    lcd.begin(16, 2);
}
void loop(){
  if(analogRead(3)>500){
    has_metal = true;
  }else{
    has_metal = false;
  }
  if(!has_afm){
    lcdString = "Insert AFM";
  }
  if(stringComplete){
    stringComplete = false;
    if(inputString == "metal\n"){
      if(has_metal){
        Serial.println("1");
      }else{
        Serial.println("0");
      }
    }
  }
  if(lcdString != pastLcdString){
    pastLcdString = lcdString;
    lcd.clear();
    lcd.print(lcdString);
  }
  delay(50);
}

void serialEvent(){
  while (Serial.available() && !stringComplete) {
    inputString = Serial.readString();
    stringComplete = true;
  }
}
