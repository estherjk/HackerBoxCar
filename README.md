# HackerBoxCar

My implementation of [HackerBoxes 0013: Autosport](https://www.instructables.com/id/HackerBoxes-0013-Autosport).

<div align="middle">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/HackerBoxCar.jpg?raw=true" width="360px">
</div>

The car is capable of three modes:

* Remote-control mode, where the Blynk mobile app is used to control the direction that the car moves (forward, left, right, reverse)
* Line-following mode, where the car's IR sensors detect a black line to control its path
  * *Note: The car performs best with gradual (as opposed to sharp) curves*
* Autonomous mode, where the car uses an ultrasonic range sensor to detect and avoid objects
  * *Note: when the car detects an object, it will randomly turn left or right in order to attempt to avoid an object*

Take a look at the [video](https://youtu.be/K7Yosm08pu0) to see it in action.

## Directory structure

* HackerBoxCar: Contains the full implementation of the car
* NodeMCUBlink: Blinks the onboard LED to check that the NodeMCU module is working
* NodeMCUIR: Tests a single IR sensor by either printing its digital or analog value
* NodeMCUPing: Tests the operation of the range finder by printing the distance to any object in cm in the serial monitor

## Blynk app

[Blynk](http://www.blynk.cc/) is a mobile app used for rapid IoT prototyping. To interface with the HackerBoxCar sketch, configure the Blynk app as shown in the screenshots below.

<div align="left">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_01.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_02.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_03.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_04.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_05.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_06.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_07.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_08.png?raw=true" width="250px">
  <img src="https://github.com/drejkim/HackerBoxCar/blob/master/images/Blynk_09.png?raw=true" width="250px">
</div>