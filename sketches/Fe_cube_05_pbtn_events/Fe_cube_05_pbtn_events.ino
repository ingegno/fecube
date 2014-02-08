/*
Controlling a simple led via a pushbutton
*/ 
 
#define buttonPin  2 // the number of the pushbutton pin
#define ledPin    11 // a PWM pin for the LED!

bool test        = false;
// variable that changes
bool allowInput  = true;
int btnStatePrev = LOW;
int btnState     = LOW;

// events
#define BTNFIXED     0    //no change
#define BTNPRESS     1
#define BTNRELEASE   2
unsigned long timepressed  = 0;
unsigned long timereleased = 0;
// button press types
#define NOPRESS      0
#define SHORTPRESS   1
#define LONGPRESS    2
#define DOUBLEPRESS  3
#define EXTREMEPRESS 4

int presstypePrev = NOPRESS;
int presstype     = NOPRESS;
unsigned long prevpresstime = 0;

//sensitivity constants
#define SHORTPRESSMAXDURATION 2000UL
#define LONGPRESSMAXDURATION  4000UL   // 4 seconds
#define DOUBLEPRESSWAIT       500UL    //half a second!


void setup() {    
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
  // LED on PWM pin, no setup needed.
  if (test) {
    Serial.begin(9600);
  }
}

void inputsampling(){
  //read the pushbutton if allowed
  if (allowInput) {
    if (presstype == NOPRESS) {
      btnStatePrev = btnState;
      btnState = digitalRead(buttonPin);
      // handle the events if needed
      eventhandling();
    } else {
      // problem, the previous press type has not been handled yet!
      // note: in our design a SHORTPRESS will be handled even it 
      //       later we change this into a DOUBLEPRESS !
      //if 5 seconds a press is not handled, we remove it
      if (millis()-prevpresstime > LONGPRESSMAXDURATION){
        presstype = NOPRESS;
        presstypePrev  = NOPRESS;
      }
    }
  }
}

void  eventhandling(){
  // process the events to set button press types
  unsigned long currt = millis();
  unsigned long prevtimereleased;
  int event = BTNFIXED;
  if (btnStatePrev != btnState) {
    // an event happened, handle it
    if (btnState == HIGH){
      event = BTNPRESS;
      timepressed = currt;
    } else {
      event = BTNRELEASE;
      prevtimereleased = timereleased;
      timereleased = currt;
    }
  }
  switch (event) {
    case BTNFIXED:
      // if no event, we can have a long press or certain short press
      if (timereleased > 0 && timepressed > timereleased
          && currt - timepressed > LONGPRESSMAXDURATION){
        presstype = EXTREMEPRESS;
        presstypePrev = NOPRESS;
        //avoid double handling of same events
        timepressed = timereleased;
      } else if (timereleased > 0 && presstypePrev == SHORTPRESS 
                  && currt - timereleased > DOUBLEPRESSWAIT){
        presstype = SHORTPRESS;
        presstypePrev = NOPRESS;
      } 
      break;
    case BTNPRESS:
      // button is pressed in, we don't sent a press type for this
      break;
    case BTNRELEASE:
      // button is released, set press type
      if (timereleased - timepressed <= SHORTPRESSMAXDURATION){
        //a short press
        if (presstypePrev == SHORTPRESS 
            && (timepressed - prevtimereleased) < DOUBLEPRESSWAIT) {
          //a double press
          presstype = DOUBLEPRESS;
          presstypePrev = NOPRESS;
        } else {
          //a normal short press, store, will be handled if no double press
          presstype = NOPRESS;
          //remember it in case it will be double press:
          presstypePrev = SHORTPRESS;
        }
      } else if (timereleased - timepressed <= LONGPRESSMAXDURATION){
        // a long press
        presstype = LONGPRESS;
      } // no need for extremelong test, BTNFIXED handles it
  }
  if (test && event != BTNFIXED){
    Serial.print(presstype);Serial.print(" ");
    Serial.println(timepressed - prevtimereleased);
  }
  // presstype has been set. The app should process it and set it to NOPRESS
}

// our app: a led that burns, dims and flickers
unsigned long looptime = 0;
#define LEDOFF     0
#define LEDON      1
#define LEDFLICKER 2
int ledstate = LEDOFF;
unsigned long flickertime = 0;
// 16 dim values
int dimvalue = 16;

void loop(){
  // every 40 ms we read input, and then process it to set the light
  unsigned long currt = millis();
  if (currt - looptime > 40UL) {
    inputsampling();
    looptime = currt;    
  }
  
  // handle button press if present
  switch (presstype) {
    case LONGPRESS:
    case EXTREMEPRESS:
      //switch on or off
      if (ledstate == LEDOFF){
         analogWrite(ledPin, 255);
         dimvalue = 16;
         ledstate = LEDON;
      } else {
         analogWrite(ledPin, 0);
         ledstate = LEDOFF;
      }
      break;
    case SHORTPRESS:
      //short press dims light
      if (ledstate != LEDOFF){
        dimvalue -= 1;
        if (dimvalue < 1) { dimvalue = 16;}
        analogWrite(ledPin, dimvalue*4);
      }
      break;
    case DOUBLEPRESS:
      //we flicker the led
      if (ledstate == LEDFLICKER) {
        ledstate = LEDON;
      } else if (ledstate != LEDOFF){
        ledstate = LEDFLICKER;
        flickertime = currt;
      }
      break;
  }
  presstype = NOPRESS;
  
  //if flicker, we flicker once every half second
  if (ledstate == LEDFLICKER) {
    if (currt - flickertime == 0) {
      analogWrite(ledPin, dimvalue*4); //on
    } else if (currt - flickertime > 1000) {
      analogWrite(ledPin, dimvalue*4); // restart
      flickertime = currt;
    } else if (currt - flickertime > 500) {
      analogWrite(ledPin, 0); //off
    }
  }
}

