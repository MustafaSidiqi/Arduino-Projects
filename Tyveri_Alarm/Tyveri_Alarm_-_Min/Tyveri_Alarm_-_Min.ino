#include <LiquidCrystal.h>
#include "keypad4x4.h" // Library for keypad. Use "" if local file

//Pin number for green LED.
const int greenLED = 11;
//Pin number for red LED.
const int redLED = 12;
//Pin number for PIR-sensor 1.
const int moveSen1 = 13;
//Pin number for PIR-sensor 2.
const int moveSen2 = 3;
//Pin number speaker.
const int speaker  = 2;
//Pin number for 16x2 display.

LiquidCrystal lcd(5, 6, 7, 8, 9, 10);
//Pin number for 4x4 keypad.
Keypad4x4 keypad(44, 42, 40, 38, 36, 34, 32, 30);


//variabel used to save the value of the number.
int value;

//char keyPressed;
//Code to turn off alarm.
int code = 1234;
//The kode pressed by the user.
int pressedCode;
//counter for number of tries. increases when pressed wrong code.
int numTry = 0;
//variabel used to save key pressed from keypad. This is in hexadecimal.
char c;


void setup() {
  // initialize digital pin 11 as an output.
  pinMode(greenLED, OUTPUT);
  // initialize digital pin 12 as an output.
  pinMode(redLED, OUTPUT);
  // initialize digital pin 13 as an input.
  pinMode(moveSen1, INPUT);
  // initialize digital pin 3 as an output.
   pinMode(moveSen2, INPUT);
  // initialize digital pin 2 as an output.
  pinMode(speaker , OUTPUT);
  // initialize keypad 2 rows, 16 colums.
  lcd.begin(16, 2);
  // set the cursor in the dispaly in first row, place number 6.
  lcd.setCursor(6, 0);
  // Write OK on the display.
  lcd.print("OK");
}

void loop() {
  // set the cursor in the dispaly in first row, place number 6.
  lcd.setCursor(6, 0);
  // Variabel that read from PIR-sensor. returns 1(high) if anything detected, else returns 0(low).
  int val_1 = digitalRead(moveSen1);
  int val_2 = digitalRead(moveSen2);
  //Turn off green led
  digitalWrite(greenLED, HIGH);
  //Wait untill either of the PIR-sensor detects anything.
  if ((val_1 || val_2) == HIGH)
  {
    //write Alarm on in the display.
    lcd.print("ALARM ON!");
    //turn off green led.
    digitalWrite(greenLED, LOW);
    //turn on the speaker.
    digitalWrite(speaker , HIGH);
    //turn on red led.
    digitalWrite(redLED, HIGH);
    //clear everything written on the LCD display.
    lcd.clear();
    // set the cursor in the dispaly in first row, place number 5.
    lcd.setCursor(5, 0);
    //write sensor on in the display.
    lcd.print("SENSOR");
    //wait for 1000 millisecounds, which is 1 secound.
    delay(1000);
    //turn on red led.
    digitalWrite(redLED, HIGH);
    // set the cursor in the dispaly in first row, place number 1.
    lcd.setCursor(0, 1);
    //write Alarm activated on in the display.
    lcd.print("ALARM ACTIVATED!");
    //wait for 3000 millisecounds, which is 3 secounds.
    delay(3000);
    //clear everything written on the LCD display.
    lcd.clear();
    // set the cursor in the dispaly in first row, place number 1.
    lcd.setCursor(0, 0);
    //write PRESS ENTER! on in the display.
    lcd.print("  PRESS ENTER!");
    //calls function called readNumber, runs the function.
    readNumber();

  }
}


//function called readNumber
int readNumber () {
  //value to keep the pressed number.
  int value = 0;
  //variabel used to convert the pressed characher from hexadecimal to decimal-system.
  char c;
  //clear everything written on the LCD display.
  lcd.clear();
  // set the cursor in the dispaly in first row, place number 1.
  lcd.setCursor(0, 0);
  //write TYPE CODE on in the display.
  lcd.print("TYPE CODE");
  // set the cursor in the dispaly in first row, place number 1.
  lcd.setCursor(0, 1);
  //This while statement will run everytime, since the its allways true.
  while (true) {
    //assign the variabel c to the pressed key on the keypad.
    c = keypad.readKeyHex();
    //the if-statement runs aslong as the pressed number is a number between 0-9.
    if (c <= 9) {
      // write character "*" on the display.
      lcd.write("*");
      // this uses the numbers place and the value it has.
      value = value * 10 + c;
    }
    //runs when a specific key on the keypad is pressed.
    if (c == 11) {
      //Assign the value of "value" to pressedCode.
      pressedCode = value;
      //clear everything written on the LCD display.
      lcd.clear();
      // First column, First row.
      lcd.setCursor(0, 0);
      //runs as long as numTry is less or equal to 3.
      while (numTry <= 3) {
        //Runs if the pressed Code is the correct code.
        if (pressedCode == code) {
          // write deactivated on the display.
          lcd.print("Deactivated");
          //resets numTry to 0.
          numTry = 0;
          //turn off red led.
          digitalWrite(redLED, LOW);
          //turn off speaker.
          digitalWrite(speaker , LOW);
          //turn on green led.
          digitalWrite(greenLED, HIGH);
          //wait for 36000000 millisecounds, which is one hour.
          delay(36000000);
          //skip the rest of the code.
          break;
          //Runs if the pressed code is not correct.
        } else if (pressedCode != code) {
          // write wrong code on the display.
          lcd.print("WRONG CODE!!");
          //wait for 500 millisecounds, which is 0,5 secound.
          delay(500);
          //clear everything written on the LCD display.
          lcd.clear();
          // write try again on the display.
          lcd.print("Try again");
          // First column, secound row.
          lcd.setCursor(0, 1);
          // increases numTry by one.
          numTry++;
          //runs if numTry is eqaul to 3.
          if (numTry == 3) {
            //clear everything written on the LCD display.
            lcd.clear();
            // First column, first row.
            lcd.setCursor(0, 0);
            // write calling police on the display.
            lcd.print("CALLING POLICE!");
            //wait for 3000 millisecounds, which is 3 secounds.
            delay(3000);
            //clear everything written on the LCD display.
            lcd.clear();
            // write Keypad disabled on the display.
            lcd.print("KEYPAD DISABLED!");
            //wait for 36000000 millisecounds, which is one hour.
            delay(36000000);
          }
          //calls function called readNumber, runs the function.
          readNumber();
        }
      }
    }
  }
}



