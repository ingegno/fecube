
const int ledPinR =  8;
const int ledPinG =  9;
const int ledPinB = 10;
const int ledRight = 11;
const int ledLeft  = 12;

long previousMillis = 0;

long interval = 6000;

bool ALLOWDIM = false;

int random_colorR1 = 0;
int random_colorG1 = 0;
int random_colorB1 = 0;
int random_colorR2 = 0;
int random_colorG2 = 0;
int random_colorB2 = 0;
int random_colorR3 = 0;
int random_colorG3 = 0;
int random_colorB3 = 0;
bool startfade = false;

void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledLeft, OUTPUT);
  
  randomSeed(analogRead(0));
  
  digitalWrite(ledRight, HIGH);
  digitalWrite(ledLeft, HIGH);
  
  random_colorR2 = random(256);
  random_colorG2 = random(256);
  random_colorB2 = random(256);
  random_colorR3 = random(256);
  random_colorG3 = random(256);
  random_colorB3 = random(256);
}

void smooth_transitie(float fadeval) {
  // fadeval between 0 and 1. Fade Led1 from color 1 to 2, and Led2 from color 2 to 3
  if (startfade == true) {
    random_colorR3 = random(256);
    random_colorG3 = random(256);
    random_colorB3 = random(256);
    startfade = false;
  }
  LEDs(round(fadeval*random_colorR2 + (1-fadeval)*random_colorR1),
       round(fadeval*random_colorG2 + (1-fadeval)*random_colorG1),
       round(fadeval*random_colorB2 + (1-fadeval)*random_colorB1),
       round(fadeval*random_colorR3 + (1-fadeval)*random_colorR2),
       round(fadeval*random_colorG3 + (1-fadeval)*random_colorG2),
       round(fadeval*random_colorB3 + (1-fadeval)*random_colorB2));
}

void LEDs(int R_1, int G_1, int B_1, int R_2, int G_2, int B_2) {
  digitalWrite(ledLeft, LOW);
  color(R_1, G_1, B_1);
  digitalWrite(ledLeft, HIGH);
  digitalWrite(ledRight, LOW);
  color(R_2, G_2, B_2);
  digitalWrite(ledRight, HIGH);
} 

/* Show color of mixing R, G, B as values 0 to 255 */
void color(int R, int G, int B) {
  // we show each unit 2 microseconds
  if (R>0) {
    digitalWrite(ledPinR, HIGH);
    delayMicroseconds(2*R);
    digitalWrite(ledPinR, LOW);
  }
  if (G>0) {
    digitalWrite(ledPinG, HIGH);
    delayMicroseconds(2*G);
    digitalWrite(ledPinG, LOW);
  }
  if (B>0) {
    digitalWrite(ledPinB, HIGH);
    delayMicroseconds(2*B);
    digitalWrite(ledPinB, LOW);
  }
  if (ALLOWDIM)
    delayMicroseconds(2*(255-R)+2*(255-G)+2*(255-B));
}

void yellow() {
  color(255, 255, 0);
}

void purple() {
  color(255, 0, 255);
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long timer = currentMillis - previousMillis;
  if (timer > interval) {
    // save last time
    previousMillis = currentMillis;
  }

  if ( timer < interval/2) {
    // first second, show fixed color
    if (startfade == false) {
      //shift colors
      random_colorR1 = random_colorR2;
      random_colorG1 = random_colorG2;
      random_colorB1 = random_colorB2;
      random_colorR2 = random_colorR3;
      random_colorG2 = random_colorG3;
      random_colorB2 = random_colorB3;
      startfade = true;
    }
    LEDs(random_colorR1, random_colorG1, random_colorB1, random_colorR2, random_colorG2, random_colorB2);
  } else {
    smooth_transitie((timer-interval/2)/float(interval/2));
  }
}
