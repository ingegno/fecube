
#define ledR  10
#define ledG  11
#define ledB  12
// Bottom/Top - Left/Right - Aft/Front
#define ledBLA 1
#define ledTLA 2
#define ledBLF 3
#define ledTLF 4
#define ledMID 5
#define ledTRA 6
#define ledTRF 7
#define ledBRA 8
#define ledBRF 9

#define buttonPin 13

int buttonState = LOW;
int buttonStatePrev = LOW;
long previousMillis = 0;

long interval;

bool ALLOWDIM = false;

void setup() {
  pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT); pinMode(ledB,OUTPUT);
  pinMode(ledBLA,OUTPUT);  pinMode(ledBLF,OUTPUT); pinMode(ledBRA,OUTPUT);
  pinMode(ledBRF,OUTPUT); pinMode(ledMID,OUTPUT); pinMode(ledTLA,OUTPUT);
  pinMode(ledTLF,OUTPUT); pinMode(ledTRA,OUTPUT); pinMode(ledTRF,OUTPUT);
 
  pinMode(buttonPin, OUTPUT);
  
  digitalWrite(ledBLA, HIGH);
  digitalWrite(ledBLF, HIGH);
  digitalWrite(ledBRA, HIGH);
  digitalWrite(ledBRF, HIGH);
  digitalWrite(ledTLA, HIGH);
  digitalWrite(ledTLF, HIGH);
  digitalWrite(ledTRA, HIGH);
  digitalWrite(ledTRF, HIGH);
  digitalWrite(ledMID, HIGH);
}

void LEDs(int R_1, int G_1, int B_1, int R_2, int G_2, int B_2) {
  digitalWrite(ledBLA, LOW);
  color(R_1, G_1, B_1);
  digitalWrite(ledBLA, HIGH);
  digitalWrite(ledBRA, LOW);
  color(R_1, G_1, B_1);
  digitalWrite(ledBRA, HIGH);
  digitalWrite(ledBLF, LOW);
  color(R_1, G_1, B_1);
  digitalWrite(ledBLF, HIGH);
  digitalWrite(ledBRF, LOW);
  color(R_1, G_1, B_1);
  digitalWrite(ledBRF, HIGH);
  
  digitalWrite(ledMID, LOW);
  color(255, 255, 255);
  digitalWrite(ledMID, HIGH);
  
  digitalWrite(ledTLA, LOW);
  color(R_2, G_2, B_2);
  digitalWrite(ledTLA, HIGH);
  digitalWrite(ledTRA, LOW);
  color(R_2, G_2, B_2);
  digitalWrite(ledTRA, HIGH);
  digitalWrite(ledTLF, LOW);
  color(R_2, G_2, B_2);
  digitalWrite(ledTLF, HIGH);
  digitalWrite(ledTRF, LOW);
  color(R_2, G_2, B_2);
  digitalWrite(ledTRF, HIGH);
  
} 

/* Show color of mixing R, G, B as values 0 to 255 */
void color(int R, int G, int B) {
  // we show each unit 2 microseconds
  if (R>0) {
    digitalWrite(ledR, HIGH);
    delayMicroseconds(2*R);
    digitalWrite(ledR, LOW);
  }
  if (G>0) {
    digitalWrite(ledG, HIGH);
    delayMicroseconds(2*G);
    digitalWrite(ledG, LOW);
  }
  if (B>0) {
    digitalWrite(ledB, HIGH);
    delayMicroseconds(2*B);
    digitalWrite(ledB, LOW);
  }
  if (ALLOWDIM)
    delayMicroseconds(2*(255-R)+2*(255-G)+2*(255-B));
}

void effect1()
{
  unsigned long timer = millis() - previousMillis;
  if ( timer < interval/2) {
    LEDs(255, 0, 255, 255, 255, 0);
  } else {
    LEDs(255, 255, 0, 255, 0, 255);
  }
}

void snake()
{ // color of the snake:
  int R_1 = 255;
  int G_1 = 0;
  int B_1 = 0;
  unsigned long timer = millis() - previousMillis;
  //9 LEDs to do
  if ( timer < interval/9) {
    digitalWrite(ledBLA, LOW); color(R_1, G_1, B_1); digitalWrite(ledBLA, HIGH);
  } else if ( timer < 2*interval/9) {
    digitalWrite(ledBLF, LOW); color(R_1, G_1, B_1); digitalWrite(ledBLF, HIGH);
  } else if ( timer < 3*interval/9) {
    digitalWrite(ledBRF, LOW); color(R_1, G_1, B_1); digitalWrite(ledBRF, HIGH);
  } else if ( timer < 4*interval/9) {
    digitalWrite(ledBRA, LOW); color(R_1, G_1, B_1); digitalWrite(ledBRA, HIGH);
  } else if ( timer < 5*interval/9) {
    digitalWrite(ledMID, LOW); color(R_1, G_1, B_1); digitalWrite(ledMID, HIGH);
  } else if ( timer < 6*interval/9) {
    digitalWrite(ledTRA, LOW); color(R_1, G_1, B_1); digitalWrite(ledTRA, HIGH);
  } else if ( timer < 7*interval/9) {
    digitalWrite(ledTRF, LOW); color(R_1, G_1, B_1); digitalWrite(ledTRF, HIGH);
  } else if ( timer < 8*interval/9) {
    digitalWrite(ledTLF, LOW); color(R_1, G_1, B_1); digitalWrite(ledTLF, HIGH);
  } else {
    digitalWrite(ledTLA, LOW); color(R_1, G_1, B_1); digitalWrite(ledTLA, HIGH);
  }
}

const int nreffects = 2;
int showeffect = 0;
void (*effects[nreffects])() = {effect1, snake};
long intervals[nreffects] = {2000,9000};

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
  
}
