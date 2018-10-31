int frekvens[21] = {220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698};
int tone_index = 0;
int i = 0;
int duration = 0;
int durationDelay = 0;
int speakerPin = 10;
int tempo = 0;

// Mester Jakob
const char mesterjakob[] = "t8,d4,e-4,d2,e-4,f10,p8,d4,e-4,f2,g4,a-10,p8,g4,a-4,g4,"
                           "a-2,h-4,h-4,h-2,a4,g4,f4,f4,f-4,e-4,d4,f2,f4,g2,f4,e-16,p4,e-2,e-4,f2,e-4,"
                           "d16,p4,f2,f4,g2,f4,e-16,p4,e-2,e-4,f2,e-4,d32,c>4,c#>4,d>4,e>4,f>4,c>4,p8,"
                           "p4,c>2,c>4,c->2,h-4,a16,c>4,c#>4,d>4,e>4,f>4,c>4,p8,p4,c>2,c>4,d>2,e>4,f>16,"
                           "d4,e-4,d2,e-4,f10,p8,d4,e-4,f2,g4,a-10,p8,g4,a-4,g4,a-2,h-4,h-4,h-2,a4,g4,f4,"
                           "f4,f-4,e-4,d4,f2,f4,g2,f4,e-16,p4,e-2,e-4,f2,e-4,d16,p4,f2,f4,g2,f4,e-16,p4,"
                           "f2,f4,g2,a4,h-4,p4,h-<4,p4,";


//Defining state names as enum
enum States {
  start, tonetrin, opp_ned, halv_opp_ned, lengde, spill_tone, tempoState
};

States state;




void setup() {
  // put your setup code here, to run once:
  pinMode(speakerPin, OUTPUT);
  state = start;
  Serial.begin(9600);

  //    tone(speakerPin, frekvens[4], 200);
  //    tonetrin_func();
}

void loop() {
  delay(10);
  // put your main code here, to run repeatedly:
  switch (state) {
    case start:
      start_func();
      break;
    case tonetrin:
      tonetrin_func();
      break;
    case lengde:
      lengde_func();
      break;
    case  spill_tone:
      spill_tone_func();
      break;
    case  tempoState:
      tempo_func();
      break;
  }

}

void start_func() {
  char c = mesterjakob[i];
  Serial.print("start_func ");
  Serial.println(c);
  Serial.print("i: ");
  Serial.println(i);
  switch (c)
  {
    case ('a'):
      tone_index = 13;
      state = tonetrin;
      delay(3);
      break;
    case ('b'):
      tone_index = 15;
      state = tonetrin;
      delay(3);
      break;
    case ('c'):
      tone_index = 3;
      state = tonetrin;
      delay(3);
      break;
    case ('d'):
      tone_index = 5;
      state = tonetrin;
      delay(3);
      break;
    case ('e'):
      tone_index = 7;
      state = tonetrin;
      delay(3);
      break;
    case ('f'):
      tone_index = 8;
      state = tonetrin;
      delay(3);
      break;
    case ('g'):
      tone_index = 10;
      state = tonetrin;
      delay(3);
      break;
    case ('h'):
      tone_index = 15;
      state = tonetrin;
      delay(3);
      break;
    case ('t'):
      state = tempoState;
      delay(3);
      break;
  }
  i++;
}

void tonetrin_func() {

  char c = mesterjakob[i];
  Serial.print("tonetrin_func ");
  Serial.println(c);
  Serial.print("i: ");
  Serial.println(i);
  if (c > 0 && c < 9) {
    state = lengde;
  }
  switch (c) {
    case ('+'):
      tone_index++;
      state = lengde;
      delay(5);
      break;
    case ('-'):
      delay(5);
      tone_index--;
      state = lengde;
      break;
    case ('<'):
      delay(5);
      tone_index = tone_index - 12;
      state = lengde;
      break;
    case ('>'):
      delay(5);
      tone_index = tone_index + 12;
      state = lengde;
      break;
    case ('#'):
      delay(5);
      tone_index++;
      state = tonetrin;
      i++;
      break;
    case (','):
      delay(5);
      state = spill_tone;
      break;
    case '0' ... '9':
      delay(5);
      state = lengde;
      break;
  }
  //  i++;
}



//  for (int i = 0; i < 10; i++) {
//    Serial.println(mesterjakob[i]);
//  }




void lengde_func() {
  delay(5);
  char c = mesterjakob[i];
  Serial.print("lengde_func ");
  Serial.println(c);
  Serial.print("i ");
  Serial.println(i);

  switch (c)
  {
    case '0' ... '9':
      delay(3);
      c -= 48;
      duration = duration * 10 + c;
      Serial.println(duration);
      Serial.print("duration");
      Serial.println(duration);
      durationDelay =  8 * duration * tempo;
      state = tonetrin;
      break;
  }
  i++;
}

void spill_tone_func() {
  Serial.print("frekvens[tone_index] ");
  Serial.println(frekvens[tone_index]);
  Serial.print("duration ");
  Serial.println(duration);
  delay(1 * duration * tempo);
  Serial.print("delay ");
  Serial.println(1 * duration * tempo);
  duration = duration * 7 * tempo;
  tone(speakerPin, frekvens[tone_index], duration);
  Serial.print("durationDelay ");
  delay(durationDelay);
  i++;
  Serial.print("i: ");
  Serial.println(i);
  state = start;
  duration = 0;
}

void tempo_func() {
  delay(5);
  char c = mesterjakob[i];
  Serial.print("tempo_func ");
  Serial.println(c);
  Serial.print("i ");
  Serial.println(i);

  switch (c)
  {
    case '0' ... '9':
      delay(5);
      c = c - 48;
      tempo = tempo * 10 + c;
      Serial.print("tempo: ");
      Serial.println(tempo);
      state = tempoState;
      break;
    case (','):
      delay(5);
      state = start;
      break;
  }
  i++;
}

