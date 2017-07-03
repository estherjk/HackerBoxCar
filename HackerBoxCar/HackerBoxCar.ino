/**************************************************************
 * This example runs directly on ESP8266 chip
 * using the Blynk platform and mobile application.
 *
 * Change WiFi ssid, password, and Blynk auth token to run :)
 *
 **************************************************************/

#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define PIN_RIGHT_MOTOR_SPEED 5
#define PIN_RIGHT_MOTOR_DIR   0
#define PIN_LEFT_MOTOR_SPEED  4
#define PIN_LEFT_MOTOR_DIR    2
#define PIN_ECHO 12 // Echo Pin
#define PIN_TRIGGER 13 // Trigger Pin
#define PIN_RIGHT_IR 14 // Right IR sensor digital pin (D5)
#define PIN_LEFT_IR 16 // Left IR sensor digital pin (D0)

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "BLYNK AUTH TOKEN";
char ssid[] = "WIFI NETWORK";
char pass[] = "WIFI PASSWORD";

// For range finder
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

// For IR sensors
boolean leftIRstate, rightIRstate;

boolean autonomousMode = false;
boolean lineFollowMode = false;

void setup()
{
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(PIN_RIGHT_MOTOR_SPEED, OUTPUT);
  pinMode(PIN_RIGHT_MOTOR_DIR, OUTPUT);
  pinMode(PIN_LEFT_MOTOR_SPEED, OUTPUT);
  pinMode(PIN_LEFT_MOTOR_DIR, OUTPUT);
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_LEFT_IR, INPUT);
  pinMode(PIN_RIGHT_IR, INPUT);
}

void loop()
{
  Blynk.run();

  useRangeFinder();
  useIRSensors();

  if(autonomousMode) {
    doCollisionAvoidance(distance);
  }

  if(lineFollowMode) {
    doLineFollowing(leftIRstate, rightIRstate);
  }

  // Add a delay between readings
  delay(10);
}

void halt()
{
  digitalWrite(PIN_RIGHT_MOTOR_SPEED, LOW);
  digitalWrite(PIN_LEFT_MOTOR_SPEED, LOW);
}

void forward()
{
  // Need to flip the direction bits due to the motor wiring
  digitalWrite(PIN_RIGHT_MOTOR_DIR, LOW);
  digitalWrite(PIN_LEFT_MOTOR_DIR, LOW);

  digitalWrite(PIN_RIGHT_MOTOR_SPEED, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_SPEED, HIGH);
}

void reverse()
{
  // Need to flip the direction bits due to the motor wiring
  digitalWrite(PIN_RIGHT_MOTOR_DIR, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_DIR, HIGH);

  digitalWrite(PIN_RIGHT_MOTOR_SPEED, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_SPEED, HIGH);
}

void right()
{
  digitalWrite(PIN_RIGHT_MOTOR_DIR, LOW);
  digitalWrite(PIN_LEFT_MOTOR_DIR, HIGH);
  digitalWrite(PIN_RIGHT_MOTOR_SPEED, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_SPEED, HIGH);
}

void left()
{
  digitalWrite(PIN_RIGHT_MOTOR_DIR, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_DIR, LOW);
  digitalWrite(PIN_RIGHT_MOTOR_SPEED, HIGH);
  digitalWrite(PIN_LEFT_MOTOR_SPEED, HIGH);
}

void useRangeFinder() {
  distance = getDistance();
 
  if(distance >= maximumRange || distance <= minimumRange){
    Serial.println("Invalid distance");
    distance = -1;
  }
  else {
    Serial.print("distance [cm]: ");
    Serial.println(distance);
  }
}

long getDistance() {
   /* The following PIN_TRIGGER/PIN_ECHO cycle is used to determine the
  distance of the nearest object by bouncing soundwaves off of it. */ 
  digitalWrite(PIN_TRIGGER, LOW); 
  delayMicroseconds(2); 

  digitalWrite(PIN_TRIGGER, HIGH);
  delayMicroseconds(10); 

  digitalWrite(PIN_TRIGGER, LOW);
  duration = pulseIn(PIN_ECHO, HIGH);

  // Calculate the distance (in cm) based on the speed of sound.
  distance = duration / 58.2;

  Blynk.virtualWrite(V11, distance);

  return distance;
}

void doCollisionAvoidance(int distance) {
  if(distance < 20 && distance >=0 ) {
    Serial.println("Object detected!");

    halt();
    delay(200);

    turnRandom();
    delay(200);
    
    halt();
  }
  else {
    forward();
  }
}

void turnRandom() {
  int value = random(2); // Random number between 0 and 1

  if(value) {
    Serial.println("Turning right!");
    right();
  }
  else {
    Serial.println("Turning left!");
    left();
  }
}

void useIRSensors() {
  leftIRstate = digitalRead(PIN_LEFT_IR);
  rightIRstate = digitalRead(PIN_RIGHT_IR);

  Serial.print("IR left: ");
  Serial.print(leftIRstate);
  Serial.print("\t");
  Serial.print("IR right: ");
  Serial.print(rightIRstate);
  Serial.println("\t");
}

void doLineFollowing(boolean leftIRstate, boolean rightIRstate) {
  // Line following logic is as follows:
  //   - If both sensors sense white, move forward
  //   - If left sensor senses black, move left
  //   - If right sensor senses black, move right
  //   - Else, halt
  // When sensor senses black, state is HIGH

  if(!leftIRstate && !rightIRstate) {
    Serial.println("Moving forward!");
    forward();
  }
  if(leftIRstate && !rightIRstate) {
    Serial.println("Turning left!");
    left();
  }
  if(!leftIRstate && rightIRstate) {
    Serial.println("Turning right!");
    right();
  }
  else if(leftIRstate && rightIRstate) {
    Serial.println("Halt!");
    halt();
  }
}

BLYNK_WRITE(V0)
{
  if(param[0])
    forward();
  else
    halt();
}

BLYNK_WRITE(V1)
{
  if(param[0])
    reverse();
  else
    halt();
}

BLYNK_WRITE(V2)
{
  if(param[0])
    right();
  else
    halt();
}

BLYNK_WRITE(V3)
{
  if(param[0])
    left();
  else
    halt();
}

BLYNK_WRITE(V10)
{
  if(param[0]) {
    autonomousMode = true;
    forward();
  }
  else {
    autonomousMode = false;
    halt();
  }
}

BLYNK_WRITE(V12)
{
  if(param[0]) {
    lineFollowMode = true;
    forward();
  }
  else {
    lineFollowMode = false;
    halt();
  }
}