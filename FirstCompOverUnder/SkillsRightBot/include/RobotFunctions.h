#include "robot-config.h"
#include "vex.h"

bool intakeLiftState = false; bool intakeFlipState = true; bool wingsState = true; 
bool buttonYPressed = false; bool buttonXPressed = false; bool limitSwitch = false;

//reset all the encoders
void ResetEncoders() {
  lMotor1.setPosition(0,degrees); lMotor2.setPosition(0,degrees);
  lMotor3.setPosition(0,degrees);
  rMotor1.setPosition(0,degrees); rMotor2.setPosition(0,degrees);
  rMotor3.setPosition(0,degrees);
}

//spin the motors for pid
void SpinMotors(double power, bool isTurning = false) {
  if(isTurning) {
    lMotor1.spin(reverse, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(reverse, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(reverse, power, pct); rMotor3.spin(forward, power, pct);
  }
  else {
    lMotor1.spin(forward, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(forward, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(forward, power, pct); rMotor3.spin(forward, power, pct);
  }
}

//lets the bot intake balls
void IntakeBalls(bool intakeState = false, double intakePower = 100) {
  if(intakeState) {intakeRollerMotor.spin(fwd,intakePower,pct);}
  else {intakeRollerMotor.spin(fwd,0,pct);}
}

//lets the bot outtake balls
void OuttakeBalls(bool outtakeState = false, double outtakePower = 100) {
  if(outtakeState) {intakeRollerMotor.spin(reverse,outtakePower,pct);}
  else {intakeRollerMotor.spin(fwd,0,pct);}
}

//manual catapult control, lowers it down to accept balls
void LowerCatapultManual(bool catapultState = false, double catapultPower = 100) {
  if (catapultState) {cataMotor.spin(fwd, catapultPower, pct);}
  else {cataMotor.spin(fwd, 0, pct);}
}

//manual catapult control, raises the catapult until it reaches max raised. dont abuse
void RaiseCatapultManual(bool catapultState = false, double catapultPower = 100) {
  if (catapultState) {cataMotor.spin(reverse, catapultPower, pct);}
  else {cataMotor.spin(fwd, 0, pct);}
}

void ShootBallAuto() {
  if (buttonXPressed) {
    if (!cataLimit.pressing()) {
      cataMotor.spin(fwd,60,pct);
    }
    else {
      cataMotor.stop(brakeType::coast);
      buttonXPressed = false;
    }
  }
}

void setButtonXPressed() {
  intakeLift.set(true);
  intakeFlip.set(false);
  buttonXPressed = true;
}

void setButtonYPressed() {
  intakeLift.set(true);
  intakeFlip.set(false);
}

void ToggleIntakeLift() {
  if (intakeLiftState == true) {
    intakeLift.set(false);
    intakeLiftState = false;
  }
  else {
    intakeLift.set(true);
    intakeLiftState = true;
  }
}

void ToggleIntakeFlip() {
  if (intakeFlipState == true) {
    intakeFlip.set(false);
    intakeFlipState = false;
  }
  else {
    intakeFlip.set(true);
    intakeFlipState = true;
  }
}

void ToggleWings() {
  if (wingsState == true) {
    wings.set(false);
    wingsState = false;
  }
  else {
    wings.set(true);
    wingsState = true;
  }
}

