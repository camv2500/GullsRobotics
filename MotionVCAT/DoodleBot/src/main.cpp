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
  //THIS IS THE BOT THAT STARTS AWAY FROM THE ROLLER
  //MAKE SURE YOU HAVE THE RIGHT PROGRAM
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);

  GoToPoint(20,-1);
  setTurning = -105;
  resetTurning = true;
  isTurning = true;
  wait(4000, msec);
  isTurning = false;
  rollerMotor.spin(fwd,100,pct);
  lMotor1.spin(reverse,20,pct);
  lMotor2.spin(reverse,20,pct);
  lMotor3.spin(reverse,20,pct);
  lMotor4.spin(reverse,20,pct);
  rMotor1.spin(reverse,20,pct);
  rMotor2.spin(reverse,20,pct);
  rMotor3.spin(reverse,20,pct);
  rMotor4.spin(reverse,20,pct);

  /*
  GoToPoint(22,0);
  GoToPoint(22,2);
  GoToPoint(22,-4,true);
  rollerMotor.spin(fwd, 50, pct);
  wait(120, msec);
  rollerMotor.spin(fwd, 0, pct);
  
  magLifter.set(false);
  GoToPoint(24,0);
  GoToPoint(24,1);
  GoToPoint(24,-4);
  rollerMotor.spin(fwd, 50, pct);
  wait(120, msec);
  rollerMotor.spin(fwd, 0, pct);
  ToggleFlywheelOn();
  GoToPoint(26,18);
  indexer1.set(true);
  wait(120, msec);
  indexer1.set(false);
  wait(120,msec);
  indexer1.set(true);
  wait(120, msec);
  indexer1.set(false);
  magLifter.set(true);
  ToggleFlywheelOff();
  intakeMotor.spin(fwd, 100, pct);
  GoToPoint(-6,20);
  GoToPoint(-18,31);
  intakeMotor.spin(fwd, 0, pct);
  ToggleFlywheelOn();
  magLifter.set(false);
  GoToPoint(-14,43);
  indexer1.set(true);
  wait(120, msec);
  indexer1.set(false);
  wait(120,msec);
  indexer1.set(true);
  wait(120, msec);
  indexer1.set(false);
  ToggleFlywheelOff();
  */
  wait(3000,msec);
  Brain.Screen.print("isExited");
  SpinMotors(0); 
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
