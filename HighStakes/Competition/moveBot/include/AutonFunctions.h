#ifndef _PROS_AUTONFUNCTIONS_H_
#define _PROS_AUTONFUNCTIONS_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"

// Function declarations
void moveForwardPID(int targetDistance, int maxSpeed);
void turnClockwiseTime(int turnTime, int maxSpeed);

// PID Constants (extern to be defined in AutonFunctions.cpp)
extern double kp;  // Proportional constant
extern double ki;  // Integral constant
extern double kd;  // Derivative constant

#endif  // _PROS_AUTONFUNCTIONS_H_
