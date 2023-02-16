// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor1           motor         13              
// rightMotor1          motor         14              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor1           motor         13              
// rightMotor1          motor         14              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "function.h"
#include <cmath>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) 
{
  vexcodeInit();
  leftMotor1.setPosition(0,degrees);
  rightMotor1.setPosition(0,degrees);
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) 
{
  //this function is just tests at this point
  //every 30 degrees equates to roughly 1 inch traveled
  //PDLoop(360);
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  //In inches
  double distance = 12;
  double convDistance = (distance/circumferenceOfWheel)*outputRat;
  /*
  leftMotor1.startRotateFor(convDistance, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  rightMotor1.rotateFor(convDistance, vex::rotationUnits::rev, 100, vex::velocityUnits::pct);
  leftMotor1.stop(brakeType::brake);
  rightMotor1.stop(brakeType::brake);
  */
  Brain.Screen.print(convDistance * 360);
  Brain.Screen.newLine();
  PDLoop(convDistance*360);
  Brain.Screen.print("IsExited");
}


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) 
{
  //basic drive, will never exit
  while (1) 
  {
    leftMotor1.spin(fwd, Controller1.Axis3.value(), pct);
    rightMotor1.spin(fwd, Controller1.Axis3.value(), pct);
    //wait(20, msec);
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
