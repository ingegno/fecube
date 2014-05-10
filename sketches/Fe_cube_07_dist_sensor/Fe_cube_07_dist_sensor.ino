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

//the max distance in cm we want to measure
#define MAX_DIST 40
//the distance under which you can't see
#define MIN_DIST 3.5
//storage variables:
int duration;
float distance = 0;
unsigned long brightness = 0UL;
unsigned long last_dist_meas = 0UL;
unsigned long looptime_mus = 0UL;
bool dotrig = false;

bool test = false;  //use serial monitor for testing (slows down update rate!)

/*************************************************/
/*       Setup code                              */
/*************************************************/
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
  // measure distance once every 0.5 seconds
  
    if (test) {
      Serial.print(looptime_mus);Serial.print(" ");Serial.print(last_dist_meas);Serial.print(" ");Serial.print((looptime_mus-last_dist_meas < 1500000UL));
      Serial.println("");
      delay(500);
    }
  if (looptime_mus-last_dist_meas < 0500000UL){
    dotrig = true;
    return distance;
  }
  if (dotrig == true){
    dotrig = false;
    // read the distance. Emit sound 1ms
    digitalWrite(trigPin, HIGH);
  }
  delayMicroseconds(1000); // Note: not allowed for the real cube to delay!!
  // for code with no delays, use:
  //if (looptime_mus-last_dist_meas < 1500000UL + 1000UL){
  //  // release to the loop 
  //  return distance;
  //}
  //we waited long enough, determine new distance:
  digitalWrite(trigPin, LOW);
  //catch echo, determine distance
  duration = pulseIn(echoPin, HIGH);
  //Notice: Out of range == 0 cm!
  distance = (duration/2) / 29.1;
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
  }
  //set time of dist meas, so that the function can rerun
  last_dist_meas = micros();
  return distance;
}

void loop(){
  looptime_mus = micros();
  distance = meas_dist();  // returns 0 or number between min and max dist
  //convert to a scale, here brightness as a fraction of 20
  if (distance != 0UL){
    brightness = (MAX_DIST-distance) * 20/(MAX_DIST-MIN_DIST);
  }
  
  digitalWrite(ledR, LOW);
  digitalWrite(ledG, LOW);
  digitalWrite(ledB, LOW);
  digitalWrite(ledR, HIGH);
  if (brightness > 0UL){
   all_led_on();
   delay(brightness);
  }
  all_led_off();
  delay(20-brightness);
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
