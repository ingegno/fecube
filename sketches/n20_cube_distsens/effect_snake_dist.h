/*
Controlling a FE Cube - intelligent patterns
*/

#ifndef EFFECT_SNAKE_DIST
#define EFFECT_SNAKE_DIST

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#define __PROG_TYPES_COMPAT__   // define needed for older arduino avr !
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

#include "fecube.h"

/*************************************************/
/*       Pattern for Fe Cube                     */
/*************************************************/

const PROGMEM prog_int16_t PatternSnake[] = {
//a color based snake order led: color + brightness as points
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
//snake with color 1 then 2
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  1000,
 0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 1,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1,10,  1000,
 //now color 2
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  1000,
 0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 2,10,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  1000,
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  2,10,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  0, 0,  -11
};


float pat_snakedist_scale_start      = 0.25;   // scale time of pattern with this amount
float pat_snakedist_scale_speedup    = 0.75;   // every repeat, time is multiplied with this
float pat_snakedist_scale_min        = 0.002;   // min value of patternscale
unsigned int pat_snakedist_repeatmin = 250;   // how many times to repeat min value before restart
int pat_snakedist_extend_pattern     = 0;    // extend the pattern this number of times
int pat_snakedist_starteffect        = 0;    // an effect to apply to the pattern

void load_snakedist_function(unsigned int currpattern, int *nextduration, int shotpattern[28]) {
  for (int ind=0; ind < 19; ind++){
    shotpatterncolornr[ind] = pgm_read_word_near(PatternSnake+19*curpattern + ind);
    *nextduration = pgm_read_word_near(PatternSnake +19*(curpattern + 2) - 1);
  }
  //use the library function to convert to a normal pattern
  fecube_conv_colnrpat_pattern();
}

//red, green, blue snake
void effect_snakedist(unsigned long framenr, int frame[27]){
    
    fecube_pattern_effect(
            framenr,
            pat_snakedist_scale_start,
            pat_snakedist_scale_speedup,
            pat_snakedist_scale_min,
            pat_snakedist_repeatmin,
            pat_snakedist_extend_pattern,
            pat_snakedist_starteffect,
            load_snakedist_function);
    
    return fixed_pattern(framenr, frame);
}

#endif

