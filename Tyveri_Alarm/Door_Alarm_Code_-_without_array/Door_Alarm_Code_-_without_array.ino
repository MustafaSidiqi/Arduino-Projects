// Mustafa Sidiqi 13.09.15
// This code will take input from a keypad, which is 4x4, and convert the individual inputted number to a whole number.

#include <LiquidCrystal.h> // Library for LCD
#include "keypad4x4.h" // Library for keypad. Use "" if local file
// Create an object for the LCD and define pin numbers
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);
// Create an object for the keypad and define pin numbers
Keypad4x4 keypad(44, 42, 40, 38, 36, 34, 32, 30);
int value;
char keyPressed;
int code = 1234;
int pressedCode;
int numTry = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);// initialize LCD with 2 rows and 16 colums.
  lcd.print("Write Code");// Print a message to the LCD.
  Serial.begin(9600);// initialize  serial port:
}
void loop() {
  lcd.setCursor(0, 1); // First column, second row
  pressedCode = readNumber();
  char keyPressed = keypad.readKeyHex();
}

int readNumber () {
  int value = 0;
  char c;
  while (true) {
    c = keypad.readKeyHex();
    if (c <= 9) {
      lcd.write(c + 48); // write character
      value = value * 10 + c;
    }

    if (c == 11) {
      pressedCode = value;
      lcd.clear();
      lcd.setCursor(0, 0); // First column, second row
      while (numTry <= 3) {
        if (pressedCode == code) {
          lcd.print("It works");
          numTry = 0;
          break;
        } else if (pressedCode != code) {
          lcd.print("Wrong Code");
          delay(250);
          lcd.clear();
          lcd.print("Try again");
          lcd.setCursor(0, 1);
          numTry++;
          if (numTry == 3) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Alarm truns on");
            delay(3000);
            lcd.clear();
            lcd.print("Restarting in 3s");
            delay(3000);
            lcd.clear();
            lcd.print("Write Code");
            lcd.setCursor(0, 1);
            numTry = 0;
            readNumber();
            
          }
          readNumber();
        }
      }
    }
  }
}




