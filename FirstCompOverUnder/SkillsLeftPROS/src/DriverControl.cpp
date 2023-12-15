#include "DriverControl.h"

// Constants

// const int Intake_Speed = 100; // Percentage intake motor speed
// const int Lift_Speed = 100; // Percentage Lift motor speed

/////////////////////////////////////////////////////////////////////////////////////
//////                              GLOBAL VARIABLES                           //////
/////////////////////////////////////////////////////////////////////////////////////
bool intakeLiftState = true; bool intakeFlipState = true; bool wingsState = true; 
bool buttonYPressed = false; bool buttonXPressed = false; bool limitSwitch = false;

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

    if (master.get_digital(E_CONTROLLER_DIGITAL_L1)) {
      ToggleIntakeLift();
    }
    if (master.get_digital(E_CONTROLLER_DIGITAL_L2)) {
      ToggleIntakeFlip();
    }
    if (master.get_digital(E_CONTROLLER_DIGITAL_R2)) {
      ToggleWings();
    }

    if (master.get_digital_new_press(E_CONTROLLER_DIGITAL_X)) {
      // cataMotor.spinFor(fwd,45,deg);
      cataMotor.move(45);
      setButtonXPressed();
    } 

    ShootBallAuto();

    // if (Controller1.ButtonX.pressing() && cataLimit.pressing()) {
    //   cataMotor.spin(fwd,40,pct);
    // }
    // else if (cataLimit.pressing()) {
    //   cataMotor.stop(brakeType::coast);
    // }
    // else {
    //   cataMotor.spin(fwd,40,pct);
    // }

    if(master.get_digital(E_CONTROLLER_DIGITAL_R1)) {
      IntakeBalls(true, 100);
    }
    else {
      IntakeBalls(false);
    }

    delay(10);
  }

  return 1;
}

void ShootBallAuto() {
  if (buttonXPressed) {
    if (!cataLimit.get_value()) {
      cataMotor.move(60);
    }
    else {
      cataMotor.set_brake_mode(E_MOTOR_BRAKE_COAST);
      cataMotor.brake();
      buttonXPressed = false;
    }
  }
}

void setButtonXPressed() {
  intakeLift.set_value(true);
  intakeFlip.set_value(false);
  buttonXPressed = true;
}

void setButtonYPressed() {
  intakeLift.set_value(true);
  intakeFlip.set_value(false);
}

void ToggleIntakeLift() {
  if (intakeLiftState == true) {
    intakeLift.set_value(false);
    intakeLiftState = false;
  }
  else {
    intakeLift.set_value(true);
    intakeLiftState = true;
  }
}

void ToggleIntakeFlip() {
  if (intakeFlipState == true) {
    intakeFlip.set_value(false);
    intakeFlipState = false;
  }
  else {
    intakeFlip.set_value(true);
    intakeFlipState = true;
  }
}

void ToggleWings() {
  if (wingsState == true) {
    wings.set_value(false);
    wingsState = false;
  }
  else {
    wings.set_value(true);
    wingsState = true;
  }
}