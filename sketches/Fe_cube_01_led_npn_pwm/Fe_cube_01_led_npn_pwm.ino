/*
Brightness is controlled via PWM of a single LED
*/

int led1=2;
// npn transistor control is connected to 11 where we do PWM
int npn=11;

void setup()  {
 // we use analog pin 0 as input for random seed generator. 
 // randomSeed() will shuffle the random function.
 randomSeed(analogRead(0));
 pinMode(led1,OUTPUT);
 //npn pin will be used for PWM, no setup needed!
}

void loop(){
  //we obtain a brightness as a random value between 0 and 255
  int rand = random(256);
  digitalWrite(led1, HIGH);
  // Apply PWM to pin npn, this will result in varying brightness
  analogWrite(npn, rand);
  delay(1000);
}
