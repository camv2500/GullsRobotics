#include "robot-config.h"
#include "vex.h"

void PIDLoop(double setPoint, bool isTurning = false, bool usingFlyWheel = false) {
  //setpoint is in number of degrees required
  double error = setPoint;
  double kP = 0.28, kI = 0.01, kD = 0.25, prevError = 0, integral = 0, derivative = 0, power = 0;
  double sensorValue = 0;

  LeftMotor1.setPosition(0, degrees);
  RightMotor1.setPosition(0, degrees);
  FlyWheel1.setPosition(0,degrees);
  FlyWheel2.setPosition(0,degrees);

  while (fabs(error) > 0.4 && !usingFlyWheel) {
    if (isTurning) {sensorValue = RightMotor1.position(degrees);}
    else {sensorValue = (LeftMotor1.position(degrees) + RightMotor1.position(degrees)) / 2;}
    error = setPoint - sensorValue;

    integral = integral + error;
    if (fabs(integral) > 500) {integral = 500;}

    derivative = error - prevError;
    prevError = error;

    power = error * kP + integral * kI + derivative * kD;

    if (isTurning) {
      LeftMotor1.spin(reverse, power, pct);
      RightMotor1.spin(forward, power, pct);
    }
    else {
      LeftMotor1.spin(forward, power, pct);
      RightMotor1.spin(forward, power, pct);
    }

    wait(20, msec);
  }

  while (usingFlyWheel) {
    kP = 0.5;
    kI = 0.005;
    kD = 0.5;
    //sensorValue = FlyWheel1.position(rev);
    error = setPoint - power;

    integral = integral + error;
    //if (fabs(integral) > 500) {integral = 500;}

    derivative = error - prevError;
    prevError = error;

    power += error * kP + integral * kI + derivative * kD;

    FlyWheel1.spin(forward, power, rpm);
    FlyWheel2.spin(forward, power, rpm);

    wait(20, msec);
  }
}

//current function for turning the robot, converts the degrees given to revolutions required and sends it to the PIDLoop
void turnRobot(double setDegrees) {
  //need to convert to using radians to decrease the amount of math

  //setDegrees is the amount of degrees we want to turn
  //turnDiameter is the diameter of the circle of roation that the robot establishes while spinning
  double turnDiameter = 12.0;

  //convert the setDegrees given into the amount of inches required
  double requiredInches = setDegrees / 360 * M_PI * turnDiameter;

  //convert the inches to revolutions
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;

  PIDLoop(requiredRevolutions, true);
}