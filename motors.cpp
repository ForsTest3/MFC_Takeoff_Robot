#include <Arduino.h>
#include "motors.h"

void initMotors() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enA, OUTPUT);

  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}


// Motor Control
void setMotors(int leftDir, int rightDir) { 
  // leftDir, rightDir: -1 reverse, 0 stop, +1 forward

  // ----- LEFT MOTOR -----
  if (leftDir > 0) {        // forward  
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(enA, HIGH);
  } else if (leftDir < 0) {  // reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(enA, HIGH);
  } else {                  // stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(enA, LOW);
  }

  // ----- RIGHT MOTOR -----
  if (rightDir > 0) {         // forward
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    digitalWrite(enB, HIGH);
  } else if (rightDir < 0) {  // reverse
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    digitalWrite(enB, HIGH);
  } else {                    // stop
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    digitalWrite(enB, LOW);
  }
}