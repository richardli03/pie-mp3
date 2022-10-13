// Import libraries
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Define and initialize pins 
const int leftSensorPin = A1; // IR sensor R
const int rightSensorPin = A0; // IR sensor L

// Define motorshield and motor objects
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *right_motor = AFMS.getMotor(1);
Adafruit_DCMotor *left_motor = AFMS.getMotor(3);

// Pack sensor pins into array
int sensorPins[2] = {leftSensorPin, rightSensorPin};

// Define voltage array for filtering 
int voltages[10];

// Define current voltage 
int curr_voltage; 

// Define booleans that tell us if the IRs detect a line or not 
bool is_line_left;
bool is_line_right;

// Define threshold voltage for determining whether the IR detects a line or not 
int threshold_voltage_right = 800; 
int threshold_voltage_left = 600;

// Define initial (default) and increased speeds (when we need to get back on the line) 
int initialSpeed = 25; // 50 to overcome friction of all the other stuff touching the ground
int fasterSpeed = 175; // 60


void setup() {
  // Declare the sensorPin as an INPUT:
  pinMode(sensorPins[0], INPUT);
  pinMode(sensorPins[1], INPUT);
  // Initialize bools that tell us whether we're on the line or not 
  is_line_left = false;
  is_line_right = false;
  // Start Adafruit motorshield 
  AFMS.begin();
  // Begin serial 
  Serial.begin(9600);
  // Set the motor speeds to the initial speed variable and make them turn forward
  right_motor->setSpeed(initialSpeed); 
  right_motor->run(FORWARD);
  left_motor->setSpeed(initialSpeed); 
  left_motor->run(FORWARD);
}

void loop() {
// Check if we're not on line - we shouldn't be on the line 
  if (is_line_left == false && is_line_right == false) {
    right_motor->setSpeed(initialSpeed); 
    left_motor->setSpeed(initialSpeed); 
    right_motor->run(FORWARD);
    left_motor->run(FORWARD);
  }
  // For each sensor i = 0 => left i = 1 => right 
  for (int i = 0; i < 2; i++){
    // Collect 10 voltages 
     for (int n = 0; n < 10; n++) {  
      voltages[n] = analogRead(sensorPins[i]);
      }
      // Take average of those 10 voltages 
      curr_voltage = average(voltages,5);
      // If it's the left sensor 
      if (i == 0) {
        // Check if it sees the tape
        if (curr_voltage > threshold_voltage_left) {
          // If it sees the tape, increase the speed of the right motor until is_line_left is false again (until the left IR is off the tape)
          Serial.print("Left voltage: ");
          Serial.println(curr_voltage);
          is_line_left = true; 
          right_motor->setSpeed(fasterSpeed);
          left_motor->run(BACKWARD);
          left_motor->setSpeed(fasterSpeed);
        }
        else {
          
          is_line_left = false;
        }
      }
      else {
        // If right IR sees tape 
        if (curr_voltage > threshold_voltage_right) {
          Serial.print("Right voltage: ");
          Serial.println(curr_voltage);
          is_line_right = true;
          // Increase speed of left motor until right IR doesn't see line anymore - boolean changes in following else statement 
          left_motor->setSpeed(fasterSpeed); 
          right_motor->run(BACKWARD);
          right_motor->setSpeed(fasterSpeed); 
          
        }
        else {
          is_line_right = false;
        }
      }
      // Print info for debugging 
      Serial.print("Right voltage: ");
      Serial.println(curr_voltage);
      Serial.print("Left: ");
      Serial.println(is_line_left);
      Serial.print("Right: ");
      Serial.println(is_line_right);
      //delay(2000);
    }
  }
 
// Find average voltage of 5 readings to filter IR data 
float average (int * array, int len)  // assuming array is int.
{
  long sum = 0L ;  // sum will be larger than an item, long for safety.
  for (int i = 0 ; i < len ; i++)
    sum += array [i] ;
  return  ((float) sum) / len ;  // average will be fractional, so float may be appropriate.
}
