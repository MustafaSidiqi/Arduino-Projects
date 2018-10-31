#include <SPI.h>
#include <SD.h>



const byte buttonPinA = 2; // the number of the pushbutton pin, changes wave
volatile bool state;// Variable used for to wave form.
long debouncing_time = 50; //Debouncing Time in milliseconds
volatile unsigned long last_micros;

File myFile;
void setup() {
  pinMode(buttonPinA, INPUT);// initialize the pushbutton pin as an input:
  attachInterrupt(0, waveChange, CHANGE); //Interrupt 5 is Digital Pin 2
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
}

void loop() {
  waveGen();
}

void reading2SD() {

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    Serial.println("reading from sdCard");
    while (myFile.available()) {

      int input = myFile.parseInt();
      Serial.print(input);
    }
    myFile.close();// close the file:
  } else {
    Serial.println("error opening test.txt");// if the file didn't open, print an error:
  }
}

void writing2SD() {

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("1,2,3,4,5,6");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


void waveChange() {//function used for deboucing.
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {//wait for aleat "debouncing_time" of time.
    //if its has been that amount of time, then we know for sure the button is pushed, so we change the state.
    Interrupt();
    last_micros = micros();

  }


}

void Interrupt() {//this function changes the state, which again chagnes the wave form.
  state = !state;//change state to the oppisite.
}

void waveGen() {
  switch (state) { //this switch case runs eiher sinus or triangels code.
    case 0:
      reading2SD();
    case 1:
      writing2SD();
  }
}

