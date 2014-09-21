
const int ledPinR =  8;
const int ledPinG =  9;
const int ledPinB = 10;

int ledStateR = LOW;
int ledStateG = LOW;
int ledStateB = LOW;
long previousMillis = 0;

long interval = 3000;

bool ALLOWDIM = false;

void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
}

/* Show color of mixing R, G, B as values 0 to 255 */
void color(int R, int G, int B) {
  // we show each unit 3 microseconds
  if (R>0) {
    digitalWrite(ledPinR, HIGH);
    delayMicroseconds(3*R);
    digitalWrite(ledPinR, LOW);
  }
  if (G>0) {
    digitalWrite(ledPinG, HIGH);
    delayMicroseconds(3*G);
    digitalWrite(ledPinG, LOW);
  }
  if (B>0) {
    digitalWrite(ledPinB, HIGH);
    delayMicroseconds(3*B);
    digitalWrite(ledPinB, LOW);
  }
  if (ALLOWDIM)
    delayMicroseconds(3*(255-R)+10*(255-G)+10*(255-B));
}

void yellow() {
  color(255, 255, 0);
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long timer = currentMillis - previousMillis;
  if (timer > interval) {
    // save last time
    previousMillis = currentMillis;
  }p

  if ( timer < interval/3) {
    yellow();
  } else if (timer < 2*interval/3) {
    color(100,100,100);
  } else {
    color(0,255,255);
  }
}
