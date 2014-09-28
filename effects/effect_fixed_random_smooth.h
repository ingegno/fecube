/*
Controlling a FE Cube - intelligent patterns

This effect can show a fixed color, a random color, or a smooth transition from
a color to a next color
*/

#ifndef EFFECTFIXEDRANDOMSMOOTH_H
#define EFFECTFIXEDRANDOMSMOOTH_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#include "fecube.h"

/** FIRST FUNCTIONS BASED ON EQUAL COLORS FOR ALL LED **/
long fixed_colorR = 0; // global variables
long fixed_colorG = 0;
long fixed_colorB = 0;

long random_colorR = 0; // global variables
long random_colorG = 0;
long random_colorB = 0;


/*************************************************/
/*       Show the set fixed color for the 
/*       entire duration
/*************************************************/

//set the color to use in th fixed duration
void set_fixed_color(int R_1, int G_1, int B_1) {
    fixed_colorR = R_1;
    fixed_colorG = G_1;
    fixed_colorB = B_1;
}

void effect_fixed_color(unsigned long framenr, int frame[27]){
  //shot: show a fixed color stored in global variables:
  if (framenr == 0) {
      random_colorR = fixed_colorR;
      random_colorG = fixed_colorG;
      random_colorB = fixed_colorB;
  }
  for (int ind=0; ind < 9; ind++){
    frame[ind*3]   = random_colorR;
    frame[ind*3+1] = random_colorG;
    frame[ind*3+2] = random_colorB;
  }
}


/*************************************************/
/*       Show a random color for the 
/*       entire duration
/*************************************************/
void effect_random_color(unsigned long framenr, int frame[27]){
  //shot: a random color for a specific duration
  if (framenr == 0) {
    //determine the random color we will use
   random_colorR = int(random(256));
   random_colorG = int(random(256));
   random_colorB = int(random(256));
  }
  //store the random color in the frame
  effect_fixed_color(1, frame);
}

/*************************************************
 *       Show the color for a firstcolor_duration,
 *       then show a transition to a second random
 *       color for a transition_duration, then show
 *       this second color up to end of the 
 *       entire duration
 *       Durations in milliseconds !
/*************************************************/

long smooth_colorR, smooth_colorG, smooth_colorB; // global variables
unsigned int smooth_color_transition_duration = 10000;
unsigned int fixed_color_duration = 5000;

void set_smooth_color_durations(unsigned int firstcolor_duration, unsigned int transition_duration) {
    fixed_color_duration = firstcolor_duration;
    smooth_color_transition_duration = transition_duration;
}

void effect_smooth_color(unsigned long framenr, int frame[27]){
  //shot: shows a color, then goes smooth to a new color
  unsigned int last_fixed_frame = fixed_color_duration/40;
  unsigned int last_trans_frame = (smooth_color_transition_duration +
                fixed_color_duration) / 40;
  unsigned int smooth_frame_length = last_trans_frame - last_fixed_frame;
  if (framenr < last_fixed_frame) {
    //show the last used random color
    effect_fixed_color(1, frame);
  } else if (framenr == last_fixed_frame){
    // finished first color, we determine what will be our next color
    smooth_colorR = int(random(256));
    smooth_colorG = int(random(256));
    smooth_colorB = int(random(256));
    effect_fixed_color(framenr, frame);
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
    effect_fixed_color(framenr, frame);
  }
}


#endif
