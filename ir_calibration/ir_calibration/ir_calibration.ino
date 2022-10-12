#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
const int leftSensorPin = A0; // IR sensor R
const int rightSensorPin = A1; // IR sensor L
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(2);
AFMS.begin();
int sensorPins[2] = {leftSensorPin, rightSensorPin};
int voltages[5];
int curr_voltage; 
bool isLine; 
int threshold_voltage = 700; 
int initialSpeed;
int fasterSpeed;

void setup() {
  // declare the sensorPin as an INPUT:
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
  right_motor->setSpeed(initialSpeed); // Maybe try 150
  right_motor->run(FORWARD);
  left_motor->setSpeed(initialSpeed); // Maybe try 150
  left_motor->run(FORWARD);
}

void loop() {
  right_motor->setSpeed(initialSpeed); // Maybe try 150
  left_motor->setSpeed(initialSpeed); // Maybe try 150
  for (int i = 0; i < 2; i++){
     for (int n = 0; n < 5; n++) {  
      voltages[n] = analogRead(sensorPins[i]);
      }
      
      curr_voltage = average(voltages,5);
      if (curr_voltage > threshold_voltage) {
        isLine = true;
      }
      else {
        isLine = false;
        if (i == 0) {
          right_motor->setSpeed(fasterSpeed);
        }
        else {
          left_motor->setSpeed(fasterSpeed);
        }
      }
      Serial.println(isLine);
      Serial.println(curr_voltage);
      delay(500);
    }
  }
 

float average (int * array, int len)  // assuming array is int.
{
  long sum = 0L ;  // sum will be larger than an item, long for safety.
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  ((float) sum) / len ;  // average will be fractional, so float may be appropriate.
}
