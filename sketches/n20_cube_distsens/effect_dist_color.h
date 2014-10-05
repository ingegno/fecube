/*
Controlling a FE Cube - intelligent patterns

This effect can show a fixed color, a random color, or a smooth transition from
a color to a next color
*/

#ifndef EFFECTDISTCOLOR_H
#define EFFECTDISTCOLOR_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#include "fecube.h"


/*************************************************/
/*       Show the set fixed color for the 
/*       entire duration, if dist sensor changes 
/*       values, we automatically have changing 
/*       colors
/*************************************************/


void effect_dist_color(unsigned long framenr, int frame[27]){
  //shot: show a fixed color stored in global variables:
  if (framenr == 0) {
    // make sure distance sens updates first color which we use
    color_to_update = 1;
  }
  for (int ind=0; ind < 9; ind++){
    frame[ind*3]   = dist_colorR1;
    frame[ind*3+1] = dist_colorG1;
    frame[ind*3+2] = dist_colorB1;
  }
}

void effect_dist_color2(unsigned long framenr, int frame[27]){
  //shot: show a fixed color stored in global variables:
  if (framenr == 0) {
    // make sure distance sens updates second color which we use
    color_to_update = 2;
  }
  for (int ind=0; ind < 9; ind++){
    frame[ind*3]   = dist_colorR2;
    frame[ind*3+1] = dist_colorG2;
    frame[ind*3+2] = dist_colorB2;
  }
}

void effect_dist_color3(unsigned long framenr, int frame[27]){
  //shot: show a fixed color stored in global variables:
  if (framenr == 0) {
    // make sure distance sens updates first color which we use
    color_to_update = 3;
  }
  for (int ind=0; ind < 9; ind++){
    frame[ind*3]   = dist_colorR3;
    frame[ind*3+1] = dist_colorG3;
    frame[ind*3+2] = dist_colorB3;
  }
}

#endif
