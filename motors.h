#ifndef MOTORS_H
#define MOTORS_H

// Motor Driver Pins 
const int in1 = 32;
const int in2 = 33;
const int enA = 27;

const int in3 = 25;
const int in4 = 26;
const int enB = 14;

void initMotors();
void setMotors(int leftDir, int rightDir);

#endif