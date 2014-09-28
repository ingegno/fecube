/*
Controlling a FE Cube - intelligent patterns
*/

#ifndef EFFECT_SIREN
#define EFFECT_SIREN

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#define __PROG_TYPES_COMPAT__   // define needed for older arduino avr !
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

#include "fecube.h"

/*************************************************/
/*       Pattern for Fe Cube                     */
/*************************************************/

const PROGMEM prog_int16_t PatternSiren[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
 0, 0, 28,  0, 0, 0,  0, 0,255,  0, 0, 0,  0, 0, 28,  0, 0, 0,  0, 0,255,  0, 0, 0,  0, 0, 0,   100,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -90
};


float pat_siren_scale_start      = 1.;   // scale time of pattern with this amount
float pat_siren_scale_speedup    = 1.;   // every repeat, time is multiplied with this
float pat_siren_scale_min        = 1.;   // min value of patternscale
unsigned int pat_siren_repeatmin = 50;   // how many times to repeat min value before restart
int pat_siren_extend_pattern     = 3;    // extend the pattern this number of times
int pat_siren_starteffect        = 0;    // an effect to apply to the pattern

void load_siren_function(unsigned int currpattern, int *nextduration, int shotpattern[28]) {
  for (int ind=0; ind < 28; ind++){
    shotpattern[ind] = pgm_read_word_near(PatternSiren +28*curpattern + ind);
    *nextduration = pgm_read_word_near(PatternSiren +28*(curpattern + 2) - 1);
  }
}

void effect_siren(unsigned long framenr, int frame[27]){
    
    fecube_pattern_effect(
            framenr,
            pat_siren_scale_start,
            pat_siren_scale_speedup,
            pat_siren_scale_min,
            pat_siren_repeatmin,
            pat_siren_extend_pattern,
            pat_siren_starteffect,
            load_siren_function);
    
    return fixed_pattern(framenr, frame);
}

#endif

