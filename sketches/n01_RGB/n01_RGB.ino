
const int ledPinR =  8;
const int ledPinG =  9;
const int ledPinB = 10;

int ledStateR = LOW;
int ledStateG = LOW;
int ledStateB = LOW;
long previousMillis = 0;

long interval = 3000;

void setup() {
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
}

void loop()
{
  unsigned long currentMillis = millis();
  unsigned long timer = currentMillis - previousMillis;
  if (timer > interval) {
    // save last time
    previousMillis = currentMillis;
  }

  if ( timer < interval/3) {
    ledStateR = HIGH;
    ledStateG = LOW;
    ledStateB = LOW;
  } else if (timer < 2*interval/3) {
    ledStateR = LOW;
    ledStateG = HIGH;
    ledStateB = LOW;
  } else {
    ledStateR = LOW;
    ledStateG = LOW;
    ledStateB = HIGH;
  }
  // set the LED D
  digitalWrite(ledPinR, ledStateR);
  digitalWrite(ledPinG, ledStateG);
  digitalWrite(ledPinB, ledStateB);
}
