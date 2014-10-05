/*
Controlling a FE Cube - intelligent patterns

This effect shows a dice roll with a 3 D6 dices. 
*/

#ifndef EFFECTSPARKLE_H
#define EFFECTSPARKLE_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#include "fecube.h"

const unsigned int sparkle_duration = 10000;
boolean fixed_color_sparkle = false;
boolean sparkle_variate = false;
int sparkle_colorR = 255;
int sparkle_colorG = 255;
int sparkle_colorB = 255;

void set_sparkle(boolean fixed_color, int R_1, int G_1, int B_1, boolean variate) {
  fixed_color_sparkle = fixed_color;
  sparkle_colorR = R_1;
  sparkle_colorG = G_1;
  sparkle_colorB = B_1;
  sparkle_variate = variate;
}

void effect_sparkle(unsigned long framenr, int frame[27]){
  //shot: we light up some LED with random colors
  // 
  if (framenr == 0) {
    randomSeed(millis());
  }
  
  if (sparkle_variate && (framenr % 25 == 0)) {
    //determine a new color
   sparkle_colorR = int(random(256));
   sparkle_colorG = int(random(256));
   sparkle_colorB = int(random(256));
  }
  //every 5 frames a new pattern, this is the sparkling
  if (framenr % 5 == 0) {    
    for (int ind=0; ind < 9; ind++){
      //determine if on or off
      if (random(2) == 0) {
        frame[ind*3] = 0;frame[ind*3+1] = 0;frame[ind*3+2] = 0;
      } else {
        //on, determine color, for each color, on or not?
        if (fixed_color_sparkle) {
          frame[ind*3] = sparkle_colorR;frame[ind*3+1] = sparkle_colorG;frame[ind*3+2] = sparkle_colorB;
        } else {
          for (int colv=0; colv <= 2; colv++){
            if (random(2) == 0) {
              frame[ind*3+colv] = int(random(0,256));
            } else {
              frame[ind*3+colv] = 0;
            }
          }
        }
      }
    }
  }
}

#endif

