#include "robot-config.h"
#include "vex.h"

void PDLoop(double setPoint) {
  double error = setPoint;
  double kP = 0.8, kI = 0, kD = 0, prevError = 0, integral = 0, derivative = 0, power = 0;
  double sensorValue = 0;

  while (fabs(error) > 0.01) {
    sensorValue = (LeftMotor1.position(rev) + RightMotor1.position(rev)) / 2;
    error = setPoint - sensorValue;
    integral = integral + error;
    //if (error <= 0 || error > (setPoint / 8)) {
      //integral = 0;
    //}
    derivative = error - prevError;
    prevError = error;
    power = error * kP + integral * kI + derivative * kD;
    LeftMotor1.spin(forward, power, pct);
    RightMotor1.spin(forward, power, pct);
  }
}