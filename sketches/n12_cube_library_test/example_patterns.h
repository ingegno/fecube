/*
Controlling a FE Cube - intelligent patterns
*/

#ifndef EXAMPLE_PATTERNS
#define EXAMPLE_PATTERNS

#include <Arduino.h> //It is very important to remember this! note that if you are using Arduino 1.0 IDE, change "WProgram.h" to "Arduino.h" 

#define __PROG_TYPES_COMPAT__   // define needed for older arduino avr !
#include <avr/pgmspace.h> // allows use of PROGMEM to store patterns in flash

/*************************************************/
/*       Pattern for Fe Cube                     */
/*************************************************/

const PROGMEM prog_int16_t PatternSnakeRGB[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
//snake red
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  1000,
 0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0, 64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
64, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 64, 0, 0,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -11
};


const PROGMEM prog_int16_t PatternHeart[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  1, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  5, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 15, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 20, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 25, 0, 0,  1000,
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0, 35, 0, 0,  1000,
 1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0,  1, 0, 0, 45, 0, 0,  1000,
 5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0,  5, 0, 0, 45, 0, 0,  1000,
15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 15, 0, 0, 55, 0, 0,  1000,
25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 25, 0, 0, 64, 0, 0,  1000,
35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 35, 0, 0, 64, 0, 0,  1000,
45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 45, 0, 0, 64, 0, 0,  1000,
55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 55, 0, 0, 64, 0, 0,  1000,
64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0,  1000,
64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0, 64, 0, 0,  1000,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -1
};


const PROGMEM prog_int16_t PatternSiren[] = {
//order led:
//ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID,  duration
 0, 0, 7,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 7,  0, 0, 0,  0, 0,64,  0, 0, 0,  0, 0, 0,   100,
// dummy to end the pattern, with duration the effect for the next repeat, see effect
 0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  0, 0, 0,  -90
};

const int pat_snake_01 = 0;
const int pat_snake_02 = 1;
const int pat_snake_03 = 2;
const int pat_heart    = 3;
const int pat_siren    = 4;

const int nr_example_pat = 5;
float patternscales_start[nr_example_pat];    // scale time of pattern with this amount
float patternscales_speedup[nr_example_pat];  // every repeat, time is multiplied with this
float patternscales_min[nr_example_pat]; // min value of patternscale
unsigned int patterns_repeatmin[nr_example_pat];// how many times to repeat min value before restart
int extend_patterns[nr_example_pat];
int starteffects[nr_example_pat];

void example_patterns_setup() {
  // pat_snake_01 = red, green, blue snake
  patternscales_start[pat_snake_01] = 1.;
  patternscales_speedup[pat_snake_01] = 0.75;
  patternscales_min[pat_snake_01] = 0.002;
  patterns_repeatmin[pat_snake_01] = 250;
  extend_patterns[pat_snake_01] = 2;
  starteffects[pat_snake_01] = 0;
  
  // pat_snake_02 = blue and red snake
  patternscales_start[pat_snake_02] = 1.;
  patternscales_speedup[pat_snake_02] = 0.75;
  patternscales_min[pat_snake_02] = 0.002;
  patterns_repeatmin[pat_snake_02] = 250;
  extend_patterns[pat_snake_02] = -1;
  starteffects[pat_snake_02] = 12;
  
  // pat_snake_03 = green and blue snake
  patternscales_start[pat_snake_03] = 1.;
  patternscales_speedup[pat_snake_03] = 0.75;
  patternscales_min[pat_snake_03] = 0.002;
  patterns_repeatmin[pat_snake_03] = 250;
  extend_patterns[pat_snake_03] = -1;
  starteffects[pat_snake_03] = -11;
  
  // beating heart
  patternscales_start[pat_heart] = 0.15;
  patternscales_speedup[pat_heart] = 0.9;
  patternscales_min[pat_heart] = 0.01;
  patterns_repeatmin[pat_heart] = 200;
  starteffects[pat_heart] = 0;
  extend_patterns[pat_heart] = 1;
  
  //Siren
  patternscales_start[pat_siren] = 1.;
  patternscales_speedup[pat_siren] = 1.;
  patternscales_min[pat_siren] = 1.;
  patterns_repeatmin[pat_siren] = 50;
  extend_patterns[pat_siren] = 3;
  starteffects[pat_siren] = 0;
}



#endif

