#include "vex.h"
#include "motion.h"
#include "math.h"

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

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
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

void autonomous(void) {
  /*
  -------------------------
  starts in front of roller
  -------------------------
  */
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);

  GoToPoint(0,12);

  /*
  setPID = -8;
  resetPID = true;
  isPID = true;
  wait(3000,msec);
  isPID = false;

  rollerMotor.spin(fwd,80,pct);
  wait(280,msec); //replace with color sensor
  rollerMotor.spin(fwd,0,pct);

  setPID = 8;
  resetPID = true;
  isPID = true;
  wait(3000,msec);
  isPID = false;

  GoToPoint(-1.1,11.5);

  //shooting
  SpinMotors(0);
  magLifter.set(false);
  setFlywheel = 600;
  resetFlywheel = true;
  isFlywheel = true;
  wait(2000,msec);
  indexer1.set(true);
  wait(500,msec);
  indexer1.set(false);
  wait(3500,msec);
  indexer1.set(true);
  wait(500,msec);
  indexer1.set(false);
  setFlywheel = 0;
  isFlywheel = false;
  */
  SpinMotors(0);
  isAuton = false;
  Brain.Screen.print("isExited");
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

void usercontrol(void) {
  isAuton = false; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = true;
  task StartUser(userController);
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
