/*
Mustafa s153168 9/10/15
Generating sound via a piezo speaker.
This program will generate sound. It will first generate higher pitch sound, 
then wait for 500 millisecound and the make a lower pitch sound. 
This will create a "alarm" kinda sound. 
 */

const int speakerPin = 15;

// the setup function runs once when you press reset or power the board
void setup() {
  
  pinMode(speakerPin, OUTPUT); // initialize digital pin 15 as an output.
}

// the loop function runs over and over again forever
void loop() {
  delay(500);//wait for 0,5 secounds.
  tone(speakerPin, 1000, 250);//generates a a tone to speakerPin, with frequency 1000, and duration 250ms 
  delay(500);//wait for 0,5 secounds.
  tone(speakerPin, 500, 250);//generates a a tone to speakerPin, with frequency 500, and duration 250ms 
}







