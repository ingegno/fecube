/*
Controlling an RGB led via npn switches
*/

// pins used:
int ledR=11;
int ledG=10;
int ledB=9;
int led1=2;

// we can control the led in two ways:
//  1. we can interrupt the GND current to the led via pin npn
//  2. we can interrupt the current coming from the anode via pin led1

void setup()  {
 pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT);
 pinMode(ledB,OUTPUT); pinMode(led1,OUTPUT);
}

void loop(){
 digitalWrite(led1,HIGH);
 //red
 digitalWrite(ledR,HIGH);
 digitalWrite(ledG,LOW);
 digitalWrite(ledB,LOW);
 //green 
 delay(1000);
 digitalWrite(ledR,LOW);
 digitalWrite(ledG,HIGH);
 digitalWrite(ledB,LOW);
 delay(1000);
 //blue
 digitalWrite(ledR,LOW);
 digitalWrite(ledG,LOW);
 digitalWrite(ledB,HIGH);
 delay(1000);
 //Red and Green: normally not working, shows as red
 digitalWrite(ledR,HIGH);
 digitalWrite(ledG,HIGH);
 digitalWrite(ledB,LOW);
 delay(1000);
 //Green and blue
 digitalWrite(ledR,LOW);
 digitalWrite(ledG,HIGH);
 digitalWrite(ledB,HIGH);
 delay(1000);
}  
