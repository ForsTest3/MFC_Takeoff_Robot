#ifndef SERVOS_H
#define SERVOS_H

#include <ESP32Servo.h>

// Servo Pins
const int servo1Pin = 12;
const int servo2Pin = 13;

extern Servo servo1;
extern Servo servo2;
extern int servo1Pos;
extern int servo2Pos;

void initServos();
void handleServo();

#endif