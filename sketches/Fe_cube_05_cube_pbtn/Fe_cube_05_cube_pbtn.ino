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

const int ledorder[] = {ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID};
const int colorder[] = {ledR, ledG, ledB};

/*************************************************/
/*       Pattern for Fe Cube                     */
/*************************************************/

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

bool test = false;  //use serial monitor for testing (slows down update rate!)

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
 pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT); pinMode(ledB,OUTPUT);
 pinMode(ledBLA,OUTPUT);  pinMode(ledBLF,OUTPUT); pinMode(ledBRA,OUTPUT);
 pinMode(ledBRF,OUTPUT); pinMode(ledMID,OUTPUT); pinMode(ledTLA,OUTPUT);
 pinMode(ledTLF,OUTPUT); pinMode(ledTRA,OUTPUT); pinMode(ledTRF,OUTPUT);
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
long random_colorR = 0; // global variables
long random_colorG = 0;
long random_colorB = 0;

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

long smooth_colorR, smooth_colorG, smooth_colorB; // global variables
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

void fixed_pattern(unsigned long framenr, int frame[27]){
  //shot: show a fixed pattern stored in global variables:
  for (int ind=0; ind < 27; ind++){
    frame[ind] = shotpattern[ind];
  }
}

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

//internally used variables, don't change:
boolean PATTERNFINISHED = true;
int NRPATTERN = 5;
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
    if (NRPATTERN > 5) {
      NRPATTERN = 0;
    }
    switch (NRPATTERN) {
      case 0:
        //first call, we load the snake pattern
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
        starteffect = -12;
        extend_pattern = 1;
        break;
      case 2:
        // green and blue
        starteffect = -11;
        break;
      case 3:
        // green back - forth
        starteffect = -11;
        extend_pattern = 1;
        break;
      case 4:
        // beating heart
        patternscale_start = 0.15;
        starteffect = 0;
        extend_pattern = 1;
        patternscale_speedup = 0.9;
        patternscale_min = 0.01;
        patternrepeatmin = 200;
        break;
      case 5:
        //Siren
        patternscale_start = 1.;
        starteffect = 0;
        extend_pattern = 3;
        patternscale_speedup = 1.;
        patternscale_min = 1.;
        patternrepeatmin = 50;
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
      case 0:
      case 1:
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
  apply_shot_effect();
  *shotduration = round(shotpattern[27] * patternscale);
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
    default:
      //we show a pattern:
      return moviepattern(shotduration);
  }
}

/***************************************************************************
       THE REST IS THE GENERAL FRAMEWORK TO SHOW FRAMES ACCORDING TO
            WHAT YOU WANTED

***************************************************************************/
//global variables needed
unsigned long startTime = 0UL;
unsigned long currentTime;
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
  }
  //consider presstype handled:
  presstype = NOPRESS;
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
