/*
Controlling an RGB led via an npn switch and digital switching
using a frame abstraction
*/

#include "frames.h"

// pins used
int ledR=11;
int ledG=10;
int ledB=9;
int led1=2;

bool test = true;  //use serial monitor for testing.

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
   combining individual light outputs so as to create the single frame.
   Eg, an RGB led cannot show R, G and B at the same time, so 
   these must be shown serial. Likewise, a led cube might not have to power
   output to drive a complete cube in one subframe. So a subframe is one 
   output of a loop in arduino.  A cycle of subrames creates a frame. 
   The cycle is repeated for the duration of the frame.
***************************************************************************/

//our first shot: a random color for a specific duration
long random_colorR, random_colorG, random_colorB; // global variables

void random_color(unsigned long framenr, int frame[3]){
  //update the frame for the time shown
  //Serial.print("asking framenr "); Serial.println(framenr);
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
  //frame[0] = 64; frame[1] = 2; frame[2] = 0;
}

shotptr movie(unsigned long *shotduration){
  // when a shot is finished, movie() is called to obtain the next shot. 
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
shotptr       curshot;
int           curframe[3];
unsigned long framenr = 0UL;
unsigned long curframenr = 1UL;
bool          newframe = true;
int           subframecolor, cursubframecolor;
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
    curframenr = framenr;
  } else {
    newframe = false;
  }
  // we continue showing the subframes as needed for the current frame
  curmicrotime = micros();
  if (newframe) {
    //reinit the subframes
    subframecolor = 0;
    subframestarttime = curmicrotime;
  } else {
    // determine if a new subframecolor is needed
    cursubframecolor = (curmicrotime - startTime) / 320UL;  // 320 = 5 * 64
    if (cursubframecolor != subframecolor){
      //new subframe
      subframecolor = cursubframecolor % 3;
      subframestarttime = curmicrotime;
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
    if (microtime < 5 * curframe[0]) {
      digitalWrite(ledR, HIGH);
    }
  } else if (color == 1) {
    if (microtime < 5 * curframe[1]) {
      digitalWrite(ledG, HIGH);
    }
  } else {
    if (microtime < 5 * curframe[2]) {
      digitalWrite(ledB, HIGH);
    }
  }
}
 
