/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\cjbar                                            */
/*    Created:      Sun Oct 23 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// select               bumper        C               
// UP                   bumper        A               
// DOWN                 bumper        B               
// Controller1          controller                    
// leftMotor            motor         1               
// rightMotor           motor         10              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "functions.h"
using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  //leftMotor.startRotateFor();
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    leftMotor.spin(fwd, Controller1.Axis3.position(), pct);
    rightMotor.spin(fwd, Controller1.Axis2.position(), pct);
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  // Run the pre-autonomous function.
  pre_auton();
  autonScreen(Competition);
  landingPage();
  // Prevent main from exiting with an infinite loop.
  return 0;
}
