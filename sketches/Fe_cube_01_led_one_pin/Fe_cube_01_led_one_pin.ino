/*
Controlling a simple led via anode current interrupt

Schematic:  GND to LED kathode (-), LED anode to resistor R1, 
            R1 to pin led1
            Use correct R1, Arduino at 5V and led of 3V will require typically R1=220 - 500 Ohm
*/

// led anode (+) is connected to 2, 
// led kathode is connected to GND
int led1=2;

// we can control the led in one way:
//  1. we can interrupt the current coming from the anode via pin led1

void setup()  {
 pinMode(led1,OUTPUT);
}

void loop(){
 digitalWrite(led1,HIGH); //current on
 delay(1000);  // 1 sec = 1000 millisec delay

 digitalWrite(led1,LOW);  //current off
 delay(1000);
}
