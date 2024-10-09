#include "robot-config.h"
#include "vex.h"

bool intakeFlipState = false; bool wingsState = true; 

//reset all the encoders
void ResetEncoders() {
  lMotor1.setPosition(0,degrees); lMotor2.setPosition(0,degrees);
  lMotor3.setPosition(0,degrees); lMotor4.setPosition(0,degrees);
  rMotor1.setPosition(0,degrees); rMotor2.setPosition(0,degrees);
  rMotor3.setPosition(0,degrees); rMotor4.setPosition(0,degrees);
}

//spin the motors for pid
void SpinMotors(double power, bool isTurning = false) {
  if(isTurning) {
    lMotor1.spin(reverse, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(reverse, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(reverse, power, pct); rMotor3.spin(forward, power, pct);
    lMotor4.spin(reverse, power, pct); rMotor4.spin(forward, power, pct);
  }
  else {
    lMotor1.spin(forward, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(forward, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(forward, power, pct); rMotor3.spin(forward, power, pct);
    lMotor4.spin(forward, power, pct); rMotor4.spin(forward, power, pct);
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
