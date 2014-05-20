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

unsigned long currentTime_mus = 0UL, cycle_time = 0UL;
int cycle_brightness = 0;

/*************************************************/
/*       variables for dist sensor interaction   */
/*************************************************/
//activate distance sensor or not
#define USE_DIST true
//speed of sound in air in cm/micros (somewhat slower to account for delay)
#define SPEED_SOUND 0.034
//the max distance in cm we want to measure
#define MAX_DIST 60.
//the distance under which you can't see
#define MIN_DIST 3.5

//control scheme to use to control the LED via dist sensor
#define DSTCTRL_SCALED 0  // color depending on distance hand
#define DSTCTRL_TIMED  1  // color depending on time hand held in place
#define DSTCTROL DSTCTRL_TIMED

//resolution for dist measurements in microseconds
#define DIST_MEAS_RESO 500000UL  //500 ms
//timeout to wait for echo pulse in microseconds
unsigned long timeout_echo = (2* MAX_DIST+1) / SPEED_SOUND;
//storage variables:
unsigned long duration = 0UL;
float distance = 0, old_distance = 0;
unsigned char echoval;
unsigned long echoduration=0UL;
bool inecholoc = false;
int brightness = 0;
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
#define test false  //use serial monitor for testing (slows down update rate!)
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
  
  cycle_time = micros();
  duration = 0UL;
}


/*************************************************/
/*      Void Loop & functions                    */
/*************************************************/

float meas_dist(){
  bool updated_dist = false;
  // measure distance once every xx seconds
  if (currentTime_mus-last_dist_meas < DIST_MEAS_RESO){
    dotrig = true;
    inecholoc = false;
  } else if (!inecholoc && dotrig == true){
    dotrig = false;
    // read the distance. Prepare to emit sound
    digitalWrite(trigPin, HIGH);
  } else if (!inecholoc && currentTime_mus-last_dist_meas > DIST_MEAS_RESO + 100UL){
    //we waited long enough, determine new distance, emit sound (8x40kHz pulses):
    echoduration = micros();
    digitalWrite(trigPin, LOW);
    //catch echo, determine distance
    bool contwait = true;
    while (contwait) {
      //timing starts running when pin reads HIGH
      echoval = digitalRead(echoPin);
      if (test) {
        Serial.print("echo val "); Serial.println(echoval);
      }
      if (echoval == HIGH) {
        //start timing
        echoduration = micros();
        contwait = false;
        inecholoc = true;
      } else if (micros() - echoduration > 800UL) {
        //timeout, jump out of loop
        contwait = false;
        inecholoc = false;
        duration = 0UL;
        updated_dist = true;
      }
    }
  } else if (inecholoc) {
    //we are waiting for the echo, we test the echo pin
    echoval = digitalRead(echoPin);
    //if we read LOW, timing ends
    if (echoval == LOW) {
      //echo received, new duration value
      duration = currentTime_mus-echoduration;
      inecholoc = false;
      updated_dist = true;
    } else if (currentTime_mus-echoduration > timeout_echo) {
      duration = 0UL;
      inecholoc = false;
      updated_dist = true;
    }
  }
  if (updated_dist) {
    
      if (test) {
        Serial.print("Duration of echo in microsec ");Serial.println(duration);
      }
    distance = (duration/2.) * SPEED_SOUND;
    if (distance < MIN_DIST || distance > MAX_DIST){
      //out of range
      if (test) {
        Serial.println("Niets gezien");
      }
      distance = 0.;
    } 
    // Set color values 
    dist_to_brightness();
    old_distance = distance;
    if (test) {
       Serial.print("Iets gezien op "); Serial.print(distance); Serial.println(" cm"); 
     }
    //set time of this dist meas, so it does not happen again too fast
    last_dist_meas = micros();
  }
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
  meas_dist();  // sets internally distance and brightness
  
  // a cycle is 20 ms
  if (currentTime_mus - cycle_time > 20000UL) {
    //restart a cycle
    cycle_time = currentTime_mus;
    digitalWrite(ledR, LOW);
    digitalWrite(ledG, LOW);
    digitalWrite(ledB, LOW);
    digitalWrite(ledR, HIGH);
    cycle_brightness = brightness;
    if (cycle_brightness > 0UL){
     all_led_on();
    } else {
      all_led_off();
    }
  }
  //in loop, we keep led state up to point that we need to switch led off
  if (currentTime_mus - cycle_time > 2*cycle_brightness*1000UL){
    all_led_off();
  }
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
