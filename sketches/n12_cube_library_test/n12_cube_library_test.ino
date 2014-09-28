/*
Controlling a FE Cube - intelligent patterns
*/
#include "fecube.h"

void effect1(unsigned long framenr, int frame[27]){
  // 25 frame per second !
  // frame order LED:  {ledTLF,   ledTLA,   ledTRF,   ledTRA,   ledBLF,   ledBLA,   ledBRF,   ledBRA,   ledMID};
  if (framenr <=25) {
    int frame2[27] = {
             255, 255,   0,  //TLF
             255, 255,   0,  //TLA
             255, 255,   0,  //TRF
             255, 255,   0,  //TRA
             255,   0, 255,  //BLF
             255,   0, 255,  //BLA
             255,   0, 255,  //BRF
             255,   0, 255,  //BRA
             255, 255, 255,  //MID
            };
    fecube_set_frame(frame, frame2);
  } else {
    int frame2[27] = {
             255,   0, 255,  //TLF
             255,   0, 255,  //TLA
             255,   0, 255,  //TRF
             255,   0, 255,  //TRA
             255, 255,   0,  //BLF
             255, 255,   0,  //BLA
             255, 255,   0,  //BRF
             255, 255,   0,  //BRA
             255, 255, 255,  //MID
            };
    fecube_set_frame(frame, frame2);
  }
  // too avoid too much cycling we switch off, and delay somewhat
}

void snake(unsigned long framenr, int frame[27]){
   // color of the snake:
  const int R_1 = 255;
  const int G_1 = 0;
  const int B_1 = 0;
  //  frames per LED
  const int frames_per_LED = 25;
  fecube_clearframe(frame);
  if (framenr <= frames_per_LED) {
    fecube_set_ledcolor(cBLA, R_1, G_1, B_1, frame);  //set the BLA led to this color
  } else if (framenr <= 2 * frames_per_LED) {
    fecube_set_ledcolor(cBLF, R_1, G_1, B_1, frame);
  } else if (framenr <= 3 * frames_per_LED) {
    fecube_set_ledcolor(cBRF, R_1, G_1, B_1, frame);
  } else if (framenr <= 4 * frames_per_LED) {
    fecube_set_ledcolor(cBRA, R_1, G_1, B_1, frame);
  } else if (framenr <= 5 * frames_per_LED) {
    fecube_set_ledcolor(cMID, R_1, G_1, B_1, frame);
  } else if (framenr <= 6 * frames_per_LED) {
    fecube_set_ledcolor(cTRA, R_1, G_1, B_1, frame);
  } else if (framenr <= 7 * frames_per_LED) {
    fecube_set_ledcolor(cTRF, R_1, G_1, B_1, frame);
  } else if (framenr <= 8 * frames_per_LED) {
    fecube_set_ledcolor(cTLF, R_1, G_1, B_1, frame);
  } else if (framenr <= 9 * frames_per_LED) {
    fecube_set_ledcolor(cTLA, R_1, G_1, B_1, frame);
  }
}
  
// List of the effects we want to show
const int nreffects = 2;
int showeffect = 0;
void (*effects[nreffects])(unsigned long, int[27]) = {effect1, snake};
unsigned long effect_duration[nreffects] = {2000UL, 9000UL};

/*************************************************/
/*       Setup code                              */
/*************************************************/
void setup() {
  fecube_setup();
  // set specific flags for fecube
  fecube_allowdim(true);
  // set the effects to show
  fecube_set_effects(nreffects, effects, effect_duration);
}

/*************************************************/
/*       De LOOP                                 */
/*************************************************/

void loop() {
  fecube_loop();
}
