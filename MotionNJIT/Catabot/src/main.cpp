// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lMotor1              motor         3               
// lMotor2              motor         4               
// Controller1          controller                    
// rMotor1              motor         7               
// rMotor2              motor         8               
// rMotor3              motor         9               
// rMotor4              motor         10              
// lMotor3              motor         5               
// lMotor4              motor         6               
// cataMotor            motor         1               
// endGame              digital_out   C               
// intakeRollerMotor    motor         2               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
  does start in front of roller
  -------------------------
  */
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);

  MoveBot(-6);
  SpinRoller(280);
  MoveBot(6);
  GoToPoint(-3,11.5);
  ShootDiscs(3);
  GoToPoint(0,0);
  GoToPoint(10,10);
  IntakeDiscs();
  GoToPoint(12,12);
  GoToPoint(16,16);
  GoToPoint(20,20);
  IntakeDiscs(true);
  GoToPoint(12,36);
  ShootDiscs(3);
  GoToPoint(30,36);
  IntakeDiscs();
  GoToPoint(30,32);
  GoToPoint(30,28);
  GoToPoint(30,24);
  IntakeDiscs(true);
  GoToPoint(12,36);

  Brain.Screen.print("isExited");
  wait(200,msec);
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
