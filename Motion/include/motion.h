#include "robot-config.h"
#include "vex.h"

void PDLoop(double setPoint) {
  double error = setPoint;
  double kP = 0.99, kI = 0, kD = 0, prevError = 0, integral = 0, derivative = 0, power = 0;
  double sensorValue = 0;

  LeftMotor1.setPosition(0, rev);
  RightMotor1.setPosition(0, rev);

  while (fabs(error) > 0.01) {
    sensorValue = (LeftMotor1.position(rev) + RightMotor1.position(rev)) / 2;
    error = setPoint - sensorValue;

    integral = integral + error;
    if (error <= 0 || integral > (setPoint * 2)) {
      integral = 0;
    }

    derivative = error - prevError;
    prevError = error;

    power = error * kP + integral * kI + derivative * kD;
    power = power * 80;

    LeftMotor1.spin(forward, power, pct);
    RightMotor1.spin(forward, power, pct);
    wait(20, msec);
  }
}