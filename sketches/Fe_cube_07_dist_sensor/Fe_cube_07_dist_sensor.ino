/*
Controlling a led cube or simple LED via a dist sensor

*/ 
 
// pins used, avoid use of memory to store it:
#define ledR 10
#define ledG 11
#define ledB 12
// led anodes are connected to pins via a resistor
// Bottom/Top - Left/Right - Aft/Front
#define ledBLA 1
#define ledTLA 4
#define ledBLF 3
#define ledTLF 2
#define ledMID 5
#define ledTRF 8
#define ledBRA 7
#define ledTRA 6
#define ledBRF 9

//distance sensor Trig and Echo
#define trigPin A0
#define echoPin A1

unsigned long currentTime_mus = 0UL;
/*************************************************/
/*       variables for dist sensor interaction   */
/*************************************************/
//activate distance sensor or not
#define USE_DIST true
//speed of sound in air in cm/ms (somewhat slower to account for delay)
#define SPEED_SOUND 29.1
//the max distance in cm we want to measure
#define MAX_DIST 15.
//the distance under which you can't see
#define MIN_DIST 3.5

//control scheme to use to control the LED via dist sensor
#define DSTCTRL_SCALED 0  // color depending on distance hand
#define DSTCTRL_TIMED  1  // color depending on time hand held in place
#define DSTCTROL DSTCTRL_TIMED

//resolution for dist measurements in microseconds
#define DIST_MEAS_RESO 500000UL  //500 ms
//timeout to wait for echo pulse in microseconds
unsigned long timeout_echo = (2* MAX_DIST+1) / SPEED_SOUND * 1000;
//storage variables:
int duration;
float distance = 0, old_distance = 0;
unsigned long brightness = 0UL;
unsigned long last_dist_meas = 0UL;
bool dotrig = false;
//4 scale vals from min to max
#define DSTSCALE_BR_MIN    MIN_DIST
#define DSTSCALE_BR_MAX    MIN_DIST + (MAX_DIST-MIN_DIST)/4.
#define DSTSCALE_BLUE_MIN  DSTSCALE_BR_MAX
#define DSTSCALE_BLUE_MAX  DSTSCALE_BLUE_MIN + (MAX_DIST-MIN_DIST)/4.
#define DSTSCALE_GREEN_MIN DSTSCALE_BLUE_MAX
#define DSTSCALE_GREEN_MAX DSTSCALE_GREEN_MIN + (MAX_DIST-MIN_DIST)/4.
#define DSTSCALE_RED_MIN   DSTSCALE_GREEN_MAX
#define DSTSCALE_RED_MAX   DSTSCALE_RED_MIN + (MAX_DIST-MIN_DIST)/4.

/*************************************************/
/*       Setup code                              */
/*************************************************/
bool test = false;  //use serial monitor for testing (slows down update rate!)
void setup() {
  if (test) {
    Serial.begin(9600);
  }
 randomSeed(analogRead(0));
 pinMode(ledR,OUTPUT); pinMode(ledG,OUTPUT); pinMode(ledB,OUTPUT);
 pinMode(ledBLA,OUTPUT);  pinMode(ledBLF,OUTPUT); pinMode(ledBRA,OUTPUT);
 pinMode(ledBRF,OUTPUT); pinMode(ledMID,OUTPUT); pinMode(ledTLA,OUTPUT);
 pinMode(ledTLF,OUTPUT); pinMode(ledTRA,OUTPUT); pinMode(ledTRF,OUTPUT);
  // initialize the distance sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);  
}


/*************************************************/
/*      Void Loop & functions                    */
/*************************************************/

float meas_dist(){
  if (test) {
      Serial.print(currentTime_mus);Serial.print(" ");Serial.print(last_dist_meas);Serial.print(" ");Serial.print((currentTime_mus-last_dist_meas < 1500000UL));
      Serial.println("");
      delay(500);
    }
  // measure distance once every xx seconds
  if (currentTime_mus-last_dist_meas < DIST_MEAS_RESO){
    dotrig = true;
    //release the function, return to the loop
    return distance;
  }
  if (dotrig == true){
    dotrig = false;
    // read the distance. Prepare to emit sound
    digitalWrite(trigPin, HIGH);
  }
  //minimum of 10 microsec of delay needed
  delayMicroseconds(100); // Note: not allowed for the real cube to delay!!
  // for code with no delays, use:
  //if (currentTime_mus-last_dist_meas < DIST_MEAS_RESO + 100UL){
  //  // release to the loop, too early to detect echo 
  //  return distance;
  //}
  //we waited long enough, determine new distance, emit sound (8x40kHz pulses):
  digitalWrite(trigPin, LOW);
  //catch echo, determine distance
  duration = pulseIn(echoPin, HIGH, timeout_echo);
  //Notice: Out of range == 0 cm!
  //speed of sound in air: 29 to 34 cm/ms. Half time to object
  distance = (duration/2) / SPEED_SOUND;
  if (distance < MIN_DIST || distance > MAX_DIST){
    //out of range
    if (test) {
      Serial.println("Niets gezien");
      delay(500);
    }
    distance = 0.;
  } else {
    if (test) {
      Serial.print("Iets gezien op "); Serial.print(distance); Serial.println(" cm"); 
      delay(500);
    }
    // Set color values 
    dist_to_brightness();
  }
  //set time of this dist meas, so it does not happen again too fast
  last_dist_meas = micros();
  return distance;
}


void dist_to_brightness(){
  if (DSTCTROL == DSTCTRL_TIMED) {
    //convert time held in place into brightness value in (0,10)
    if (distance >=DSTSCALE_BR_MIN && distance <= DSTSCALE_BR_MAX ) {
      if (old_distance >=DSTSCALE_BR_MIN && old_distance <= DSTSCALE_BR_MAX ) {
        //second measurement here, we increase brightness one
        brightness += 1;
        if (brightness >10) brightness = 0;
      }
    }
    old_distance = distance;
  } else {
    //convert distance into brightness value in (0,10)
    if (distance == 0) {
      return;
    }
    //normalized distance in [0,20]
    brightness = (MAX_DIST-distance) * 10/(MAX_DIST-MIN_DIST);
  }
}


void loop(){
  currentTime_mus = micros();
  distance = meas_dist();  // returns 0 or number between min and max dist
  
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledR, HIGH);
  if (brightness > 0UL){
   all_led_on();
   delay(2*brightness);
  }
  all_led_off();
  delay(20-2*brightness);
}

void all_led_off(){
 digitalWrite(ledBLA,HIGH); digitalWrite(ledBLF,HIGH);
 digitalWrite(ledBRA,HIGH); digitalWrite(ledBRF,HIGH);
 digitalWrite(ledMID,HIGH); digitalWrite(ledTLA,HIGH);
 digitalWrite(ledTLF,HIGH); digitalWrite(ledTRA,HIGH);
 digitalWrite(ledTRF,HIGH);
}

void all_led_on(){
 digitalWrite(ledBLA,LOW); digitalWrite(ledBLF,LOW);
 digitalWrite(ledBRA,LOW); digitalWrite(ledBRF,LOW);
 digitalWrite(ledMID,LOW); digitalWrite(ledTLA,LOW);
 digitalWrite(ledTLF,LOW); digitalWrite(ledTRA,LOW);
 digitalWrite(ledTRF,LOW);
}
