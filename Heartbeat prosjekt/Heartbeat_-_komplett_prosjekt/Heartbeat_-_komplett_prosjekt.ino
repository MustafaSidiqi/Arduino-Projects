#include <SPI.h>
#include <SD.h>
#include "TimerOne.h"

File myFile;
unsigned int array[543] = {58 , 58 , 58 , 58 , 59 , 59 , 59 , 59 , 59 , 59 , 60 , 60 , 60 , 61 , 61 , 61 , 62 , 62 , 62 , 63 , 64 , 64 , 65 , 65 , 66 , 67 , 67 , 68 , 69 , 70 , 70 , 70 , 71 , 71 , 71 , 71 , 72 , 72 , 73 , 73 , 74 , 74 , 75 , 75 , 76 , 76 , 76 , 77 , 77 , 78 , 78 , 78 , 79 , 79 , 79 , 79 , 79 , 80 , 80 , 80 , 80 , 80 , 79 , 79 , 79 , 79 , 79 , 79 , 78 , 78 , 78 , 78 , 78 , 78 , 77 , 77 , 77 , 77 , 76 , 76 , 76 , 75 , 75 , 75 , 75 , 74 , 74 , 74 , 74 , 73 , 73 , 72 , 72 , 72 , 71 , 71 , 71 , 70 , 70 , 70 , 69 , 69 , 68 , 68 , 68 , 67 , 67 , 66 , 66 , 65 , 65 , 64 , 63 , 63 , 62 , 62 , 61 , 61 , 61 , 60 , 60 , 60 , 60 , 59 , 59 , 59 , 59 , 59 , 58 , 58 , 58 , 58 , 58 , 58 , 58 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 59 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 59 , 59 , 59 , 59 , 59 , 58 , 58 , 58 , 57 , 57 , 57 , 56 , 56 , 55 , 55 , 54 , 51 , 45 , 37 , 34 , 31 , 39 , 43 , 47 , 50 , 56 , 61 , 63 , 66 , 70 , 77 , 84 , 91 , 130 , 140 , 154 , 159 , 162 , 165 , 168 , 192 , 195 , 199 , 201 , 207 , 212 , 218 , 223 , 237 , 240 , 243 , 237 , 215 , 215 , 206 , 190 , 176 , 175 , 139 , 141 , 118 , 108 , 101 , 62 , 56 , 22 , 23 , 12 , 1 , 2 , 3 , 5 , 7 , 10 , 14 , 17 , 18 , 19 , 20 , 21 , 23 , 24 , 26 , 30 , 33 , 37 , 40 , 43 , 47 , 50 , 52 , 53 , 54 , 55 , 57 , 58 , 60 , 63 , 64 , 65 , 65 , 65 , 66 , 66 , 66 , 66 , 66 , 66 , 66 , 65 , 65 , 65 , 65 , 65 , 65 , 64 , 64 , 64 , 64 , 64 , 64 , 63 , 63 , 63 , 63 , 63 , 63 , 62 , 62 , 62 , 62 , 62 , 62 , 62 , 62 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 60 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 62 , 62 , 62 , 62 , 62 , 62 , 63 , 63 , 63 , 63 , 64 , 64 , 64 , 65 , 65 , 65 , 65 , 66 , 66 , 66 , 67 , 67 , 68 , 68 , 68 , 69 , 69 , 70 , 70 , 70 , 71 , 71 , 72 , 72 , 73 , 73 , 73 , 74 , 74 , 74 , 75 , 75 , 75 , 76 , 76 , 77 , 77 , 77 , 78 , 78 , 78 , 78 , 79 , 79 , 80 , 80 , 81 , 81 , 82 , 82 , 83 , 83 , 83 , 83 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 84 , 83 , 83 , 83 , 83 , 83 , 83 , 83 , 82 , 82 , 82 , 82 , 82 , 82 , 82 , 81 , 81 , 80 , 80 , 80 , 79 , 79 , 79 , 78 , 78 , 78 , 77 , 77 , 77 , 76 , 76 , 75 , 75 , 75 , 74 , 74 , 73 , 73 , 72 , 72 , 71 , 71 , 71 , 71 , 70 , 70 , 70 , 69 , 69 , 69 , 68 , 68 , 67 , 67 , 66 , 66 , 66 , 65 , 65 , 65 , 64 , 64 , 64 , 64 , 63 , 63 , 63 , 63 , 62 , 62 , 62 , 62 , 61 , 61 , 62 , 62 , 62 , 62 , 62 , 62 , 62 , 62 , 62 , 62 , 62 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 61 , 62 , 62 , 62 , 62 , 62 , 62 , 63 , 63};
int removeButton = 2;
bool readyState = false;
const int ISRbtn = 2;
int numberValues = 0;
const int maxValues = 1000;
int valueArray[maxValues];
int index = 0;

long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

void setup() {
  // put your setup code here, to run once:
  DDRC = 0b11111111;
  pinMode(13, OUTPUT);
  pinMode(removeButton, INPUT);
  pinMode(ISRbtn, INPUT);
  attachInterrupt(0, debounceInterrupt, HIGH); //Interrupt 0 is Digital Pin 2
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(53)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  removeFile();
  sdWrite();
  sdRead();
  readyState = true;
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(500);
}

void loop() {
  // put your main code here, to run repeatedly:
  sdRead();
}


void sdWrite() {
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    for (int i = 0; i < 543; i++) {
      myFile.println(array[i]);
      Serial.println(array[i]);
    }
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void sdRead() {

  if (!readyState) {
    // re-open the file for reading:
    myFile = SD.open("test.txt");
    if (myFile) {
      Serial.println("test.txt:");

      // read from the file until there's nothing else in it:
      Serial.println("reading from sdCard");
      if (myFile) {
        //for (index = 0; index <= numberValues; index++) {
        while (myFile.available()) {
          int input = myFile.parseInt();
          valueArray[index] = input;
          index++;
          Serial.print("input:");
          Serial.println(input);
          Serial.print("index:");
          Serial.println(index);
        }
        numberValues = index;
        Serial.println(index);
        myFile.close();
      }
      else {
        Serial.println("error opening test.txt");// if the file didn't open, print an error:
      }
    }
  }
  Serial.print("numberValues");
  Serial.println(numberValues);
  if (readyState == true) {
    for (int i = 0; i < numberValues - 1; i++) {
      //PORTC =  valueArray[i];
      valueArray[i];
      delayMicroseconds(5);
      Serial.println(PORTC =  valueArray[i]);
    }

  }
}
void removeFile() {
  SD.remove("test.txt");
}

void HeartFail() {
  Serial.println("HEART IS FAILING ");
  PORTC = 128;
}

void debounceInterrupt() {
  if((long)(micros() - last_micros) >= debouncing_time * 1000) {
    HeartFail();
    last_micros = micros();
  }
}

