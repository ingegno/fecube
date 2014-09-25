
const int ledR = 10;
const int ledG = 11;
const int ledB = 12;
// Bottom/Top - Left/Right - Aft/Front
int ledBLA=1; int ledTLA=2; int ledBLF=3; int ledTLF=4;
int ledMID=5; int ledTRF=6; int ledBRA=8; int ledTRA=7;
int ledBRF=9;


long previousMillis = 0;

long interval = 2000;

bool ALLOWDIM = false;

void setup() {

 pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT); pinMode(ledB,OUTPUT);
 pinMode(ledBLA,OUTPUT);  pinMode(ledBLF,OUTPUT); pinMode(ledBRA,OUTPUT);
 pinMode(ledBRF,OUTPUT); pinMode(ledMID,OUTPUT); pinMode(ledTLA,OUTPUT);
 pinMode(ledTLF,OUTPUT); pinMode(ledTRA,OUTPUT); pinMode(ledTRF,OUTPUT);
  
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
