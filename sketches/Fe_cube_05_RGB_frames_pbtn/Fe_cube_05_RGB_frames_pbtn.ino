/*
Controlling an RGB led via an npn switch and digital switching
using a frame abstraction
*/

// pins used
int ledR=11;
int ledG=10;
int ledB=9;
int led1=2;

#define btnpin  3  //de pin die pushbutton leest

bool test = false;  //use serial monitor for testing.

int NRSHOT = 0;    //shot number to start with
int PREVSHOT = 0;
int MAXSHOT = 3;   //maximum shot number

/*************************************************/
/*       variables for input sampling            */
/*************************************************/
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

/*************************************************/
/*       Setup code                              */
/*************************************************/
void setup() {
  if (test) {
    Serial.begin(9600);
  }
  randomSeed(analogRead(0));
  // define the pins we use for the RGB led
  pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT);
  pinMode(ledB,OUTPUT); pinMode(led1,OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(btnpin, INPUT);
}


/*************************************************/
/*       Input sampling code                     */
/*************************************************/

void inputsampling(){
  //read the pushbutton if allowed
  if (allowInput) {
    if (presstype == NOPRESS) {
      btnStatePrev = btnState;
      btnState = digitalRead(btnpin);
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
    allowInput = false;
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
  if (test){// && event != BTNFIXED){
    Serial.print(presstype);Serial.print(" ");
    Serial.println(timepressed - prevtimereleased);
    delay(100);
  }
  // presstype has been set. The app should process it and set it to NOPRESS
}

/***************************************************************************
We consider the effect (a random color for 1 second) to be a shot or action.
A shot consists of frames which are shown 40ms. We determe in the loop if
a new frame must be drawn.

General outline animation architecture 

1. A movie is a sequence of shots.
2. A shot has a duration expressed in ms. The action will be split up in 
   frames to give the illusion of smooth change. 
2. A frame is a fixed pattern that repeats for 1/25 of a second. The human
   eye can only see 24 images per second, so one frame every 1/25 seconds
   can give the illusion of smooth movement/change
   Frames themself are drawn from subframes
3. To create a frame, multiplexing will be needed. This is the act of
   combining individual light outputs to create a single frame.
   Eg, an RGB led cannot show R, G and B at the same time, so these must be
   shown in serie. For the same reason, a led cube might not have to power
   output to drive a complete cube in one subframe. So a subframe is one 
   output of a loop in arduino.  A cycle of subrames creates a frame. 
   The cycle is repeated for the duration of the frame.
***************************************************************************/
unsigned long movietime = 0UL;
//our first shot: a random color for a specific duration
long random_colorR = 0;
long random_colorG = 0;
long random_colorB = 0; // global variables

void random_color(unsigned long framenr, int frame[3]){
  //update the frame for the time shown
  if (framenr == 0) {
    //determine the random color we will use
   random_colorR = int(random(65));
   random_colorG = int(random(65));
   random_colorB = int(random(65));
   if (test) {
     Serial.print("New random color:");
     Serial.print(random_colorR * 4);Serial.print(" ");
     Serial.print(random_colorG * 4);Serial.print(" ");
     Serial.print(random_colorB * 4);Serial.print(" at time ");
     Serial.println(millis()/1000.);
   }
  }
  //store the random color in the frame
  frame[0] = random_colorR;
  frame[1] = random_colorG;
  frame[2] = random_colorB;
  //to test: hard code colors here:
  //frame[0] = 0; frame[1] = 0; frame[2] = 64;
}


void blink_color(unsigned long framenr, int frame[3]){
  //update the frame for the time shown
  if (framenr <25 ) {
    frame[0] = 64;
    frame[1] = 0;
    frame[2] = 64;
  } else {
    frame[0] = 0;
    frame[1] = 0;
    frame[2] = 0;
  }
}

//convert framenr to milliseconds
unsigned long framenr2ms(unsigned long framenr){
  return framenr  * 40;  //40ms per frame
}

int rainbowsinglecolorduration = 20;  //in milliseconds!
unsigned long rainbowshotduration = 255*rainbowsinglecolorduration;
void rainbow(unsigned long framenr, int frame[3]){
  //we show a rainbow effect, every color one second, 255 colors! 
  
  //determine color number that corresponds with the framenr, so which second?
  int color = framenr2ms(framenr) / rainbowsinglecolorduration;
  //in case color is too large, use modulo to put it in interval (0,255)
  color = color % 256;
  
  //we determine a color in the color wheel, number in (0,255) rescaled to (0,64) via /4
  if(color < 85) {
    frame[0] = int(color*3/4); 
    frame[1] = int((255-color*3)/4); 
    frame[2] = 0;
  } else if(color < 170) {
    color -= 85;
    frame[2] = int(color*3/4); 
    frame[0] = int((255-color*3)/4); 
    frame[1] = 0;
  } else {
    color -= 170;
    frame[1] = int(color*3/4); 
    frame[2] = int((255-color*3)/4); 
    frame[0] = 0;
  }
}

void switch_off(unsigned long framenr, int frame[3]){
  //shot: switch off, allow inputsampling to continue
  frame[0] = 0;
  frame[1] = 0;
  frame[2] = 0;
  // too avoid too much cycling we switch off, and delay somewhat
  delay(35);
}

void (*movie(unsigned long *shotduration))(unsigned long, int[3]){
  // when a shot is finished, movie() is called to obtain the next shot.
  
  //first check for possible special shots
  switch (NRSHOT) {
    case 9999:
      //switch off
      *shotduration=1000;
      return switch_off;
      break;
  }
  
  //handle the normal shots:
  if (NRSHOT >= MAXSHOT) {NRSHOT = 0;}
  switch (NRSHOT) {
    case 0:
      // Here we have a single random color, and a fixed duration of 1000 ms.
      *shotduration = 1000UL;
      return random_color;
      break;
    case 1:
      //blink is 2 seconds for one cycle of the shot
      *shotduration = 2000UL;
      return blink_color;
      break;
    case 2:
      //rainbow effect
      *shotduration = rainbowshotduration;
      return rainbow;
    default:
      //we should not get here, if we are here, we switch off
      return switch_off;
  }
  // Here we have a single random color, and a fixed duration of 1000 ms.
  *shotduration = 1000;
  return random_color;
}


/***************************************************************************
           THAT WAS IT! SHORT NO?
           
       THE REST IS THE GENERAL FRAMEWORK TO SHOW FRAMES ACCORDING TO
            WHAT YOU WANTED

***************************************************************************/
//global variables needed
unsigned long startTime = 0UL;
unsigned long currentTime;
unsigned long shotduration = 0UL;
//shotptr       curshot;
void (*curshot)(long unsigned int, int*);
int           curframe[3];
unsigned long framenr = 0UL;
unsigned long curframenr = 1UL;
boolean       newframe = true;
unsigned long starttimeframe = 0UL;
int           subframecolor;
unsigned long subframecycle, cursubframecycle;
unsigned long subframestarttime;
unsigned long curmicrotime;

void loop(){
  //do input sampling 
  inputsampling();
  //first we determine if a new shot must start or not
  currentTime = millis();
  bool newshot = true;
  switch (presstype) {
    case NOPRESS:
      //verder doen met huidige shot, of het herstarten als einde bereikt
      if (currentTime - startTime < shotduration) {
        //no new shot yet
        newshot = false;
        }
      break;
    case SHORTPRESS:
      //increase the pattern number to show new pattern
      NRSHOT += 1;
      break;
    case EXTREMEPRESS:
      //switch on or off
      if (NRSHOT == 9999) {
        NRSHOT = PREVSHOT;  //back on
        if (NRSHOT == 9999){NRSHOT = 0;}
      } else {
        PREVSHOT = NRSHOT;
        NRSHOT = 9999; //off
      }
      break;
    case DOUBLEPRESS:
      //no function for this
      newshot = false;
      break;
    default:
      newshot = false;
  }
  //consider presstype handled:
  presstype = NOPRESS;
  if (newshot) {
    //a new shot
    startTime = millis();
    curshot = movie(&shotduration);
    currentTime = startTime;
    curframenr = 1000UL; //dummy value
  }
  //we obtain the framenumber we should show, one frame=40ms
  unsigned long framenr = (currentTime - startTime)/40UL;
  if (curframenr != framenr){
    //a new frame to show, obtain it
    curshot(framenr, curframe);
    newframe = true;
    starttimeframe = micros();
    curframenr = framenr;
  } else {
    newframe = false;
  }
  // we continue showing a cycle of subframes as needed for the current frame
  curmicrotime = micros();
  if (newframe) {
    //allow input on next sampling
    allowInput = true;
    //reinit the subframes
    subframecolor = 0;
    subframestarttime = curmicrotime;
    subframecycle = 0UL;;
    cursubframecycle = 0UL;
  } else {
    // determine if a new subframecolor is needed
    cursubframecycle = (curmicrotime - starttimeframe) / 960UL; //960=3*5*64
    if (cursubframecycle != subframecycle){
      //new subframecycle
      subframecycle = cursubframecycle;
      subframestarttime = curmicrotime;
      subframecolor = 0;
    } else {
      subframecolor = subframecolor + 1;
      subframecolor = subframecolor % 3;
    }
  }
  //we know the frame, the color, and how far in the subframe we are
  show_subframe_color(subframecolor, curmicrotime - subframestarttime);
}

void show_subframe_color(int color, long microtime){
  // all off
  digitalWrite(led1, HIGH);
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  if (color == 0) {
    if (microtime < 15 * curframe[0]) {
      digitalWrite(ledR, HIGH);
    }
  } else if (color == 1) {
    if (microtime < 15 * curframe[1]) {
      digitalWrite(ledG, HIGH);
    }
  } else {
    if (microtime < 15 * curframe[2]) {
      digitalWrite(ledB, HIGH);
    }
  }
}
 
