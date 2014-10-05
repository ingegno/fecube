/*
Controlling a FE Cube - intelligent patterns

This effect shows a dice roll with a 3 D6 dices. 
*/

#ifndef EFFECTDICEROLL_H
#define EFFECTDICEROLL_H

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#include "fecube.h"

int D6R = 0; int D6G = 0; int D6B = 0;

const unsigned int rolldice_duration = 8000;


int rolldice_rolseconds = 2;
int rolldice_showduration = 6;
int rolldice_showvalduration = 1;  //seconds to show val
  
void effect_rolldice(unsigned long framenr, int frame[27]){
  //shot: 3d6 dices rolling, 2 sec rolling, 6 sec show value
  // 
  if (framenr == 0) {
    randomSeed(millis());
    D6R = random(1,7);D6G = random(1,7);D6B = random(1,7);
  }
  if (framenr < rolldice_rolseconds * 25UL) {
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
          frame[ind*3+add] = 255;
        }
      }
    }
  } else {
    for (int ind=0; ind < 27; ind++){
      frame[ind] = 0;
    }
    //every half second another color
    int color = (framenr-rolldice_rolseconds * 25UL) % (3*25UL*rolldice_showvalduration);
    int val = 0;
    if (color < 25UL*rolldice_showvalduration){
      color = 0;
      val = D6R;
    } else if (color < 2*25UL*rolldice_showvalduration) {
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

#endif

