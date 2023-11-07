#include "AutonFunctions.h"

/////////////////////////////////////////////////////////////////////////////////////
//////                              GLOBAL CONSTANTS                           //////
/////////////////////////////////////////////////////////////////////////////////////

//reset all the encoders
// void ResetEncoders() {
//   lMotor1.setPosition(0,degrees); lMotor2.setPosition(0,degrees);
//   lMotor3.setPosition(0,degrees); lMotor4.setPosition(0,degrees);
//   rMotor1.setPosition(0,degrees); rMotor2.setPosition(0,degrees);
//   rMotor3.set_position(0,degrees); rMotor4.setPosition(0,degrees);
// }
void ResetEncoders() {
  lMotor1.tare_position(); lMotor2.tare_position();
  lMotor3.tare_position(); lMotor4.tare_position();
  rMotor1.tare_position(); rMotor2.tare_position();
  rMotor3.tare_position(); rMotor4.tare_position();
}

//spin the motors for pid
void SpinMotors(double power, bool isTurning) {
  if(isTurning) {
    // lMotor1.spin(reverse, power, pct); rMotor1.spin(forward, power, pct);
    // lMotor2.spin(reverse, power, pct); rMotor2.spin(forward, power, pct);
    // lMotor3.spin(reverse, power, pct); rMotor3.spin(forward, power, pct);
    // lMotor4.spin(reverse, power, pct); rMotor4.spin(forward, power, pct);
    lMotor1.move(-power); rMotor1.move(power);
    lMotor2.move(-power); rMotor2.move(power);
    lMotor3.move(-power); rMotor3.move(power);
    lMotor4.move(-power); rMotor4.move(power);
  }
  else {
    // lMotor1.spin(forward, power, pct); rMotor1.spin(forward, power, pct);
    // lMotor2.spin(forward, power, pct); rMotor2.spin(forward, power, pct);
    // lMotor3.spin(forward, power, pct); rMotor3.spin(forward, power, pct);
    // lMotor4.spin(forward, power, pct); rMotor4.spin(forward, power, pct);
    lMotor1.move(power); rMotor1.move(power);
    lMotor2.move(power); rMotor2.move(power);
    lMotor3.move(power); rMotor3.move(power);
    lMotor4.move(power); rMotor4.move(power);
  }
}

//lets the bot intake balls
void IntakeBalls(bool intakeState, double intakePower) {
  if(intakeState) {intakeRollerMotor.move(intakePower);}
  else {intakeRollerMotor.move(0);}
}

//lets the bot outtake balls
void OuttakeBalls(bool outtakeState, double outtakePower) {
  if(outtakeState) {intakeRollerMotor.move(-outtakePower);}
  else {intakeRollerMotor.move(0);}
}

//manual catapult control, lowers it down to accept balls
void LowerCatapult(bool catapultState, double catapultPower) {
  if (catapultState) {cataMotor.move(catapultPower);}
  else {cataMotor.move(0);}
}

//manual catapult control, raises the catapult until it reaches max raised. dont abuse
void RaiseCatapult(bool catapultState, double catapultPower) {
  if (catapultState) {cataMotor.move(-catapultPower);}
  else {cataMotor.move(0);}
}

