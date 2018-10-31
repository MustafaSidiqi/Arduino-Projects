#include <LiquidCrystal.h>
#include "keypad4x4.h" // Library for keypad. Use "" if local file

const int blueLED = 49;
const int redLED = 51;
const int boardPin = 13;
const int moveSen = 2;
const int speaker  = 3;
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);
Keypad4x4 keypad(47, 45, 43, 41, 39, 37, 35, 33);

int value;
char keyPressed;
int code = 1234;
int pressedCode;
int numTry = 0;
char c;

void setup() {
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(boardPin, OUTPUT);
  pinMode(moveSen, INPUT);
  pinMode(speaker , OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  lcd.print("OK");
}

void loop() {
  lcd.setCursor(6, 0);
  int val = digitalRead(moveSen);
  digitalWrite(blueLED, HIGH);
  if (val == HIGH)
  {
    lcd.print("OK");
    digitalWrite(blueLED, LOW);
    digitalWrite(boardPin, HIGH);
    digitalWrite(speaker , HIGH);
    digitalWrite(redLED, HIGH);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ALARM!");
    delay(1000);
    digitalWrite(boardPin, LOW);
    digitalWrite(redLED, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("ALARM ACTIVATED!");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  PRESS ENTER!");
    readNumber();

  }
}



int readNumber () {
  int value = 0;
  char c;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TYPE CODE");
  lcd.setCursor(0, 1);
  while (true) {
    c = keypad.readKeyHex();
    if (c <= 9) {
      lcd.write("*"); // write character
      value = value * 10 + c;
    }

    if (c == 11) {
      pressedCode = value;
      lcd.clear();
      lcd.setCursor(0, 0); // First column, second row
      while (numTry <= 3) {
        if (pressedCode == code) {
          lcd.print("Deactivated");
          numTry = 0;
          digitalWrite(redLED, LOW);
          digitalWrite(blueLED, HIGH);
          digitalWrite(speaker , LOW);
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
            lcd.clear();
            lcd.print("Calling Police!");
            delay(3000);
            lcd.clear();
            lcd.print("KEYPAD DISABLED!");
            delay(3600000);


          }
          readNumber();
        }
      }
    }
  }
}



