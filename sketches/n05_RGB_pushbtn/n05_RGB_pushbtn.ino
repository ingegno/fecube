
#define buttonPin 12
#define ledPinB   13

int ledStateB = LOW;
int buttonState = LOW;
int buttonStatePrev = LOW;
long previousMillis = 0;

long interval;


void setup() {
  pinMode(buttonPin, OUTPUT);
  pinMode(ledPinB, OUTPUT);
}


void effect1() {
  unsigned long timer = millis() - previousMillis;
  
  if ( timer < interval/3) {
    ledStateB = LOW;
  } else if (timer < 2*interval/3) {
    ledStateB = LOW;
  } else {
    ledStateB = HIGH;
  }
}

void effect2() {
  ledStateB = HIGH;
}

void effect3() {
  ledStateB = LOW;
}

void effect4() {
  unsigned long timer = millis() - previousMillis;
  //dim effect
  if ( timer < interval/3) {
    ledStateB = LOW;
  } else if (timer < 2*interval/3) {
    ledStateB = LOW;
  } else {
    ledStateB = HIGH;
  }
}

const int nreffects = 4;
int showeffect = 0;
void (*effects[nreffects])() = {effect1, effect2, effect3, effect4};
long intervals[nreffects] = {3000,3000,3000,3};

void loop()
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // if the pushbutton is pressed, increase effect to show:
  if (buttonState == HIGH) {
    if (buttonStatePrev == LOW) {
      showeffect += 1;
      if (showeffect >= nreffects) {
        showeffect = 0;
      }
    }
  }
  buttonStatePrev = buttonState;
  
  unsigned long currentMillis = millis();
  unsigned long timer = currentMillis - previousMillis;
  interval = intervals[showeffect];
  if (timer > interval) {
    // save last time
    previousMillis = currentMillis;
  }

  // show correct effect
  (*effects[showeffect])();
  
  // set computed state
  digitalWrite(ledPinB, ledStateB);
}
