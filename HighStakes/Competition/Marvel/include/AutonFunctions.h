#ifndef _PROS_AUTONFUNCTIONS_H_
#define _PROS_AUTONFUNCTIONS_H_

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"

// Function declarations
void lateralPID(double targetDistance, int maxSpeed);
void turnPID(double targetDegrees, int maxSpeed);
void turnClockwiseTime(int turnTime, int maxSpeed);
double degreesToInches(double);
// PID Constants (extern to be defined in AutonFunctions.cpp)
extern double kp;  // Proportional constant
extern double ki;  // Integral constant
extern double kd;  // Derivative constant

#endif  // _PROS_AUTONFUNCTIONS_H_
