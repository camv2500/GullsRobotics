#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"

using namespace pros;

// Constants

// const int Intake_Speed = 100; // Percentage intake motor speed
// const int Lift_Speed = 100; // Percentage Lift motor speed

// Variables

int userController() {
  while(isUser) {
    //calculate the power for the left and right side independently using two joysticks (tank control)
    double leftDrive = (Controller1.Axis3.value());
    double rightDrive = (Controller1.Axis2.value());

    //calculate the power for the left and right side independently using one joystick (arcade control)
    //double leftDrive = (Controller1.Axis2.value() - Controller1.Axis1.value());
    //double rightDrive = (Controller1.Axis2.value() + Controller1.Axis1.value());

    lMotor1.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor2.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor3.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor4.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    rMotor1.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor2.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor3.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor4.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);

    //intake control
    if(Controller1.ButtonL1.pressing()) {
      IntakeBalls(true, 100);
    }
    else if (Controller1.ButtonL2.pressing()) {
      OuttakeBalls(true, 100);
    }
    else {
      IntakeBalls(false);
    }

    //Maunal Catapult Control
    if(Controller1.ButtonR1.pressing()) {
      LowerCatapult(true, 100);
    }
    else if (Controller1.ButtonR2.pressing()) {
      RaiseCatapult(true, 100);
    }
    else {
      LowerCatapult(false);
    }

    /* commented out bc no limit switch
    //catapult control with limit switch
    if (Controller1.ButtonR1.pressing() && cataLimit.pressing()) {
      cataMotor.spin(fwd,100,pct);
    }
    else if (cataLimit.pressing()) {
      cataMotor.stop(brakeType::hold);
    }
    else {
      cataMotor.spin(fwd,100,pct);
    }
    */

    wait(10,msec);
  }

  return 1;
}