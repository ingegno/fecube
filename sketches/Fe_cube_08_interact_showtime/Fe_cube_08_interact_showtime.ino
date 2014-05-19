/*
Controlling a FE Cube - intelligent patterns
*/
#define __PROG_TYPES_COMPAT__   // define needed for older arduino avr !
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

// pins used, avoid use of memory to store it:
#define ledR 10
#define ledG 11
#define ledB 12
// led anodes are connected to pins via a resistor
// Bottom/Top - Left/Right - Aft/Front
#define ledBLA 1
#define ledTLA 4
#define ledBLF 3
#define ledTLF 2
#define ledMID 5
#define ledTRF 8
#define ledBRA 7
#define ledTRA 6
#define ledBRF 9
// pushbutton pin
#define btnpin 13
//distance sensor Trig and Echo
#define trigPin A0
#define echoPin A1

const int ledorder[] = {ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID};
const int colorder[] = {ledR, ledG, ledB};

//time state of the loop
unsigned long currentTime_mus = 0UL;
unsigned long currentTime;

/*************************************************/
/*       Pattern for Fe Cube                     */
/*************************************************/

const PROGMEM prog_int16_t PatternSnake[] = {
//a color based snake order led: color + brightness as points
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
//snake with color 1 then 2
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  1000,
 0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  1000,
 //now color 2
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  1000,
 0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  -11
};


const PROGMEM prog_int16_t PatternSnakeRGB[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
//snake red
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  1000,
 0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -11
};


const PROGMEM prog_int16_t PatternHeart[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  5, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 15, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 20, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 25, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 35, 0, 0,  1000,
 1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0, 45, 0, 0,  1000,
 5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0, 45, 0, 0,  1000,
15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 55, 0, 0,  1000,
25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 64, 0, 0,  1000,
35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 64, 0, 0,  1000,
45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 64, 0, 0,  1000,
55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 64, 0, 0,  1000,
64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0,  1000,
64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -1
};


const PROGMEM prog_int16_t PatternSiren[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
 0, 0, 7,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 7,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,   100,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -90
};

#define test false //use serial monitor for testing (slows down update rate!)

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
/*       variables for dist sensor interaction   */
/*************************************************/
//activate distance sensor or not
#define USE_DIST true
//speed of sound in air in cm/micros
#define SPEED_SOUND 0.034
//the max distance in cm we want to measure
#define MAX_DIST 15.
//the distance under which you can't see
#define MIN_DIST 3.5

//control scheme to use to control the LED via dist sensor
#define DSTCTRL_SCALED 0  // color depending on distance hand
#define DSTCTRL_TIMED  1  // color depending on time hand held in place
#define DSTCTROL DSTCTRL_TIMED

//resolution for dist measurements in microseconds
#define DIST_MEAS_RESO 500000UL  //500 ms
//timeout to wait for echo pulse in microseconds
unsigned long timeout_echo = (2* MAX_DIST+1) / SPEED_SOUND;
//storage variables:
int duration;
float distance = 0, old_distance = 0;
unsigned long brightness = 0UL;
unsigned long last_dist_meas = 0UL;
//by default the color that is controlled is color 1
int color_to_update = 1;
bool dotrig = false;
//4 scale vals from min to max
#define DSTSCALE_BR_MIN    MIN_DIST
#define DSTSCALE_BR_MAX    MIN_DIST + (MAX_DIST-MIN_DIST)/4.
#define DSTSCALE_BLUE_MIN  DSTSCALE_BR_MAX
#define DSTSCALE_BLUE_MAX  DSTSCALE_BLUE_MIN + (MAX_DIST-MIN_DIST)/4.
#define DSTSCALE_GREEN_MIN DSTSCALE_BLUE_MAX
#define DSTSCALE_GREEN_MAX DSTSCALE_GREEN_MIN + (MAX_DIST-MIN_DIST)/4.
#define DSTSCALE_RED_MIN   DSTSCALE_GREEN_MAX
#define DSTSCALE_RED_MAX   DSTSCALE_RED_MIN + (MAX_DIST-MIN_DIST)/4.

/*************************************************/
/*       Setup code                              */
/*************************************************/
void setup() {
  if (test) {
    Serial.begin(9600);
  }
 randomSeed(analogRead(0));
 pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT); pinMode(ledB,OUTPUT);
 pinMode(ledBLA,OUTPUT);  pinMode(ledBLF,OUTPUT); pinMode(ledBRA,OUTPUT);
 pinMode(ledBRF,OUTPUT); pinMode(ledMID,OUTPUT); pinMode(ledTLA,OUTPUT);
 pinMode(ledTLF,OUTPUT); pinMode(ledTRA,OUTPUT); pinMode(ledTRF,OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(btnpin, INPUT);
  // initialize the distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

/*************************************************/
/*       Input sampling code pushbutton          */
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
  if (test && event != BTNFIXED){
    Serial.print(presstype);Serial.print(" ");
    Serial.println(timepressed - prevtimereleased);
  }
  // presstype has been set. The app should process it and set it to NOPRESS
}


/*************************************************/
/*       The application: an Fe Cube             */
/*************************************************/

/***************************************************************************
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
unsigned long movietime = 0UL;

/** FIRST FUNCTIONS BASED ON EQUAL COLORS FOR ALL LED **/
int random_colorR = 64; // global variables
int random_colorG = 0;
int random_colorB = 0;
//color 2
int random_colorR2 = 0; // global variables
int random_colorG2 = 64;
int random_colorB2 = 0;
//color 3
int random_colorR3 = 0; // global variables
int random_colorG3 = 0;
int random_colorB3 = 64;

void fixed_color(unsigned long framenr, int frame[27]){
  //shot: show a fixed color stored in global variables:
  for (int ind=0; ind < 9; ind++){
    frame[ind*3]   = random_colorR;
    frame[ind*3+1] = random_colorG;
    frame[ind*3+2] = random_colorB;
  }
}

void random_color(unsigned long framenr, int frame[27]){
  //shot: a random color for a specific duration
  if (framenr == 0) {
    //determine the random color we will use
   random_colorR = int(random(65));
   random_colorG = int(random(65));
   random_colorB = int(random(65));
  }
  //store the random color in the frame
  fixed_color(framenr, frame);
}

int smooth_colorR, smooth_colorG, smooth_colorB; // global variables
unsigned int smooth_color_transition_duration = 10000;
unsigned int fixed_color_duration = 5000;

void smooth_color(unsigned long framenr, int frame[27]){
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
    for (int ind=1; ind < 9; ind++){
      frame[ind*3]   = frame[0];
      frame[ind*3+1] = frame[1];
      frame[ind*3+2] = frame[2];
    }
  } else {
    //we have (framenr >= last_trans_frame)
    //so finished, we end with last color showing it fixed
    random_colorR = smooth_colorR;
    random_colorG = smooth_colorG;
    random_colorB = smooth_colorB;
    fixed_color(framenr, frame);
  }
}

/** NEXT FUNCTIONS BASED ON ALL LED DIFFERENT **/
int shotpattern[28] = {0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0,0,0, 0};
// same but based on fixed color and brightness
int shotpatterncolor[19] = {0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0,0, 0};

void fixed_pattern(unsigned long framenr, int frame[27]){
  //shot: show a fixed pattern stored in global variables:
  for (int ind=0; ind < 27; ind++){
    frame[ind] = shotpattern[ind];
  }
}

#define P_TYPE_UNDEF 0 // Unknown pattern type
#define P_TYPE_FULL  1 // Pattern via full RGB value
#define P_TYPE_COLOR 2 // Pattern via a color number + brightness
int patterntype=0;                  // what type of pattern? FULL or COLOR?
float patternscale_start   = 1.;    // scale time of pattern with this amount
float patternscale_speedup = 0.75;  // every repeat, time is multiplied with this
float patternscale_min     = 0.002; // min value of patternscale
unsigned int patternrepeatmin = 250;// how many times to repeat min value before restart
int totalpatterns  = 1;             // how many patterns in our movie.
int extend_pattern = 2;             // extend the pattern this number of times
// effect to apply, use as last duration
//  0: no effect;  -1: reverse the entire pattern
//-11: shift colors one right; -12: shift colors two right
//-90, -180, -270: rotate over those angles
int starteffect = 0;


#define MAX_NRSHOT 7
#define START_SHOT 5
//internally used variables, don't change:
boolean PATTERNFINISHED = true;
int NRPATTERN = START_SHOT;
int PREVPATTERN = 0;
float patternscale = patternscale_start;
unsigned int patternrepeat = 0;
unsigned int curpattern = 0;
int nrextends = 0;
int revert = 1;
int effect=starteffect;

void (*moviepattern(unsigned long *shotduration))(unsigned long, int[27]){
  // we obtain the current pattern:
  if (PATTERNFINISHED) {
    nrextends = 0;
    curpattern = 0;
    if (NRPATTERN > MAX_NRSHOT) {
      NRPATTERN = 0;
    }
    switch (NRPATTERN) {
      case 0:
        //first call, we load the snake pattern
        patterntype = P_TYPE_FULL;
        // red, green, blue
        patternscale_start = 1.;
        patternscale_speedup = 0.75;
        patternscale_min = 0.002;
        patternrepeatmin = 250;
        extend_pattern = 2;
        starteffect = 0;
        break;
      case 1:
        // blue and red
        patterntype = P_TYPE_COLOR;
        starteffect = 0;
        extend_pattern = 0;
        patternscale_start = 1.;
        patternscale_speedup = 0.75;
        patternscale_min = 0.002;
        patternrepeatmin = 250;
        break;
      case 2:
        // green and blue
        patterntype = P_TYPE_FULL;
        starteffect = -11;
        break;
      case 3:
        // green back - forth
        patterntype = P_TYPE_FULL;
        starteffect = -11;
        extend_pattern = 1;
        break;
      case 4:
        // beating heart
        patterntype = P_TYPE_FULL;
        patternscale_start = 0.15;
        starteffect = 0;
        extend_pattern = 1;
        patternscale_speedup = 0.9;
        patternscale_min = 0.01;
        patternrepeatmin = 200;
        break;
      case 5:
        //Siren
        patterntype = P_TYPE_FULL;
        patternscale_start = 1.;
        starteffect = 0;
        extend_pattern = 3;
        patternscale_speedup = 1.;
        patternscale_min = 1.;
        patternrepeatmin = 50;
        break;
      case 6:
      case 7:
        // no pattern, shot handled in movie
        break;
    }
    //reset start in case it changed
    effect = starteffect;
    patternscale = patternscale_start;
    PATTERNFINISHED = false;
  }
  int nextduration = 0;
  for (int ind=0; ind < 28; ind++){
    switch (NRPATTERN) {
      case 1:
        if (ind < 19) {
          shotpatterncolor[ind] = pgm_read_word_near(PatternSnake+19*curpattern + ind);
          nextduration = pgm_read_word_near(PatternSnake +19*(curpattern + 2) - 1);
        }
        break;
      case 0:
      case 2:
        shotpattern[ind] = pgm_read_word_near(PatternSnakeRGB +28*curpattern + ind);
        nextduration = pgm_read_word_near(PatternSnakeRGB +28*(curpattern + 2) - 1);
        break;
      case 3:
        shotpattern[ind] = pgm_read_word_near(PatternSnakeRGB +28*curpattern + ind);
        nextduration = pgm_read_word_near(PatternSnakeRGB +28*(curpattern + 2) - 1);
        // we override the effect as we want reverse!
        if (nextduration <= 0) {
          nextduration = -1;
        }
        break;
      case 4:
        shotpattern[ind] = pgm_read_word_near(PatternHeart +28*curpattern + ind);
        nextduration = pgm_read_word_near(PatternHeart +28*(curpattern + 2) - 1);
        break;
      case 5:
        shotpattern[ind] = pgm_read_word_near(PatternSiren +28*curpattern + ind);
        nextduration = pgm_read_word_near(PatternSiren +28*(curpattern + 2) - 1);
        break;
    }
  }
  if (patterntype == P_TYPE_FULL){
    apply_shot_effect();
    *shotduration = round(shotpattern[27] * patternscale);
  } else {
    // color based pattern
    apply_shot_effect_color();
    *shotduration = round(shotpatterncolor[18] * patternscale);
  }
  //next time show next pattern
  curpattern += revert;
  if (nextduration <= 0 || curpattern == 0){
    //pattern table finished, restart table with an extend if asked, 
    //otherwise start from start with a speedup if required.
    if (nrextends == extend_pattern){
      // finished extending, start from 0, do speedup if requested.
      nrextends = 0;
      curpattern = 0;
      revert = 1;
      effect = starteffect;
      patternscale *= patternscale_speedup;
      if (patternscale <= patternscale_min){
        // repeat the minimum scale a given number of times
        patternrepeat += 1;
        if (patternrepeat > patternrepeatmin){
          PATTERNFINISHED = true;
          patternscale = patternscale_start;
          patternrepeat = 0;
        } else {
          patternscale = patternscale_min;
        }
      }
    } else {
      //extend the pattern, prepare to do an effect
      nrextends += 1;
      if (effect == -11 && nextduration == -11){
        effect = -12;
      } else if (effect == -12 && nextduration == -11){
        effect = 0;
      } else if (effect == -90) {
        if (nextduration == -90){
         effect = -180;
        } else if (nextduration == -180) {
          effect = -270;
        } else if (nextduration == -270) {
          effect = 0;
        } else {
          effect = nextduration;
        }
      } else if (effect == -180) {
        if (nextduration == -90){
         effect = -270;
        } else if (nextduration == -180) {
          effect = 0;
        } else if (nextduration == -270) {
          effect = -90;
        } else {
          effect = nextduration;
        }
      } else if (effect == -270) {
        if (nextduration == -90){
         effect = 0;
        } else if (nextduration == -180) {
          effect = -90;
        } else if (nextduration == -270) {
          effect = -180;
        } else {
          effect = nextduration;
        }
      } else {
        effect = nextduration;
      }
      if (effect == -1 || curpattern == 0){
        //we revert the pattern
        revert = -revert;
        effect = starteffect;
        if (!(curpattern == 0)){
          curpattern = curpattern - 2;
        } 
      } else {
        curpattern = 0;
      }
    }
  }
  return fixed_pattern;
}

void apply_shot_effect_color(){
  //we have a color based pattern, we convert to normal pattern, then apply shot
  int tmp1,tmp2;
  for (int indsh=0; indsh < 9; indsh++){
    tmp1 = shotpatterncolor[2*indsh];
    tmp2 = shotpatterncolor[2*indsh+1];
    if (tmp1 == 1) {
      //color 1, brightness tmp2 is scale from 0 to 10
      shotpattern[3*indsh]   = int(random_colorR * tmp2/10.);
      shotpattern[3*indsh+1] = int(random_colorG * tmp2/10.);
      shotpattern[3*indsh+2] = int(random_colorB * tmp2/10.);
      color_to_update = 1;
    } else if (tmp1 == 2) {
      //color 2
      shotpattern[3*indsh]   = int(random_colorR2 * tmp2/10.);
      shotpattern[3*indsh+1] = int(random_colorG2 * tmp2/10.);
      shotpattern[3*indsh+2] = int(random_colorB2 * tmp2/10.);
      color_to_update = 2;
    } else if (tmp1 == 3) {
      //color 3
      shotpattern[3*indsh]   = int(random_colorR3 * tmp2/10.);
      shotpattern[3*indsh+1] = int(random_colorG3 * tmp2/10.);
      shotpattern[3*indsh+2] = int(random_colorB3 * tmp2/10.);
      color_to_update = 3;
    } else { //0 or undefined, no color to show
      //color 1, brightness tmp2 is scale from 0 to 10
      shotpattern[3*indsh]   = 0;
      shotpattern[3*indsh+1] = 0;
      shotpattern[3*indsh+2] = 0;
    }
  }
  apply_shot_effect();
}

void apply_shot_effect(){
  //apply an effect on the shot
  if (effect == -11){
    rotateRGB_shot();
  } else if (effect == -12){
    rotateRGB_shot();
    rotateRGB_shot();
  } else if (effect == -90){
    rotate_shot();
  } else if (effect == -180){
    rotate_shot();
    rotate_shot();
  } else if (effect == -270){
    rotate_shot();
    rotate_shot();
    rotate_shot();
  } 
}

void rotateRGB_shot(){
  int tmp;
  for (int indsh=0; indsh < 9; indsh++){
    tmp = shotpattern[3*indsh+2];
    shotpattern[3*indsh+2] = shotpattern[3*indsh+1];
    shotpattern[3*indsh+1] = shotpattern[3*indsh];
    shotpattern[3*indsh] = tmp;
  }
}

void rotate_shot(){
  //map ledorder is {0, 1, 2, 3, 4, 5, 6, 7, 8} in shotpattern:
  //ledTLF, ledTLA, ledTRF, ledTRA, ledBLF, ledBLA, ledBRF, ledBRA, ledMID
  //goes to rotatemap with the new positions in shotpattern
  //ledTRF, ledTLF, ledTRA, ledTLA, ledBRF, ledBLF, ledBRA, ledBLA, ledMID
  const int rotatemap[9] = {2, 0, 3, 1, 6, 4, 7, 5, 8};
  int shotcopy[27];
  for (int indsh=0; indsh < 27; indsh++){
    shotcopy[indsh] = shotpattern[indsh];
  }
  for (int indsh=0; indsh < 9; indsh++){
    shotpattern[3*rotatemap[indsh]]   = shotcopy[3*indsh];
    shotpattern[3*rotatemap[indsh]+1] = shotcopy[3*indsh+1];
    shotpattern[3*rotatemap[indsh]+2] = shotcopy[3*indsh+2];
  }
}

void switch_off(unsigned long framenr, int frame[27]){
  //shot: switch the cube off, allow inputsampling to continue
  for (int ind=0; ind < 27; ind++){
    frame[ind] = 0;
  }
  // too avoid too much cycling we switch off, and delay somewhat
  all_led_off();
  delay(35);
}

void one(int frame[27], int color){
  //switch leds corresponding with the color and number 1
  frame[8*3+color] = 64;
}
void two(int frame[27], int color){
  //switch leds corresponding with the color and number 2
  frame[1*3+color] = 64; frame[2*3+color] = 64;
}
void three(int frame[27], int color){
  //switch leds corresponding with the color and number 3
  frame[8*3+color] = 64; frame[0*3+color] = 64; frame[7*3+color] = 64;
}
void four(int frame[27], int color){
  //switch leds corresponding with the color and number 4
  frame[0*3+color] = 64; frame[1*3+color] = 64; frame[2*3+color] = 64;
  frame[3*3+color] = 64;
}
void five(int frame[27], int color){
  //switch leds corresponding with the color and number 5
  frame[8*3+color] = 64; frame[0*3+color] = 64; frame[1*3+color] = 64;
  frame[6*3+color] = 64; frame[7*3+color] = 64;
}
void six(int frame[27], int color){
  //switch leds corresponding with the color and number 6
  frame[4*3+color] = 64; frame[5*3+color] = 64; frame[6*3+color] = 64;
  frame[7*3+color] = 64; frame[0*3+color] = 64; frame[3*3+color] = 64;
}

int D6R = 0; int D6G = 0; int D6B = 0;

void rolldice(unsigned long framenr, int frame[27]){
  //shot: 3d6 dices rolling, 2 sec rolling, 6 sec show value
  // 
  int rolseconds = 2;
  int showduration = 6;
  int showvalduration = 1;  //seconds to show val
  if (framenr == 0) {
    randomSeed(millis());
    D6R = random(1,7);D6G = random(1,7);D6B = random(1,7);
  }
  if (framenr < rolseconds * 25UL) {
    //first 50, every 5 frames a new pattern, this is rolling
    if (framenr % 5 == 0) {
      for (int ind=0; ind < 9; ind++){
        //determine if on or off
        if (random(2) == 0) {
          frame[ind*3] = 0;frame[ind*3+1] = 0;frame[ind*3+2] = 0;
        } else {
          //on, determine color
          frame[ind*3] = 0;frame[ind*3+1] = 0;frame[ind*3+2] = 0;
          int add = random(3);
          frame[ind*3+add] = 64;
        }
      }
    }
  } else {
    for (int ind=0; ind < 27; ind++){
      frame[ind] = 0;
    }
    //every half second another color
    int color = (framenr-rolseconds * 25UL) % (3*25UL*showvalduration);
    int val = 0;
    if (color < 25UL*showvalduration){
      color = 0;
      val = D6R;
    } else if (color < 2*25UL*showvalduration) {
      color = 1;
      val = D6G;
    } else { color = 2; val = D6B;
    }
    if (val == 1) {one(frame, color);}
    if (val == 2) {two(frame, color);}
    if (val == 3) {three(frame, color);}
    if (val == 4) {four(frame, color);}
    if (val == 5) {five(frame, color);}
    if (val == 6) {six(frame, color);}
  }
}

void (*movie(unsigned long *shotduration))(unsigned long, int[27]){
  // when a shot is finished, movie() is called to obtain the next shot.
  color_to_update = 1;  //by default only base color to update via dist sensor
  unsigned long curmovietime = millis();
  switch (NRPATTERN) {
    case 666:
      //roll 3 dices
      *shotduration = 8000UL;
      //this shot is shown once, prepare for end:
      NRPATTERN = PREVPATTERN;
      PATTERNFINISHED = true;
      return rolldice;
      break;
    case 9999:
      //switch off
      *shotduration=1000;
      return switch_off;
      break;
    case 6:
      //smooth random color
      *shotduration = smooth_color_transition_duration + 2 * fixed_color_duration;
      return smooth_color;
    case 7:
      //fixed interactive color
      *shotduration = 10000;
      return fixed_color;
    default:
      //we show a pattern:
      return moviepattern(shotduration);
  }
}


/*************************************************/
/*       Dist Sensor functions                   */
/*************************************************/

float meas_dist(){
  if (test) {
      Serial.print(currentTime_mus);Serial.print(" ");Serial.print(last_dist_meas);Serial.print(" ");Serial.print((currentTime_mus-last_dist_meas < 1500000UL));
      Serial.println("");
      delay(500);
    }
  // measure distance once every xx seconds
  if (currentTime_mus-last_dist_meas < DIST_MEAS_RESO){
    dotrig = true;
    //release the function, return to the loop
    return distance;
  }
  if (dotrig == true){
    dotrig = false;
    // read the distance. Prepare to emit sound
    digitalWrite(trigPin, HIGH);
  }
  //minimum of 10 microsec of delay needed
  //delayMicroseconds(100); // Note: not allowed for the real cube to delay!!
  // for code with no delays, use:
  if (currentTime_mus-last_dist_meas < DIST_MEAS_RESO + 100UL){
    // release to the loop, too early to trigger sound 
    return distance;
  }
  //we waited long enough, determine new distance, emit sound (8x40kHz pulses):
  digitalWrite(trigPin, LOW);
  //catch echo, determine distance
  duration = pulseIn(echoPin, HIGH, timeout_echo);
  //Notice: Out of range == 0 cm!
  distance = (duration/2) * SPEED_SOUND;
  if (distance < MIN_DIST || distance > MAX_DIST){
    //out of range
    if (test) {
      Serial.println("Niets gezien");
      delay(500);
    }
    old_distance = distance;
    distance = 0.;
  } else {
    if (test) {
      Serial.print("Iets gezien op "); Serial.print(distance); Serial.println(" cm"); 
      delay(500);
    }
    // Set color values 
    dist_to_brightness();
    dist_to_color();
    old_distance = distance;
  }
  //set time of this dist meas, so it does not happen again too fast
  last_dist_meas = micros();
  return distance;
}

void dist_to_brightness(){
  if (DSTCTROL == DSTCTRL_TIMED) {
    //convert time held in place into brightness value in (0,10)
    if (distance >=DSTSCALE_BR_MIN && distance <= DSTSCALE_BR_MAX ) {
      if (old_distance >=DSTSCALE_BR_MIN && old_distance <= DSTSCALE_BR_MAX ) {
        //second measurement here, we increase brightness one
        brightness += 1;
        if (brightness >10) brightness = 0;
      }
    }
  } else {
    //convert distance into brightness value in (0,10)
    if (distance == 0) {
      return;
    }
    //normalized distance in [0,20]
    brightness = (MAX_DIST-distance) * 10/(MAX_DIST-MIN_DIST);
  }
}

void dist_to_color(){
  
  if (DSTCTROL == DSTCTRL_TIMED) {
    //convert time held in place into brightness value in (0,10)
    if (distance >= DSTSCALE_BR_MIN && distance <= DSTSCALE_BR_MAX ) {
      //if (old_distance >= DSTSCALE_BR_MIN && old_distance <= DSTSCALE_BR_MAX ) 
      {
        //second measurement here, we increase brightness one
        switch (color_to_update) {
          case 2:
            random_colorR2 -= 6;random_colorG2 -= 6;random_colorB2 -= 6;
            if (random_colorR2 < 0) random_colorR2 = 0;
            if (random_colorG2 < 0) random_colorG2 = 0;
            if (random_colorB2 < 0) random_colorB2 = 0;
            if (random_colorR2 == 0 && random_colorG2 == 0 && random_colorB2 == 0) {
              //switch off
              random_colorR2 = 64-random(0,5);random_colorG2 = 64-random(0,5);random_colorB2 = 64-random(0,5);
            }
            break;
          case 3:
            random_colorR3 -= 6;random_colorG2 -= 6;random_colorB2 -= 6;
            if (random_colorR3 < 0) random_colorR3 = 0;
            if (random_colorG3 < 0) random_colorG3 = 0;
            if (random_colorB3 < 0) random_colorB3 = 0;
            if (random_colorR3 == 0 && random_colorG3 == 0 && random_colorB3 == 0) {
              //switch off
              random_colorR3 = 64-random(0,5);random_colorG3 = 64-random(0,5);random_colorB3 = 64-random(0,5);
            }
            break;
          default:
            random_colorR -= 6;random_colorG -= 6;random_colorB -= 6;
            if (random_colorR < 0) random_colorR = 0;
            if (random_colorG < 0) random_colorG = 0;
            if (random_colorB < 0) random_colorB = 0;
            if (random_colorR == 0 && random_colorG == 0 && random_colorB == 0) {
              //switch off
              random_colorR = 64-random(0,5);random_colorG = 64-random(0,5);random_colorB = 64-random(0,5);
            }
            break;
        }
      }
    } else if (distance >= DSTSCALE_BLUE_MIN && distance <= DSTSCALE_BLUE_MAX ) {
      //if (old_distance >= DSTSCALE_BLUE_MIN && old_distance <= DSTSCALE_BLUE_MAX ) 
      {
        //second measurement here, we increase blue by one
        switch (color_to_update) {
          case 2:
            random_colorB2 += 6;
            if (random_colorB2 >64) random_colorB2 = random(0,5);
          case 3:
            random_colorB3 += 6;
            if (random_colorB3 >64) random_colorB3 = random(0,5);
          default:
            random_colorB += 6;
            if (random_colorB >64) random_colorB = random(0,5);
        }
      }
    } else if (distance >= DSTSCALE_GREEN_MIN && distance <= DSTSCALE_GREEN_MAX ) {
      //if (old_distance >= DSTSCALE_GREEN_MIN && old_distance <= DSTSCALE_GREEN_MAX ) 
      {
        //second measurement here, we increase greed by one
        switch (color_to_update) {
          case 2:
            random_colorG2 += 6;
            if (random_colorG2 >64) random_colorG2 = random(0,5);
          case 3:
            random_colorG3 += 6;
            if (random_colorG3 >64) random_colorG3 = random(0,5);
          default:
            random_colorG += 6;
            if (random_colorG >64) random_colorG = random(0,5);
        }
      }
    } else if (distance >= DSTSCALE_RED_MIN && distance <= DSTSCALE_RED_MAX ) {
      //if (old_distance >= DSTSCALE_RED_MIN && old_distance <= DSTSCALE_RED_MAX ) 
      {
        //second measurement here, we increase red by one
        switch (color_to_update) {
          case 2:
            random_colorR2 += 6;
            if (random_colorR2 >64) random_colorR2 = random(0,5);
          case 3:
            random_colorR3 += 6;
            if (random_colorR3 >64) random_colorR3 = random(0,5);
          default:
            random_colorR += 6;
            if (random_colorR >64) random_colorR = random(0,5);
        }
      }
    }
  } else {
    //convert distance into RGB value
    if (distance == 0) {
      return;
    }
    //first cm to switch off color
    if (distance < MIN_DIST + 1){
        switch (color_to_update) {
          case 2:
          random_colorR2 = 0;
          random_colorG2 = 0;
          random_colorB2 = 0;
          case 3:
          random_colorR3 = 0;
          random_colorG3 = 0;
          random_colorB3 = 0;
          default:
          random_colorR = 0;
          random_colorG = 0;
          random_colorB = 0;
        }
    }
    //normalized distance in [0,9]
    float norm_dist = (MAX_DIST-distance) * 9/(MAX_DIST-(MIN_DIST+1));
    if (norm_dist <= 3){
      //RED: value from 0 to 64
        switch (color_to_update) {
          case 2:
            random_colorR2 = int(norm_dist/3*64);
          case 3:
            random_colorR3 = int(norm_dist/3*64);
          default:
            random_colorR = int(norm_dist/3*64);
        }
    } else if (norm_dist <= 6) {
      //GREEN
        switch (color_to_update) {
          case 2:
            random_colorG2 = int((norm_dist-3)/3*64);
          case 3:
            random_colorG3 = int((norm_dist-3)/3*64);
          default:
            random_colorG  = int((norm_dist-3)/3*64);
        }
    } else{
      //BLUE
        switch (color_to_update) {
          case 2:
            random_colorB2 = int((norm_dist-6)/3*64);
          case 3:
            random_colorB3 = int((norm_dist-6)/3*64);
          default:
            random_colorB = int((norm_dist-6)/3*64);
        }
    }
  }
}

/***************************************************************************
       THE REST IS THE GENERAL FRAMEWORK TO SHOW FRAMES ACCORDING TO
            WHAT YOU WANTED

***************************************************************************/
//global variables needed
unsigned long startTime = 0UL;
unsigned long shotduration = 0UL;
//shotptr       curshot;
void (*curshot)(long unsigned int, int*);
int           curframe[27];
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
  currentTime_mus = micros();
  bool newshot = true;
  switch (presstype) {
    case NOPRESS:
      if (currentTime - startTime < shotduration) {
        //no new shot yet
        newshot = false;
        }
      break;
    case SHORTPRESS:
      //increase the pattern number to show new pattern
      NRPATTERN += 1;
      PATTERNFINISHED = true;
      break;
    case EXTREMEPRESS:
      //switch on or off
      if (NRPATTERN == 9999) {
        NRPATTERN = PREVPATTERN;  //back on
        if (NRPATTERN == 9999){NRPATTERN = 0;}
      } else {
        PREVPATTERN = NRPATTERN;
        NRPATTERN = 9999; //off
      }
      PATTERNFINISHED = true;
      break;
    case DOUBLEPRESS:
      //we run 3 D6 dices, show result for some time, then restart
      PREVPATTERN = NRPATTERN;
      NRPATTERN = 666;
      PATTERNFINISHED = true;
      break;
    default:
      newshot = false;
  }
  //consider presstype handled:
  presstype = NOPRESS;
  //obtain distance with distance sensor
  if (USE_DIST) {
    distance = meas_dist();
  } else {
    distance = 0;
  }
  //produce shot if needed
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
  unsigned long subfrcycleduration = 70UL; //tweak this for best behavior,60 to 150UL, in 1/64ths
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
    cursubframecycle = (curmicrotime - starttimeframe) / (subfrcycleduration * 64UL); //960=3*5*64
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
  show_subframe_color(subframecolor, curmicrotime - subframestarttime, subfrcycleduration);
}

void show_subframe_color(int color, long microtime, unsigned long subfrcycleduration){
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  all_led_off();
  //switch on correct color
  digitalWrite(colorder[color], HIGH);
  //see which led on and which not in order 
  //ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID
  for (int ledind=0; ledind<9; ledind++){
    if (microtime < subfrcycleduration * curframe[3*ledind + color]) {
      digitalWrite(ledorder[ledind], LOW);
    }
  }
}

void all_led_off(){
 digitalWrite(ledBLA,HIGH); digitalWrite(ledBLF,HIGH);
 digitalWrite(ledBRA,HIGH); digitalWrite(ledBRF,HIGH);
 digitalWrite(ledMID,HIGH); digitalWrite(ledTLA,HIGH);
 digitalWrite(ledTLF,HIGH); digitalWrite(ledTRA,HIGH);
 digitalWrite(ledTRF,HIGH);
}

void all_led_on(){
 digitalWrite(ledBLA,LOW); digitalWrite(ledBLF,LOW);
 digitalWrite(ledBRA,LOW); digitalWrite(ledBRF,LOW);
 digitalWrite(ledMID,LOW); digitalWrite(ledTLA,LOW);
 digitalWrite(ledTLF,LOW); digitalWrite(ledTRA,LOW);
 digitalWrite(ledTRF,LOW);
}
