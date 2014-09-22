
const int ledPinR =  8;
const int ledPinG =  9;
const int ledPinB = 10;
const int ledRight = 11;
const int ledLeft  = 12;

long previousMillis = 0;

long interval = 2000;

bool ALLOWDIM = false;

void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledLeft, OUTPUT);
  
  digitalWrite(ledRight, HIGH);
  digitalWrite(ledLeft, HIGH);
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
    LEDs(255, 0, 255, 255, 255, 0);
  } else {
    LEDs(255, 255, 0, 255, 0, 255);
  }
}
