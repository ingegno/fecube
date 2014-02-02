/*
Controlling a FE Cube
*/

// pins used
int ledR=10; int ledG=11; int ledB=12;
// led anodes are connected to pins via a resistor
// Bottom/Top - Left/Right - Aft/Front
int ledBLA=1; int ledTLA=2; int ledBLF=3; int ledTLF=4;
int ledMID=5; int ledTRF=6; int ledBRA=7; int ledTRA=8;
int ledBRF=9;

bool test = false;  //use serial monitor for testing.

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
unsigned long movietime = 0UL;
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
  unsigned long curmovietime = millis();
  if (test) {
    Serial.print("shot ");
    Serial.print(curmovietime - movietime); Serial.print(" ");
    Serial.print(curmovietime); Serial.print(" ");
  }
  if (curmovietime - movietime > 2*60*1000UL  + 3*4000UL){
    //start the movie again from the start.
    movietime = curmovietime;
  }
  if (curmovietime - movietime < 4000UL) {
    //4 seconds red
    *shotduration = 4000;
    random_colorR = 64; random_colorG = 0; random_colorB = 0;
    return fixed_color;
  } else if (curmovietime - movietime < 8000UL) {
    //4 seconds green
    *shotduration = 4000;
    random_colorR = 0; random_colorG = 64; random_colorB = 0;
    return fixed_color;
  } else if (curmovietime - movietime < 12000UL) {
    //4 seconds blue
    *shotduration = 4000;
    random_colorR = 0; random_colorG = 0; random_colorB = 64;
    return fixed_color;
  } else if (curmovietime - movietime < 12000UL + 60UL * 1000UL) {
    //random color for 1 min, with 1 sec for a random color
    *shotduration = 1000;
    return random_color;
  } else {
    // one minitue smooth transitions each 4 sec
    smooth_color_transition_duration = 3000;
    fixed_color_duration = 500;
    // a color, smooth transition, and another color, so duration:
    *shotduration = smooth_color_transition_duration + 2 * fixed_color_duration;
    return smooth_color;
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
int           curframe[3];
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
      subframecolor += 1;
      subframecolor = subframecolor % 3;
    }
  }
  //we know the frame, the color, and how far in the subframe we are
  show_subframe_color(subframecolor, curmicrotime - subframestarttime, subfrcycleduration);
}

void show_subframe_color(int color, unsigned long microtime, unsigned long subfrcycleduration){
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  all_led_on();
  if (color == 0) {
    if (microtime < subfrcycleduration * curframe[0]) {
      digitalWrite(ledR, HIGH);
    }
  } else if (color == 1) {
    if (microtime < subfrcycleduration * curframe[1]) {
      digitalWrite(ledG, HIGH);
    }
  } else {
    if (microtime < subfrcycleduration * curframe[2]) {
      digitalWrite(ledB, HIGH);
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
