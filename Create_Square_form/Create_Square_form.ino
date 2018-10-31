/* Mustafa Sidiqi s153168 
 *  30/09/15
 *  Create square/sin waves.
 *  This code will create square waves with 500 Hz.
 */

const int pin = 9;



void setup() {
  // put your setup code here, to run once:
  pinMode(pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  // 2 ms = 1/0.002 = 500 Hz… 
     digitalWrite(pin, HIGH); 
     delay(1); 
     digitalWrite(pin, LOW);
     delay(1);

}










