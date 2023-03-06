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
  does not start in front of roller
  -------------------------
  */
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);

  RotateBot(-10,500);
  ShootDiscs(2);
  wait(1000,msec);
  RotateBot(10,500);
  MoveBot(-15,2000);
  RotateBot(-90,2500);
  MoveBot(23,3000);
  RotateBot(43,2000);
  IntakeDiscs();
  MoveBot(17,2000);
  MoveBot(5,2000);
  IntakeDiscs(true);
  RotateBot(85);
  ShootDiscs(1);
  RotateBot(-88);
  IntakeDiscs();
  MoveBot(12,2000);
  MoveBot(3,2000);
  IntakeDiscs(true);
  RotateBot(105,2000);
  ShootDiscs(1);
  RotateBot(-110,2000);
  IntakeDiscs();
  MoveBot(12,2000);
  MoveBot(3,2000);
  IntakeDiscs(true);
  RotateBot(125,2000);
  ShootDiscs(1);
  RotateBot(100,2000);
  MoveBot(-40,4000);
  MoveBot(4,1200);
  RotateBot(90,1500);
  MoveBot(25,3000);

  
  
  SpinMotors(0);
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
