/*
Controlling an RGB led via an npn switch and digital switching
using a frame abstraction
*/

// pins used
int ledR=11;
int ledG=9;
int ledB=10;
int led1=2;

bool test = false;  //use serial monitor for testing.

void setup() {
  if (test) {
    Serial.begin(9600);
  }
  randomSeed(analogRead(0));
  // define the pins we use for the RGB led
  pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT);
  pinMode(ledB,OUTPUT); pinMode(led1,OUTPUT);
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
//our first shot: a fixed color for a specific duration (here we show blue)
long fixed_colorR = 0;
long fixed_colorG = 0;
long fixed_colorB = 64; // global variables

void fixed_color(unsigned long framenr, int frame[3]){
    
  //store the color in the frame. Dit is blue want hierboven is blue
  frame[0] = fixed_colorR;
  frame[1] = fixed_colorG;
  frame[2] = fixed_colorB;
 
}

void fixed_groen(unsigned long framenr, int frame[3]){
    // groen
  //store the color in the frame
  frame[0] = 0;
  frame[1] = 64;
  frame[2] = 0;
}

void fixed_BR(unsigned long framenr, int frame[3]){
    // blue en red
  //store the color in the frame
  frame[0] = 64;
  frame[1] = 0;
  frame[2] = 64;
}

// we gaan nu 2 shots tonen: eerst groen en dan BR elke voor 1 seconde, we hebben een 'counter' nodig, we noemen dit nr
int nr=-1;
void (*movie(unsigned long *shotduration))(unsigned long, int[3]){
  // when a shot is finished, movie() is called to obtain the next shot. 
  // Here we have a single random color, and a fixed duration of 3000 ms.
  nr=nr+1; 
  if (nr>1) nr = 0;
  if (nr==0) {
    *shotduration = 1000;
    return fixed_groen;
  } else {
    *shotduration = 1000;
    return fixed_BR;
  }
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
  //first we determine if a new shot must start or not
  currentTime = millis();
  if (currentTime - startTime >= shotduration) {
    //a new shot
    curshot = movie(&shotduration);
    startTime = millis();
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
 
