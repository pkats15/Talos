#include <Key.h>
#include <Keypad.h>

#include <Adafruit_CharacterOLED.h>

#include <Wire.h>


#define SLAVE_ADDRESS 0x04
boolean has_metal = false;
boolean has_afm = false;
boolean correct_afm = false;
boolean is_robot_in_use = false;

//Resettable variables
String inputString = "";           // a string to hold incoming data
boolean stringComplete = false;
Adafruit_CharacterOLED lcd(OLED_V2, 4, 5, 6, 7, 8, 9, 10);
String lcdString,
       pastLcdString = "",
       lcdString2,
       pastLcdString2 = "";
boolean insertingPass = false;
int isPassCorrect = -1;
String passString = "";
int pass[4] = { -1, -1, -1, -1 };
int lastChar = 0;

//Non-resettable
int lastWeight = 0;


//Constants
const byte ROWS = 4;        // Four rows
const byte COLS = 3;        // Three columns
char keys[ROWS][COLS] = {
	{ '1', '2', '3' },
	{ '4', '5', '6' },
	{ '7', '8', '9' },
	{ '*', '0', '#' }
};
byte rowPins[ROWS] = { A3, A4, 3, 2 };
byte colPins[COLS] = { A0, A1, A2 };


// Create the Keypad
Keypad kpd =
    Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup()
{
	Serial.begin(9600);             // start serial for output
	lcd.begin(16, 2);
    //TODO lastWeight = measureWeight();
}

void checkForWeight(){
    delay(10000);
    //TODO Find weight
}

void checkPass(String password){
  Serial.println("{\"pass\": "+ password +"}");
  delay(200);
}

void reset(){
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Please wait");
	lcd.setCursor(0, 1);
	lcd.print("...........");

	has_metal = false;
	has_afm = false;
	correct_afm = false;
	is_robot_in_use = false;
	inputString = "";
	stringComplete = false;
	lcdString = "";
	pastLcdString = "",
	lcdString2 = "";
	pastLcdString2 = "";
	insertingPass = false;
	isPassCorrect = -1;
	passString = "";
    pass[4] = { -1, -1, -1, -1 };
    lastChar = 0;

	delay(5000);
}

void
loop() {
	char key = kpd.getKey();
	if (key) {
		if (isDigit(key)) {
			if (!insertingPass)
				insertingPass = true;
			pass[lastChar] = String(key).toInt();
			Serial.println(pass[lastChar]);
			lastChar++;
		}
	}
	if (analogRead(3) > 500)
		has_metal = true;
	else
		has_metal = false;
	if (!has_afm && !insertingPass) {
		lcdString = "Insert AFM";
		lcdString2 = "AFM: ";
	} else if (insertingPass) {
		lcdString = "AFM:";
		lcdString2 = "";
		for (int i = 0; i < 4; i++)
			if (pass[i] != -1)
				lcdString2 += "*";
	}
	if (lastChar == 4) {
		insertingPass = false;
		has_afm = true;
		passString = "";
		for (int i = 0; i < 4; i++) {
			passString += String(pass[i]);
			pass[i] = -1;
		}
		lastChar = 0;
		checkPass(passString);
		delay(80);
		if(isPassCorrect == 1) {
			lcdString = "Now insert metal";
			lcdString2 = "Ready";
			correct_afm = true;
		}
	}
	if (lcdString != pastLcdString || lcdString2 != pastLcdString2) {
		pastLcdString = lcdString;
		pastLcdString2 = lcdString2;
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(lcdString);
		lcd.setCursor(0, 1);
		lcd.print(lcdString2);
	}
	delay(50);
}

void
serialEvent(){
	while (Serial.available() && !stringComplete) {
		inputString = Serial.readString();
		stringComplete = true;
		stringComplete = false;
		if (inputString == "metal\n") {
			if (has_metal && correct_afm) {
				Serial.println("{\"metal\": true}");
			}else{
				Serial.println("{\"metal\": false}");
			}
		}else if(inputString == "correct:1\n") {
			isPassCorrect = 1;
		}else if(inputString == "correct:0\n") {
			isPassCorrect = 0;
		}
	}
}
