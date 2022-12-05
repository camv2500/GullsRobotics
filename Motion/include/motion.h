#include "robot-config.h"
#include "vex.h"

void PIDLoop(double setPoint, bool isTurning = false) {
  //setpoint is in number of revolutions required
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

    if (isTurning) {
      LeftMotor1.spin(forward, power, pct);
      RightMotor1.spin(reverse, power, pct);
      wait(20, msec);
    }
    else {
      LeftMotor1.spin(forward, power, pct);
      RightMotor1.spin(forward, power, pct);
      wait(20, msec);
    }
  }
}

//current function for turning the robot, converts the degrees given to revolutions required and sends it to the PIDLoop
void turnRobot(double setDegrees) {
  //need to convert to using radians to decrease the amount of math

  //setDegrees is the amount of degrees we want to turn
  //turnDiameter is the diameter of the circle of roation that the robot establishes while spinning
  double turnDiameter = 13.0;

  //convert the setDegrees given into the amount of inches required
  double requiredInches = setDegrees / 360 * M_PI * turnDiameter;

  //convert the inches to revolutions
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat;

  PIDLoop(requiredRevolutions, true);
}