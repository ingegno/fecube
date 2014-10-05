/*
Controlling a FE Cube - intelligent patterns
*/
#include "fecube.h"

// we load some effects
#include "effect_fixed_random_smooth.h"
#include "effect_rolldice.h"
#include "effect_beating_heart.h"
#include "effect_siren.h"
#include "effect_sparkle.h"

// List of the effects we want to show
const int nreffects = 4;
void (*effects[nreffects])(unsigned long, int[27]) = {effect_random_color,
                                                      effect_beating_heart,
                                                      effect_siren, effect_sparkle};
unsigned long effect_duration[nreffects] = {1000UL, 1000UL,
                                            1000UL, 10000UL};

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
  set_sparkle(true, 255, 255, 255, true);
}

/*************************************************/
/*       De LOOP                                 */
/*************************************************/

void loop() {
  fecube_loop();
}
