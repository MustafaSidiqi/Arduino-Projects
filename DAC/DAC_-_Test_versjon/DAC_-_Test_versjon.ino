#include "TimerOne.h"

const byte buttonPinA = 2; // the number of the pushbutton pin, changes wave
const byte buttonPinB = 3; // the number of the pushbutton pin, changes frequency.
const byte ledPin = 13; // for testing.
volatile bool state;// Variable used for to wave form.
volatile byte c = 0;//variable used for
volatile unsigned int frequency = 100000;//frequency, 0.1 secounds.
long debouncing_time = 50; //Debouncing Time in milliseconds
volatile unsigned long last_micros;

byte sine[256] = {128, 131, 134, 137, 140, 143, 146, 149,//array with all the sine values.
                  152, 156, 159, 162, 165, 168, 171, 174,
                  176, 179, 182, 185, 188, 191, 193, 196,
                  199, 201, 204, 206, 209, 211, 213, 216,
                  218, 220, 222, 224, 226, 228, 230, 232,
                  234, 235, 237, 239, 240, 242, 243, 244,
                  246, 247, 248, 249, 250, 251, 251, 252,
                  253, 253, 254, 254, 254, 255, 255, 255,
                  255, 255, 255, 255, 254, 254, 253, 253,
                  252, 252, 251, 250, 249, 248, 247, 246,
                  245, 244, 242, 241, 239, 238, 236, 235,
                  233, 231, 229, 227, 225, 223, 221, 219,
                  217, 215, 212, 210, 207, 205, 202, 200,
                  197, 195, 192, 189, 186, 184, 181, 178,
                  175, 172, 169, 166, 163, 160, 157, 154,
                  151, 148, 145, 142, 138, 135, 132, 129,
                  126, 123, 120, 117, 113, 110, 107, 104,
                  101, 98, 95, 92, 89, 86, 83, 80,
                  77, 74, 71, 69, 66, 63, 60, 58,
                  55, 53, 50, 48, 45, 43, 40, 38,
                  36, 34, 32, 30, 28, 26, 24, 22,
                  20, 19, 17, 16, 14, 13, 11, 10,
                  9, 8, 7, 6, 5, 4, 3, 3,
                  2, 2, 1, 1, 0, 0, 0, 0,
                  0, 0, 0, 1, 1, 1, 2, 2,
                  3, 4, 4, 5, 6, 7, 8, 9,
                  11, 12, 13, 15, 16, 18, 20, 21,
                  23, 25, 27, 29, 31, 33, 35, 37,
                  39, 42, 44, 46, 49, 51, 54, 56,
                  59, 62, 64, 67, 70, 73, 76, 79,
                  81, 84, 87, 90, 93, 96, 99, 103,
                  106, 109, 112, 115, 118, 121, 124, 128
                 };

void setup()
{
  pinMode(buttonPinA, INPUT);// initialize the pushbutton pin as an input:
  pinMode(buttonPinB, INPUT);// initialize the pushbutton pin as an input:
  pinMode (ledPin, OUTPUT);//testing..
  Serial.begin(9600);//testing..
  Timer1.initialize(frequency);         // initialize timer1, and set a 0,1 second period
  Timer1.attachInterrupt(waveGen);  // attaches callback() as a timer overflow interrupt
  attachInterrupt(0, waveChange, RISING); //Interrupt 5 is Digital Pin 2
  attachInterrupt(1, freqChange, RISING); //Interrupt 5 is Digital Pin 3
  //  for (int i = 30; i < 38; i++) {//testing..
  //    pinMode(i, OUTPUT);
  //  }
}

void loop() {

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

void freqChange() {
  frequency = frequency - 10000;
  Serial.println("frequency");
  Serial.println(frequency);
  if (frequency < 10000) {
    frequency = 100000;
  }

}

void waveGen() {
  switch (state) { //this switch case runs eiher sinus or triangels code.
    case 0:
      //Serial.println("Sinus!");
      PORTC =  sine[c];
      //Serial.println(sine[c]);
      if (c == 255) {
        c = 0;
      }
      c++;
      break;
    case 1:
      //Serial.println("triangles!");
      for (int a = 0; a < 255; a++) {
        PORTC = a;

        //    delayMicroseconds(10);
      }
      for (int b = 255; b >= 0; b--) { 
        PORTC = b;
      }
      break;
  }
}


