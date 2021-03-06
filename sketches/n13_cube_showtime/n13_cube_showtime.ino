/*
Controlling a FE Cube - intelligent patterns
*/
#include "fecube.h"

// we load some effects
#include "effect_fixed_random_smooth.h"
#include "effect_rolldice.h"
#include "effect_beating_heart.h"
#include "effect_siren.h"
#include "effect_snake.h"
#include "effect_simple_pattern.h"

// List of the effects we want to show
const int nreffects = 6;
void (*effects[nreffects])(unsigned long, int[27]) = {effect_random_color, effect_smooth_color,
                                                      effect_beating_heart, effect_siren,
                                                      effect_snakeBR, effect_simple_pattern};
unsigned long effect_duration[nreffects] = {1000UL, 4000UL,
                                            1000UL, 1000UL, 1000UL,
                                            1000UL,};

/*************************************************/
/*       Setup code                              */
/*************************************************/
void setup() {
  fecube_setup();
  // set specific flags for fecube
  fecube_allowdim(true);
  //start with effect random color
  fecube_set_starteffectnr(1);
  // set the effects to show
  fecube_set_effects(nreffects, effects, effect_duration);
  // set the double press effect, see effect_rolldice.h
  fecube_set_dblpress_effect(rolldice_duration, effect_rolldice);
  
  // set effect information
  // fixed color to show
  set_fixed_color(255, 0, 255);
  // timings for smooth color transitions
  set_smooth_color_durations(1000, 2000);
}

/*************************************************/
/*       De LOOP                                 */
/*************************************************/

void loop() {
  fecube_loop();
}
