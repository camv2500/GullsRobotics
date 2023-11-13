#include "DriverControl.h"

// Constants

// const int Intake_Speed = 100; // Percentage intake motor speed
// const int Lift_Speed = 100; // Percentage Lift motor speed

// Variables

int userController() {
  while(isUser) {
    //calculate the power for the left and right side independently using two joysticks (tank control)
    double leftDrive = master.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    double rightDrive = master.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

    //calculate the power for the left and right side independently using one joystick (arcade control)
    //double leftDrive = (Controller1.Axis2.value() - Controller1.Axis1.value());
    //double rightDrive = (Controller1.Axis2.value() + Controller1.Axis1.value());

    lMotor1.move(controlCurve(leftDrive));
    lMotor2.move(controlCurve(leftDrive));
    lMotor3.move(controlCurve(leftDrive));
    // lMotor4.move(controlCurve(leftDrive));
    rMotor1.move(controlCurve(rightDrive));
    rMotor2.move(controlCurve(rightDrive));
    rMotor3.move(controlCurve(rightDrive));
    // rMotor4.move(controlCurve(rightDrive));

    //intake control
    if(master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      IntakeBalls(true, 100);
    }
    else if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      OuttakeBalls(true, 100);
    }
    else {
      IntakeBalls(false);
    }

    //Maunal Catapult Control
    if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      LowerCatapult(true, 100);
    }
    else if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
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

    delay(10);
  }

  return 1;
}