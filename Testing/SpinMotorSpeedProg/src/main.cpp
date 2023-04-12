/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\User                                             */
/*    Created:      Wed Apr 12 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Motor1               motor         1               
// Controller1          controller                    
// Flywheel             motor         4               
// Intake               motor         3               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  while (true) {
  if (Controller1.ButtonUp.pressing()) {
    Motor1.spin(fwd,10,pct);
  }
  else if (Controller1.ButtonRight.pressing()) {
    Motor1.spin(fwd,20,pct);
  }
  else if (Controller1.ButtonDown.pressing()) {
    Motor1.spin(fwd,30,pct);
  }
  else if (Controller1.ButtonLeft.pressing()) {
    Motor1.spin(fwd,40,pct);
  }
  else if (Controller1.ButtonX.pressing()) {
    Motor1.spin(fwd,50,pct);
  }
  else if (Controller1.ButtonA.pressing()) {
    Motor1.spin(fwd,60,pct);
  }
  else if (Controller1.ButtonB.pressing()) {
    Motor1.spin(fwd,70,pct);
  }
  else if (Controller1.ButtonY.pressing()) {
    Motor1.spin(fwd,80,pct);
  }
  else if (Controller1.ButtonL1.pressing()) {
    Motor1.spin(fwd,90,pct);
  }
  else if (Controller1.ButtonR1.pressing()) {
    Motor1.spin(fwd,100,pct);
  }
  else {
    Motor1.spin(fwd,0,pct);
  }

  //flywheel
  if (Controller1.ButtonL2.pressing()) {
    Flywheel.spin(reverse,100,pct);
  }
  else {
    Flywheel.spin(reverse,0,pct);
  }

  //intake
  if (Controller1.ButtonR2.pressing()) {
    Intake.spin(fwd,100,pct);
  }
  else {
    Intake.spin(fwd,0,pct);
  }
  }
}
