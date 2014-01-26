/*
Controlling an RGB led via an npn switch and digital switching
using a frame abstraction to show smooth transistion
*/

// pins used
int ledR=11;
int ledG=10;
int ledB=9;
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
   combining individual light outputs so as to create the single frame.
   Eg, an RGB led cannot show R, G and B at the same time, so 
   these must be shown serial. Likewise, a led cube might not have to power
   output to drive a complete cube in one subframe. So a subframe is one 
   output of a loop in arduino.  A cycle of subrames creates a frame. 
   The cycle is repeated for the duration of the frame.
***************************************************************************/

long random_colorR = 0; // global variables
long random_colorG = 0;
long random_colorB = 0;

void fixed_color(unsigned long framenr, int frame[3]){
  //shot: show a fixed color stored in global variables:
  frame[0] = random_colorR;
  frame[1] = random_colorG;
  frame[2] = random_colorB;
}

void random_color(unsigned long framenr, int frame[3]){
  //shot: a random color for a specific duration
  if (framenr == 0) {
    //determine the random color we will use
   random_colorR = int(random(65));
   random_colorG = int(random(65));
   random_colorB = int(random(65));
  }
  //store the random color in the frame
  frame[0] = random_colorR;
  frame[1] = random_colorG;
  frame[2] = random_colorB;
}

long smooth_colorR, smooth_colorG, smooth_colorB; // global variables
unsigned int smooth_color_transition_duration = 10000;
unsigned int fixed_color_duration = 5000;

void smooth_color(unsigned long framenr, int frame[3]){
  //shot: shows a color, then goes smooth to a new color
  unsigned int last_fixed_frame = fixed_color_duration/40;
  unsigned int last_trans_frame = (smooth_color_transition_duration +
                fixed_color_duration) / 40;
  unsigned int smooth_frame_length = last_trans_frame - last_fixed_frame;
  if (framenr < last_fixed_frame) {
    //show the fixed color
    fixed_color(framenr, frame);
  } else if (framenr == last_fixed_frame){
    // finished first color, we determine what will be our next color
    smooth_colorR = int(random(65));
    smooth_colorG = int(random(65));
    smooth_colorB = int(random(65));
    fixed_color(framenr, frame);
  } else if(framenr < last_trans_frame) {
    // we compute how much to mix both colors
    float blend = (framenr - last_fixed_frame) /  float(smooth_frame_length);
    frame[0] = round((1-blend) * random_colorR + blend * smooth_colorR);
    frame[1] = round((1-blend) * random_colorG + blend * smooth_colorG);
    frame[2] = round((1-blend) * random_colorB + blend * smooth_colorB);
  } else {
    //we have (framenr >= last_trans_frame)
    //so finished, we end with last color showing it fixed
    random_colorR = smooth_colorR;
    random_colorG = smooth_colorG;
    random_colorB = smooth_colorB;
    fixed_color(framenr, frame);
  }
}

void (*movie(unsigned long *shotduration))(unsigned long, int[3]){
  // when a shot is finished, movie() is called to obtain the next shot. 
  // a color, smooth transition, and another color, so duration:
  *shotduration = smooth_color_transition_duration + 2 * fixed_color_duration;
  return smooth_color;
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
bool          newframe = true;
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
    cursubframecycle = (curmicrotime - startTime) / 960UL; //960=3*5*64
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
 
