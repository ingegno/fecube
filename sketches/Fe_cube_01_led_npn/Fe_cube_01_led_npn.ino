/*
Controlling a simple led via an npn switch and a anode current interrupt
*/

// led anode (+) is connected to 2, 
// led kathode is connected to GND via an npn transistor
int led1=2;
// npn transistor control is connected to 11 (middle leg)
int npn=11;

// we can control the led in two ways:
//  1. we can interrupt the GND current to the led via pin npn
//  2. we can interrupt the current coming from the anode via pin led1

void setup()  {
 pinMode(led1,OUTPUT);
 pinMode(npn,OUTPUT);
}

void loop(){
  //we cycle through 3 states.
  //This is on: 
  digitalWrite(led1,HIGH);  
  digitalWrite(npn,HIGH);
  delay(1000);  
  //This is off, no current to led
  digitalWrite(led1,LOW);  
  digitalWrite(npn,HIGH);
  delay(1000);
  //This is off due to NPN
  digitalWrite(led1,HIGH);  
  digitalWrite(npn,LOW);
  delay(1000);
}  
