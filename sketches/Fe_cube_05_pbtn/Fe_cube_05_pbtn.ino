/*
Controlling a simple led via a pushbutton

 Note: on most Arduinos there is already a LED on the board
 attached to pin 13 so you could leave the LED out
*/ 
 
#define buttonPin  2 // the number of the pushbutton pin
#define ledPin    13 // the number of the LED pin

// variable that changes
int buttonState = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);      
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}

void loop(){
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // if the pushbutton is pressed, the buttonState is HIGH:
  if (buttonState == HIGH) {     
    // turn LED on:    
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW); 
  }
}
