#include <Key.h>
#include <Keypad.h>

#include <Adafruit_CharacterOLED.h>

#include <Wire.h>


#define SLAVE_ADDRESS 0x04
boolean has_metal = false;
boolean has_afm = false;
boolean is_robot_in_use = false;
String inputString = "";           // a string to hold incoming data
boolean stringComplete = false;
Adafruit_CharacterOLED lcd(OLED_V2, 4, 5, 6, 7, 8, 9, 10);
String lcdString,
       pastLcdString = "",
       lcdString2,
       pastLcdString2 = "";
boolean insertingPass = false;
int pass[4] = { -1, -1, -1, -1 };
int lastChar = 0;
const byte ROWS = 4;      // Four rows
const byte COLS = 3;      // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'},
        {'*', '0', '#'}
};
byte rowPins[ROWS] = { A3, A4, 3, 2 };
byte colPins[COLS] = { A0, A1, A2 };

String passString="";

// Create the Keypad
Keypad kpd =
        Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void
setup()
{
        Serial.begin(9600); // start serial for output
        lcd.begin(16, 2);
}
void
loop()
{
        char key = kpd.getKey();
        if (key) {
                if (isDigit(key)) {
                        if (!insertingPass) {
                                insertingPass = true;
                        }
                        pass[lastChar] = String(key).toInt();
                        lastChar++;
                }
        }
        if (analogRead(3) > 500) {
                has_metal = true;
        } else {
                has_metal = false;
        }
        if (!has_afm && !insertingPass) {
                lcdString = "Insert AFM";
                lcdString2 = "AFM: ";
        } else if (insertingPass) {

                lcdString = "AFM:";
                lcdString2 = "";
                for (int i = 0; i < 4; i++) {
                        if (pass[i] != -1) {
                                lcdString2 += "*";
                        }
                }
        }
        if (lastChar == 4) {
                insertingPass = false;
                has_afm = true;
                for (int i = 0; i < 4; i++) {
                        pass[i] = -1;
                        passString += String(pass[i]);
                }
                Serial.println(passString);
                lastChar = 0;
        }
        if (stringComplete) {
                stringComplete = false;
                if (inputString == "metal\n") {
                        if (has_metal) {
                                Serial.println("1");
                        } else {
                                Serial.println("0");
                        }
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
serialEvent()
{
        while (Serial.available() && !stringComplete) {
                inputString = Serial.readString();
                stringComplete = true;
        }
}
