/*
Controlling a FE Cube - intelligent patterns
*/

#ifndef EFFECT_SNAKE
#define EFFECT_SNAKE

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#define __PROG_TYPES_COMPAT__   // define needed for older arduino avr !
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

#include "fecube.h"

/*************************************************/
/*       Pattern for Fe Cube                     */
/*************************************************/

const PROGMEM prog_int16_t PatternSnakeRGB[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
//snake red
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,255, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,255, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,255, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,255, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,255, 0, 0,  1000,
  0, 0, 0,255, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,255, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,255, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
255, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,255, 0, 0,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -11
};


float pat_snake_scale_start      = 1.;   // scale time of pattern with this amount
float pat_snake_scale_speedup    = 0.75;   // every repeat, time is multiplied with this
float pat_snake_scale_min        = 0.002;   // min value of patternscale
unsigned int pat_snake_repeatmin = 250;   // how many times to repeat min value before restart
int pat_snake_extend_pattern     = 2;    // extend the pattern this number of times
int pat_snake_starteffect        = 0;    // an effect to apply to the pattern

void load_snake_function(unsigned int currpattern, int *nextduration, int shotpattern[28]) {
  for (int ind=0; ind < 28; ind++){
    shotpattern[ind] = pgm_read_word_near(PatternSnakeRGB +28*curpattern + ind);
    *nextduration = pgm_read_word_near(PatternSnakeRGB +28*(curpattern + 2) - 1);
  }
}

//red, green, blue snake
void effect_snakeRGB(unsigned long framenr, int frame[27]){
    
    fecube_pattern_effect(
            framenr,
            pat_snake_scale_start,
            pat_snake_scale_speedup,
            pat_snake_scale_min,
            pat_snake_repeatmin,
            pat_snake_extend_pattern,
            pat_snake_starteffect,
            load_snake_function);
    
    return fixed_pattern(framenr, frame);
}

//blue and red snake
void effect_snakeBR(unsigned long framenr, int frame[27]){
    
    fecube_pattern_effect(
            framenr,
            pat_snake_scale_start,
            pat_snake_scale_speedup,
            pat_snake_scale_min,
            pat_snake_repeatmin,
            1,
            -12,
            load_snake_function);
    
    return fixed_pattern(framenr, frame);
}

//green and blue snake
void effect_snakeGB(unsigned long framenr, int frame[27]){
    
    fecube_pattern_effect(
            framenr,
            pat_snake_scale_start,
            pat_snake_scale_speedup,
            pat_snake_scale_min,
            pat_snake_repeatmin,
            1,
            -11,
            load_snake_function);
    
    return fixed_pattern(framenr, frame);
}

#endif

