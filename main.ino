/*
  Arduino-Mega based line following robot with obstacle detection and color recognition.

  Connections:
  # IR array
  | Pin | Connected to | Type |
  | --- | ------------ | ---- |
  |  1  |       52     | INPUT|
  |  2  |       50     | INPUT|
  |  3  |       48     | INPUT|
  |  4  |       46     | INPUT|
  |  5  |       44     | INPUT|
  |  6  |       42     | INPUT|
  |  7  |       40     | INPUT|
  |  8  |       38     | INPUT|

  # Motor driver
  | Pin | Connected to | Type |
  | --- | ------------ | ---- |
  | OUT1|       4      |OUTPUT|
  | OUT2|       5      |OUTPUT|
  | OUT3|       2      |OUTPUT|
  | OUT4|       3      |OUTPUT|

  # IR sensor
  | Pin | Connected to | Type |
  | --- | ------------ | ---- |
  | OUT |      32      | INPUT|

  # Color sensor
  | Pin | Connected to | Type |
  | --- | ------------ | ---- |
  | S2  |      51      |OUTPUT|
  | S3  |      53      |OUTPUT|
  | OUT |      49      | INPUT|

  #RGB led
  | Pin | Connected to | Type |
  | --- | ------------ | ---- |
  |  R  |      22      |OUTPUT|
  |  G  |      24      |OUTPUT|
  |  B  |      26      |OUTPUT|
*/

// Including required libraries
#include "MotorDriver.h"
#include "LineDetector.h"
#include "PIDController.h"


#define stdVolt 150

// Declaring global pins
int motorPins[] = {11,10,6,9}, // MotorL+, MotorL-, MotorR+, MotorR-
    //colorPins[] = {51, 53, 49}, // S2, S3, OUT
    lfrPins[] = {2, 3, 4, 5, 7, 8, 12, 13}; // Left to right

// Global objects
MotorDriver motor(motorPins);
//ColorSensor cSensor(colorPins);
LineDetector lfr(lfrPins);

int lastDeviation = 0, // Variable to store deviation calculated in previous cycle
    passedCross = 0; // Whether bot has passed a cross section

void setup(){
  Serial.begin(9600);
}

void loop() {
  // Calculating error and voltage
  int deviation = lfr.calcDeviation();
  int volt = PID(deviation, lastDeviation);
  Serial.println(deviation);
  /* Moving bot
  if(deviation < 0) {
    motor.move('r', volt);
    if (lfr.is90Turn())
      delay(250);
    //Serial.println("Right");
  }
  else if(deviation > 0) {
    motor.move('l', volt);
    if (lfr.is90Turn())
      delay(250);
    //Serial.println("Left");
  }
  else {
    // Move forward
    motor.move('f', stdVolt);
    //Serial.println("Forward");
  }*/
  lastDeviation = deviation; // Storing current deviation for future use
  delay(1000);
}
