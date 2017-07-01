/*
 HC-SR04 Ping distance sensor:
 VCC to NodeMCU 3.3V or VIN 
 GND to NodeMCU G
 Echo to NodeMCU pin D6 (GPIO12) 
 Trig to NodeMCU pin D7 (GPIO13)
 
 This sketch originated from Virtualmix: http://goo.gl/kJ8Gl
 Was modified and posted to: http://arduinobasics.blogspot.com
 And was finally modified for NodeMCU by HackerBoxes.com
 */

#define echoPin 12 // Echo Pin
#define trigPin 13 // Trigger Pin
#define LEDPin  16 // Onboard LED

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
}

void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 Serial.println("-1");
 digitalWrite(LEDPin, HIGH); 
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.println(distance);
 digitalWrite(LEDPin, LOW); 
 }
 
 //Delay 50ms before next reading.
 delay(50);
}
