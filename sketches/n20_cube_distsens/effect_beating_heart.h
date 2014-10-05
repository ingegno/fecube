/*
Controlling a FE Cube - intelligent patterns
*/

#ifndef EFFECT_BEATING_HEART
#define EFFECT_BEATING_HEART

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#define __PROG_TYPES_COMPAT__   // define needed for older arduino avr !
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

#include "fecube.h"

/*************************************************/
/*       Pattern for Fe Cube                     */
/*************************************************/

const PROGMEM prog_int16_t PatternHeart[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  4, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 20, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 60, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 80, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,100, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,140, 0, 0,  1000,
  4, 0, 0,  4, 0, 0,  4, 0, 0,  4, 0, 0,  4, 0, 0,  4, 0, 0,  4, 0, 0,  4, 0, 0,180, 0, 0,  1000,
 20, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0, 20, 0, 0,180, 0, 0,  1000,
 60, 0, 0, 60, 0, 0, 60, 0, 0, 60, 0, 0, 60, 0, 0, 60, 0, 0, 60, 0, 0, 60, 0, 0,220, 0, 0,  1000,
100, 0, 0,100, 0, 0,100, 0, 0,100, 0, 0,100, 0, 0,100, 0, 0,100, 0, 0,100, 0, 0,255, 0, 0,  1000,
140, 0, 0,140, 0, 0,140, 0, 0,140, 0, 0,140, 0, 0,140, 0, 0,140, 0, 0,140, 0, 0,255, 0, 0,  1000,
180, 0, 0,180, 0, 0,180, 0, 0,180, 0, 0,180, 0, 0,180, 0, 0,180, 0, 0,180, 0, 0,255, 0, 0,  1000,
220, 0, 0,220, 0, 0,220, 0, 0,220, 0, 0,220, 0, 0,220, 0, 0,220, 0, 0,220, 0, 0,255, 0, 0,  1000,
255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,  1000,
255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,255, 0, 0,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -1
};

float pat_heart_scale_start      = 0.15; // scale time of pattern with this amount
float pat_heart_scale_speedup    = 0.9;  // every repeat, time is multiplied with this
float pat_heart_scale_min        = 0.01; // min value of patternscale
unsigned int pat_heart_repeatmin = 200;  // how many times to repeat min value before restart
int pat_heart_extend_pattern     = 1;    // extend the pattern this number of times
int pat_heart_starteffect        = 0;    // an effect to apply to the pattern

void load_heart_function(unsigned int currpattern, int *nextduration, int shotpattern[28]) {
  for (int ind=0; ind < 28; ind++){
    shotpattern[ind] = pgm_read_word_near(PatternHeart +28*curpattern + ind);
    *nextduration = pgm_read_word_near(PatternHeart +28*(curpattern + 2) - 1);
  }
}

void effect_beating_heart(unsigned long framenr, int frame[27]){
    
    fecube_pattern_effect(
            framenr,
            pat_heart_scale_start,
            pat_heart_scale_speedup,
            pat_heart_scale_min,
            pat_heart_repeatmin,
            pat_heart_extend_pattern,
            pat_heart_starteffect,
            load_heart_function);
    
    return fixed_pattern(framenr, frame);
}

#endif

