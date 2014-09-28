/*
Controlling a FE Cube - intelligent patterns
*/

#ifndef FECUBE_H
#define FECUBE_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#define __PROG_TYPES_COMPAT__   // define needed for older arduino avr !
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

// pins used, avoid use of memory to store it:
#define ledR 10
#define ledG 11
#define ledB 12
// led anodes are connected to pins via a resistor
#define ledBLA 1
#define ledTLA 2
#define ledBLF 3
#define ledTLF 4
#define ledMID 5
#define ledTRA 6
#define ledTRF 7
#define ledBRA 8
#define ledBRF 9

// pushbutton pin
#define buttonPin 13

const int ledorder[] = {ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID};
// counter in array ledorder
const int cTLF = 0; const int cTLA = 1; const int cTRF = 2; const int cTRA = 3; const int cBLF = 4;
const int cBLA = 5; const int cBRF = 6; const int cBRA = 7; const int cMID = 8;
const int colorder[] = {ledR, ledG, ledB};
const int cR = 0; const int cG = 1; const int cB = 2;

bool ALLOWDIM = false;

bool test = false;  //use serial monitor for testing (slows down update rate!)

/*************************************************/
/*       Simple functions                        */
/*************************************************/
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

void fecube_clearframe(int frame[27]) {
  for (int ind=0; ind < 27; ind++){
    frame[ind] = 0;
  }
}

void fecube_set_frame(int frame1[27], int frame2[27]) {
  for (int ind=0; ind < 27; ind++){
    frame1[ind] = frame2[ind];
  }
}
 
void fecube_set_ledcolor(int led, int R_1, int G_1, int B_1, int frame[27]) {
  frame[led*3+cR] = R_1; frame[led*3+cG] = G_1;frame[led*3+cB] = B_1;
}

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
void fecube_setup() {
  if (test) {
    Serial.begin(9600);
  }
  randomSeed(analogRead(0));
  pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT); pinMode(ledB,OUTPUT);
  pinMode(ledBLA,OUTPUT);  pinMode(ledBLF,OUTPUT); pinMode(ledBRA,OUTPUT);
  pinMode(ledBRF,OUTPUT); pinMode(ledMID,OUTPUT); pinMode(ledTLA,OUTPUT);
  pinMode(ledTLF,OUTPUT); pinMode(ledTRA,OUTPUT); pinMode(ledTRF,OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);     
}


/*************************************************/
/*       General effects                         */
/*************************************************/

void fecube_switch_off(unsigned long framenr, int frame[27]){
  //shot: switch the cube off, allow inputsampling to continue
  for (int ind=0; ind < 27; ind++){
    frame[ind] = 0;
  }
  // too avoid too much cycling we switch off, and delay somewhat
  all_led_off();
  delay(35);
}

// show numbers on the cube
void one(int frame[27], int color){
  //switch leds corresponding with the color and number 1
  frame[8*3+color] = 255;
}
void two(int frame[27], int color){
  //switch leds corresponding with the color and number 2
  frame[1*3+color] = 255; frame[2*3+color] = 255;
}
void three(int frame[27], int color){
  //switch leds corresponding with the color and number 3
  frame[8*3+color] = 255; frame[0*3+color] = 255; frame[7*3+color] = 255;
}
void four(int frame[27], int color){
  //switch leds corresponding with the color and number 4
  frame[0*3+color] = 255; frame[1*3+color] = 255; frame[2*3+color] = 255;
  frame[3*3+color] = 255;
}
void five(int frame[27], int color){
  //switch leds corresponding with the color and number 5
  frame[8*3+color] = 255; frame[0*3+color] = 255; frame[1*3+color] = 255;
  frame[6*3+color] = 255; frame[7*3+color] = 255;
}
void six(int frame[27], int color){
  //switch leds corresponding with the color and number 6
  frame[4*3+color] = 255; frame[5*3+color] = 255; frame[6*3+color] = 255;
  frame[7*3+color] = 255; frame[0*3+color] = 255; frame[3*3+color] = 255;
}

/*************************************************/
/*       Flag setting functions                  */
/*************************************************/

int NREFFECT = 0;

void fecube_set_starteffectnr(int val) {
  NREFFECT = val;
}

void fecube_allowdim(bool val) {
  ALLOWDIM = val;
}

//maximum number of effects: 20 (increasing this increases memory use !!
const int fecube_maxnreffects = 20;
//actual number set by user
int fecube_nreffects;
void (*fecube_effects[fecube_maxnreffects])(unsigned long, int[27]);
unsigned long fecube_effect_duration[fecube_maxnreffects];

void fecube_set_effects(const int nreffects, void (*effects[])(unsigned long, int[27]), unsigned long effect_duration[]) {
  fecube_nreffects = nreffects;
  for (int ind=0; ind < nreffects; ind++){
    fecube_effects[ind] = effects[ind];
    fecube_effect_duration[ind] = effect_duration[ind];
  }
}

//effect to show on double press (shown once, then stops)
void (*fecube_dblpress_effect)(long unsigned int, int*) = fecube_switch_off;
unsigned long fecube_dblpress_duration = 10000UL;
void fecube_set_dblpress_effect(unsigned long duration, void (*effect)(unsigned long, int[27])) {
  fecube_dblpress_duration = duration;
  fecube_dblpress_effect = effect;
}

//effect to show on long press
void (*fecube_longpress_effect)(long unsigned int, int*) = fecube_switch_off;
unsigned long fecube_longpress_duration = 1000UL;
void fecube_set_longpress_effect(unsigned long duration, void (*effect)(unsigned long, int[27])) {
  fecube_longpress_duration = duration;
  fecube_longpress_effect = effect;
}
 
 
unsigned long shotduration = 0UL;
// hook function to change duration of an effect. Use with care, normally
// shot duration is set by user in the effect duration list. Use this function 
// for effects with difficult to know duration, so you can change is programmatically
void fecube_set_shotduration(unsigned long val) {
    shotduration = val;
}

/*************************************************/
/*       Input sampling code                     */
/*************************************************/

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
    allowInput = false;
  }
}


/*************************************************/
/*      Support for pattern effects              */
/*************************************************/

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
int extend_pattern = 2;             // extend the pattern this number of times
// effect to apply, use as last duration
//  0: no effect;  -1: reverse the entire pattern
//-11: shift colors one right; -12: shift colors two right
//-90, -180, -270: rotate over those angles
int pattern_starteffect = 0;

//internally used variables, don't change:
boolean PATTERNFINISHED = true;
int PREVPATTERN = 0;
float patternscale = patternscale_start;
unsigned int patternrepeat = 0;
unsigned int curpattern = 0;
int nrextends = 0;
int revert = 1;
int pattern_effect=pattern_starteffect;

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

void apply_shot_effect(){
  //apply an effect on the shot
  if (pattern_effect == -11){
    rotateRGB_shot();
  } else if (pattern_effect == -12){
    rotateRGB_shot();
    rotateRGB_shot();
  } else if (pattern_effect == -90){
    rotate_shot();
  } else if (pattern_effect == -180){
    rotate_shot();
    rotate_shot();
  } else if (pattern_effect == -270){
    rotate_shot();
    rotate_shot();
    rotate_shot();
  } 
}


void fecube_pattern_effect(unsigned long framenr, float scale_start, float scale_speedup,
            float scale_min, unsigned int repeat_min, int extend, int starteffect,
            void (*load_pattern_function)(unsigned int, int*, int[28])
                          ) {
  // if frame 0, we load the correct pattern, and then continue with fixed_pattern
  // for all frames of the computed duration. 
  // next time we have frame 0, we shift to the next line, and repeat!
  if (framenr == 0 ) {
    // we obtain the current pattern:
    if (PATTERNFINISHED) {
        nrextends = 0;
        curpattern = 0;
        //first call, set variabls
        patternscale_start  = scale_start;
        patternscale_speedup= scale_speedup;
        patternscale_min    = scale_min;
        patternrepeatmin    = repeat_min;
        extend_pattern      = extend;
        pattern_starteffect = starteffect;
        
        //reset start in case it changed
        pattern_effect = pattern_starteffect;
        patternscale = patternscale_start;
        PATTERNFINISHED = false;
    }
    int nextduration = 0;
    load_pattern_function(curpattern, &nextduration, shotpattern);
            
    apply_shot_effect();
    
    //overrule user set duration, this is a pattern, we read duration from 
    // the pattern
    fecube_set_shotduration(round(shotpattern[27] * patternscale));
    
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
          pattern_effect = pattern_starteffect;
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
        if (pattern_effect == -11 && nextduration == -11){
            pattern_effect = -12;
        } else if (pattern_effect == -12 && nextduration == -11){
            pattern_effect = 0;
        } else if (pattern_effect == -90) {
            if (nextduration == -90){
            pattern_effect = -180;
            } else if (nextduration == -180) {
            pattern_effect = -270;
            } else if (nextduration == -270) {
            pattern_effect = 0;
            } else {
            pattern_effect = nextduration;
            }
        } else if (pattern_effect == -180) {
            if (nextduration == -90){
            pattern_effect = -270;
            } else if (nextduration == -180) {
            pattern_effect = 0;
            } else if (nextduration == -270) {
            pattern_effect = -90;
            } else {
            pattern_effect = nextduration;
            }
        } else if (pattern_effect == -270) {
            if (nextduration == -90){
            pattern_effect = 0;
            } else if (nextduration == -180) {
            pattern_effect = -90;
            } else if (nextduration == -270) {
            pattern_effect = -180;
            } else {
            pattern_effect = nextduration;
            }
        } else {
            pattern_effect = nextduration;
        }
        if (pattern_effect == -1 || curpattern == 0){
            //we revert the pattern
            revert = -revert;
            pattern_effect = pattern_starteffect;
            if (!(curpattern == 0)) {
            curpattern = curpattern - 2;
            } 
        } else {
            curpattern = 0;
        }
      }
    }
  }
}

/*************************************************/
/*       The application: an Fe Cube             */
/*************************************************/

/***************************************************************************
A shot consists of frames which are shown 40ms. We determe in the loop if
a new frame must be drawn.

General outline animation architecture 

1. A movie is a sequence of shots.
2. A shot/effect has a duration expressed in ms. The action will be split up in 
   frames to give the illusion of smooth change. 
2. A frame is a fixed pattern that repeats for 1/25 of a second. The human
   eye can only see 24 images per second, so one frame every 1/25 seconds
   can give the illusion of smooth movement/change
   Frames themself are drawn from subframes
3. To create a frame, multiplexing will be needed. This is the act of
   combining individual light outputs so as to create the single frame.
   Eg, an RGB led cannot show R, G and B at the same time, so 
   these must be shown serial. Likewise, a led cube might not have the power
   output to drive a complete cube in one subframe. So a subframe is one 
   output of a loop in arduino.  A cycle of subrames creates a frame. 
   The cycle is repeated for the duration of the frame.
***************************************************************************/
unsigned long movietime = 0UL;


void (*movie(unsigned long *shotduration))(unsigned long, int[27]){
  // when a shot is finished, movie() is called to obtain the next shot.
  unsigned long curmovietime = millis();
  switch (NREFFECT) {
    case 666:
      //Double click effect
      *shotduration = fecube_dblpress_duration;
      //this shot is shown once, prepare for end:
      NREFFECT = PREVPATTERN;
      PATTERNFINISHED = true;
      return fecube_dblpress_effect;
      break;
    case 9999:
      //long press effect
      *shotduration = fecube_longpress_duration;
      return fecube_longpress_effect;
      break;
    default:
      //we show effect for the NREFFECT
      if (NREFFECT >= fecube_nreffects) {
        NREFFECT = 0;
      }
      *shotduration = fecube_effect_duration[NREFFECT];
      return fecube_effects[NREFFECT];
  }
}

/***************************************************************************
       THE REST IS THE GENERAL FRAMEWORK TO SHOW FRAMES ACCORDING TO
            WHAT YOU WANTED

***************************************************************************/
//global variables needed
unsigned long startTime = 0UL;
unsigned long currentTime;
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


void show_subframe_color(int color, long microtime, unsigned long subfrcycleduration){
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  all_led_off();
  //switch on correct color
  digitalWrite(colorder[color], HIGH);
  //see which led on and which not in order 
  //ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID
  int scale = 1;
  for (int ledind=0; ledind<9; ledind++){
    // colors are 0 to 255, but we use only 0 to 64, therefore, divide by 4 ! 
    if (ALLOWDIM == false) {
      //rescale the color to a max of 255 over the colors.
      int maxval = max(curframe[3*ledind + 0],max(curframe[3*ledind + 1],curframe[3*ledind + 2]));
      if (maxval >=1 ) {
        scale = 255/maxval;
      }
    }
    if (microtime < subfrcycleduration * int((curframe[3*ledind + color] + 1)/4) * scale) {
      digitalWrite(ledorder[ledind], LOW); //LED is on.
    }
  }
}

void fecube_loop(){
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
      NREFFECT += 1;
      PATTERNFINISHED = true;
      break;
    case EXTREMEPRESS:
      //switch on or off
      if (NREFFECT == 9999) {
        NREFFECT = PREVPATTERN;  //back on
        if (NREFFECT == 9999){NREFFECT = 0;}
      } else {
        PREVPATTERN = NREFFECT;
        NREFFECT = 9999; //off
      }
      PATTERNFINISHED = true;
      break;
    case DOUBLEPRESS:
      //we run 3 D6 dices, show result for some time, then restart
      PREVPATTERN = NREFFECT;
      NREFFECT = 666;
      PATTERNFINISHED = true;
      break;
    default:
      newshot = false;
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


#endif
