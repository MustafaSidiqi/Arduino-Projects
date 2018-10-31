#include <LiquidCrystal.h>

const int okPin = 49;
const int alarmPin = 51;
const int boardPin = 13;
const int inputPin = 2;
const int piezoPin = 3;
LiquidCrystal lcd(50, 48, 46, 44, 42, 40);

int value;
char keyPressed;
int code = 1234;
int pressedCode;
int numTry = 0;
char c;

void setup() {
  pinMode(okPin, OUTPUT);
  pinMode(alarmPin, OUTPUT);
  pinMode(boardPin, OUTPUT);
  pinMode(inputPin, INPUT);
  pinMode(piezoPin, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  lcd.print("OK");
}

void loop() {
  lcd.setCursor(6, 0);
  int val = digitalRead(inputPin);
  digitalWrite(okPin, HIGH);
  if (val == HIGH)
  {
    lcd.print("OK");
    digitalWrite(okPin, LOW);
    digitalWrite(boardPin, HIGH);
    digitalWrite(piezoPin, HIGH);
    digitalWrite(alarmPin, HIGH);
    lcd.clear();
    lcd.setCursor(5, 0);
    lcd.print("ALARM!");
    delay(1000);
    digitalWrite(boardPin, LOW);
    digitalWrite(piezoPin, LOW);
    digitalWrite(alarmPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("ALARM ACTIVATED!");
  }
}


