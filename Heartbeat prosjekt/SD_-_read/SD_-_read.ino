#include <SPI.h>
#include <SD.h>
const int numberValues = 1000;
unsigned int valueArray[numberValues];
int index = 0;

File myFile;

void setup() {
  DDRC = 0b11111111;
  // Open serial communications and wait for port to open:
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

  // put your setup code here, to run once:
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    Serial.println("reading from sdCard");
    //    while (myFile.available()) {
    //
    //      int input = myFile.parseInt();
    //      valueArray[i] = input;
    //      //Serial.print(input);
    //      Serial.println(valueArray[i] = input);
    //      i++;
    //    }
    //    myFile.close();// close the file:
    //  }
    if (myFile) {
      //for (index = 0; index <= numberValues; index++) {
      while (myFile.available()) {
        int input = myFile.parseInt();
        valueArray[index] = input;
        delayMicroseconds(5);
        index++;
        Serial.print("input:");
        Serial.println(input);
        Serial.print("index:");
        Serial.println(index);
      }

      //}
      Serial.println(index);
      myFile.close();
    }





    else {
      Serial.println("error opening test.txt");// if the file didn't open, print an error:
    }
  }
  Serial.print("index: ");
  Serial.println(index);
  delay(5000);
}


void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < (sizeof(valueArray)/2); i++) {
    PORTC =  valueArray[i];
    delayMicroseconds(5);
    Serial.println(PORTC =  valueArray[i]);
  }
}
