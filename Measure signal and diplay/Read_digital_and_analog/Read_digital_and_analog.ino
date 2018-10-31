
#include <LiquidCrystal.h> // Library for LCD
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);
int readValuePinDigi = 11;//Pin to read the digital value 
int readValuePinAnalog = A0;//Pin to read the digital value
int valueDigi = 0;//Variable to store the digital value 
int valueAnalog = 0;//Variable to store the analog value. 

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);// initialize LCD with 2 rows and 16 colums.
  lcd.print("D/A Value");// Print a message to the LCD.
  delay(2000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:

  valueDigi = digitalRead(readValuePinDigi);//Read the digital value from pin.
  valueAnalog = analogRead(readValuePinAnalog);//Read the analog value from pin.
  lcd.print("Digital: ");// Print a message to the LCD.
  lcd.print(valueDigi);// Print a message to the LCD.
  lcd.setCursor(0, 1);
  lcd.print("Analog: ");// Print a message to the LCD.
  lcd.print(valueAnalog);// Print a message to the LCD.
  delay(250);
  lcd.clear();
}
