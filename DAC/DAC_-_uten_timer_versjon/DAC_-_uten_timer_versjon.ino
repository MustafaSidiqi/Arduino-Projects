const int buttonPinA = 2;     // the number of the pushbutton pin
const int buttonPinB = 3;
int ledPin = 13;
volatile int state = LOW;
long int sine[256];
int j = 0;
void setup()
{

  // initialize the pushbutton pin as an input:
  pinMode(buttonPinA, INPUT);
  pinMode(buttonPinB, INPUT);
  pinMode (ledPin, OUTPUT);
  Serial.begin(9600);
  for (int i = 30; i < 38; i++) {
    pinMode(i, OUTPUT);
  }

  float x;
  float y;
  for (int i = 0; i < 256; i++) {
    x = (float)i;
    y = sin((x / 255) * 2 * PI);
    sine[i] = int(y * 128) + 128;
    //    Serial.print(i);
    delayMicroseconds(50);

  }
  attachInterrupt(0, ISR_trigger, HIGH); //Interrupt 5 is Digital Pin 18
}

void loop() {
  digitalWrite (ledPin, state);

  if (state) {
    for (int i = 0; i < 256; i++)
    {
      j++;
      PORTC =  sine[i];
      Serial.print(sine[i]);
      Serial.print(", ");
      delayMicroseconds(5);
    }
  } else if (!state) {
    for (int a = 0; a < 256; a++) {
      PORTC = a;
      //    delayMicroseconds(10);
    }
    for (int b = 256; b >= 0; b--) {
      PORTC = b;
    }
  }

}

void ISR_trigger() {
  state = !state;
}


