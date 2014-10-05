/*
Controlling a FE Cube - intelligent patterns

This effect shows a color with distance
*/

#ifndef EFFECTDISTANCE_H
#define EFFECTDISTANCE_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#include "fecube.h"

float dist_scale;

void effect_distance(unsigned long framenr, int frame[27]){
  //shot: show a fixed color stored in global variables:
  if (framenr == 0) {
    // make sure distance sens updates first color which we use
    color_to_update = 1;
  }
  if (distance>MIN_DIST && distance<MAX_DIST) {
    dist_scale = 1. - float(MAX_DIST-distance) /(MAX_DIST-MIN_DIST); 
    for (int ind=0; ind < 9; ind++){
      frame[ind*3]   = int((1-dist_scale) * 255);
      frame[ind*3+1] = 0;
      frame[ind*3+2] = int(dist_scale * 255);
    }
  } else{
    for (int ind=0; ind < 9; ind++){
      frame[ind*3]   = 0;
      frame[ind*3+1] = 255;
      frame[ind*3+2] = 0;
    }
  }
}


#endif
