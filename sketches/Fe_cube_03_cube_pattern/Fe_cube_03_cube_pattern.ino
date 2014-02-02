/*
Controlling a FE Cube - patterns
*/
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

// pins used
int ledR=10; int ledG=11; int ledB=12;
// led anodes are connected to pins via a resistor
// Bottom/Top - Left/Right - Aft/Front
int ledBLA=1; int ledTLA=4; int ledBLF=3; int ledTLF=2;
int ledMID=5; int ledTRF=8; int ledBRA=7; int ledTRA=6;
int ledBRF=9;

int ledorder[] = {ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID};
int colorder[] = {ledR, ledG, ledB};


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
 //snake green
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0,64, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0,64, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0,64, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0,64, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0,64, 0,  1000,
 0, 0, 0,  0,64, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0,64, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0,64, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0,64, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0,64, 0,  1000,
 //snake blue
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0,64,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0,64,  1000,
 0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0,64,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0,64,  1000,
// dummy to end the pattern
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0
  };


const PROGMEM prog_int16_t PatternCircle[] = {
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
 0,20,60,  0,60,20,  0,60,20,  0,20,60,  0,20,60,  0,60,20,  0,60,20,  0,20,60,  0, 0, 0,  150,
 0,60,20,  0,20,60,  0,20,60,  0,60,20,  0,60,20,  0,20,60,  0,20,60,  0,60,20,  0, 0, 0,  150,
// 0,60,20,  0,20,60,  0,20,60,  0,60,20, 30, 0,40, 64,30, 0, 64,30, 0, 30, 0,40,  0, 0, 0,  100,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0
  };


bool test = false;  //use serial monitor for testing (slows down update rate)

void setup() {
  if (test) {
    Serial.begin(9600);
  }
 randomSeed(analogRead(0));
 pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT); pinMode(ledB,OUTPUT);
 pinMode(ledBLA,OUTPUT);  pinMode(ledBLF,OUTPUT); pinMode(ledBRA,OUTPUT);
 pinMode(ledBRF,OUTPUT); pinMode(ledMID,OUTPUT); pinMode(ledTLA,OUTPUT);
 pinMode(ledTLF,OUTPUT); pinMode(ledTRA,OUTPUT); pinMode(ledTRF,OUTPUT);
}

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

float patternscale_start = 1.;        // scale time of pattern with this amount
float patternscale_speedup = 0.75;   // every repeat, time is multiplied with this
float patternscale_min = 0.002;      // min value of patternscale
unsigned int patternrepeatmin = 250; // how many times to repeat min value before restart
int totalpatterns = 2;               // how many patterns in our movie.
//internally used variables, don't change:
boolean PATTERNFINISHED = true;
int NRPATTERN = 0;
float patternscale = patternscale_start;
unsigned int patternrepeat = 0;
unsigned int curpattern = 0;

void (*moviepattern(unsigned long *shotduration))(unsigned long, int[27]){
  // we obtain the current pattern:
  if (PATTERNFINISHED) {
    if (NRPATTERN >= totalpatterns) {NRPATTERN = 0;} //restart
    switch (NRPATTERN) {
      case 0:
        //first call, we load the snake pattern
        patternscale_speedup = 0.75;
        patternscale_min = 0.002;
        patternrepeatmin = 250;
        break;
      case 1:
        //now the circle
        patternscale_speedup = 1.;  //fixed speed
        patternscale_min = 1.;
        patternrepeatmin = 100;     // finished after 500 rotations
        break;
    }
    //reset start in case it changed
    patternscale = patternscale_start;
    PATTERNFINISHED = false;
  }
  int nextduration = 0;
  for (int ind=0; ind < 28; ind++){
    switch (NRPATTERN) {
      case 0:
        shotpattern[ind] = pgm_read_word_near(PatternSnakeRGB +28*curpattern + ind);
        nextduration = pgm_read_word_near(PatternSnakeRGB +28*(curpattern + 2) - 1);
        break;
      case 1:
        shotpattern[ind] = pgm_read_word_near(PatternCircle + 28*curpattern + ind);
        nextduration = pgm_read_word_near(PatternCircle + 28*(curpattern + 2) - 1);
        break;
    }
  }
  *shotduration = round(shotpattern[27] * patternscale);
  //next time show next pattern
  curpattern += 1;  
  //test if this was not last pattern
  if (nextduration == 0){
    //pattern table finished, restart table
    curpattern = 0;
    patternscale *= patternscale_speedup;
    if (patternscale <= patternscale_min){
      patternrepeat += 1;
      if (patternrepeat > patternrepeatmin){
        PATTERNFINISHED = true;
        NRPATTERN += 1;
        patternscale = patternscale_start;
        patternrepeat = 0;
      } else {
        patternscale = patternscale_min;
      }
    }
  }
  return fixed_pattern;
}

void (*movie(unsigned long *shotduration))(unsigned long, int[27]){
  // when a shot is finished, movie() is called to obtain the next shot.
  unsigned long curmovietime = millis();
  //we show a pattern:
  return moviepattern(shotduration);
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
  unsigned long subfrcycleduration = 30UL; //tweak this for best behavior,60 to 150UL, in 1/64ths
  curmicrotime = micros();
  if (newframe) {
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
