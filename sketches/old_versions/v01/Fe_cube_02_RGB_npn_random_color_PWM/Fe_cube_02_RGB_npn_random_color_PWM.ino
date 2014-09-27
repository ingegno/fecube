/*
Controlling an RGB led via an npn switches and PWM
Here a random color is shown for 1 sec
*/
// pins used:
int ledR=11;
int ledG=10;
int ledB=9;
int led1=2;
// delay for each PWM. Play with it: 1, 4, 10
int delayDuration = 4;
// testing
bool test = true; //set = true for monitor!

// global variables to hold the color state of a led1
long randR, randG, randB;

//we need access to current time frequently
unsigned long currentTime = millis();
unsigned long prevTime;

void setup()  {
  //for debugging we set up serial communication. This uses pins 0 and 1!
  Serial.begin(9600);
  // we use analog pin 0 as input for random seed generator.
  // randomSeed() will shuffle the random function.
  randomSeed(analogRead(0));
  // define the pins we use for the RGB led, not needed for PWM feeds !
  pinMode(led1, OUTPUT);
}


void loop(){
  digitalWrite(led1, HIGH);
  analogWrite(ledR, 0);
  analogWrite(ledG, 0);
  analogWrite(ledB, 0); 
  randR = random(256); // randR = 5;
  randG = random(256); // randG = 252;
  randB = random(256); // randB = 9;
  if (test) {
    Serial.print("color: "); Serial.print(randR); Serial.print(" - ");
    Serial.print(randG); Serial.print(" - "); Serial.println(randB);
  }
    
  // showing we need access to the time:
  currentTime = millis();
  prevTime = currentTime;
  // For 1 second we show the randR,randG,randB color:
  while (currentTime - prevTime < 1000) {   
    // We cycle through the R, G and B part, and show each color for 
    // a fixed delayDuration time 
    analogWrite(ledR, randR);
    delay(delayDuration);
    analogWrite(ledR, 0);
    analogWrite(ledG, randG);
    delay(delayDuration);
    analogWrite(ledG, 0);
    analogWrite(ledB, randB);
    delay(delayDuration);
    analogWrite(ledB, 0);
    currentTime = millis(); 
  }
}

