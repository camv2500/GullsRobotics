#include "robot-config.h"
#include "vex.h"

void PDLoop(double setPoint, bool isTurning = false) {
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
      RightMotor1.spin(forward, power, pct);
      wait(20, msec);
    }
    else {
      LeftMotor1.spin(forward, power, pct);
      RightMotor1.spin(forward, power, pct);
      wait(20, msec);
    }
  }
}

//current function for turning the robot, converts the degrees given to revolutions required and sends it to the PDLoop
void turnRobot(double setDegrees) {
  //setDegrees is the amount of degrees we want to turn
  //turnDiameter is the diameter of the circle of roation that the robot establishes while spinning
  double turnDiameter = 13.0;

  //convert the setDegrees given into the amount of inches required
  double requiredInches = setDegrees / 360 * M_PI * turnDiameter;

  //convert the inches to revolutions
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat;

  PDLoop(requiredRevolutions, true);

  /* old stuff just here for reference 
  double requiredDistance, rotationDegree;
  //this calculates how many inches is required to be moved each degree
  //track width * pi / total degrees in one rotation = 0.0575958653
  rotationDegree = 6.6 * M_PI / 360;
  //this converts the degrees given into an amount of rotations that can be used for the PDLoop
  //rotation degree above * how many degrees we wish to move / 2? / inches per degree = amount of degrees to move the robot
  requiredDistance = rotationDegree * setDegrees / 2 / 0.02836160034490785562;
  */
}