// Mustafa Sidiqi 13.09.15 
// This code will take input from a keypad, which is 4x4, and convert the individual inputted number to a whole number.

#include <LiquidCrystal.h> // Library for LCD
#include "keypad4x4.h" // Library for keypad. Use "" if local file
// Create an object for the LCD and define pin numbers
LiquidCrystal lcd(5, 6, 7, 8, 9, 10);
// Create an object for the keypad and define pin numbers
Keypad4x4 keypad(44, 42, 40, 38, 36, 34, 32, 30);
int i = 0; // Decides the place of the inputted number in mainArray
int k = 0;//Used in the while loop. The loop will run untill the length of mainArray is less then k. 
int numPressed; //
int multipi = 1;// used in the while loop. each number will get muliplied by this. 
int num = 0; // The final number. 
int mainArray[10]; // Array used to input each number.
int arrLength = -1; // The length of mainArray, this will be incresed by one each time a number is pressed. 

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);// initialize LCD with 2 rows and 16 colums.
  lcd.print("Test keypad");// Print a message to the LCD.
  Serial.begin(9600);// initialize  serial port:
}
void loop() {
  int c = keypad.readKeyASCII(); // Wait for key pressed
  if ((c != 0) && (c >= 48 && c <= 56)) { // a number must be pressed, and the pressed number must be between 48 and 56 ascii character, which is 0-9.
    lcd.setCursor(i, 1); // First column, second row
    lcd.write("*"); // write character
    numPressed = c - 48; // subtract 48 from the ascii character, so we end up with the number pressed. 
    //    Serial.println(numPressed);
    //    Serial.println(i);
    mainArray[i] = numPressed;//Insert the number into mainArray. 
    i++; //increase i by one.
    arrLength++; //increase i by one.
  
  }
  if (c == 65) { // if the ascii charatcer has the value 65, which is "A".
    lcd.clear();// clear the LCD. 
    while (k <= arrLength) {
      num += mainArray[arrLength] * multipi; //this will multipli each number in the array with "multipi". The idea is the each number has its place, like ones, tens, hundreds and so on. 
      multipi *= 10;
      arrLength--;
      Serial.println(num);
    }
    lcd.setCursor(0, 0); // First column, second row
    lcd.print("Number is:");
    lcd.print(num);
  }
}




