#include "vex.h"
#include <iostream>

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lMotor1              motor         8               
// lMotor2              motor         9               
// lMotor3              motor         10              
// rMotor1              motor         11              
// rMotor2              motor         6               
// rMotor3              motor         13              
// Controller1          controller                    
// intakeMotor          motor         15              
// intakeMotor2         motor         7               
// FlywheelMotor        motor         20              
// rollerMotor          motor         1               
// indexer1             digital_out   A               
// endGame              digital_out   B               
// Controller2          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----
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
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);

  RotateBot(-20);
  IntakeDiscs();
  MoveBot(-10);
  MoveBot(5.5);
  RotateBot(100);
  IntakeDiscs(true);

  MoveBot(-10);
  SpinMotors(-10);
  SpinRoller(250);
  SpinMotors(0);
  MoveBot(5);

  FlywheelMotor.spin(fwd, 12, volt);
  RotateBot(12);
  MoveBot(8.6);
  ShootDiscs(3);
  FlywheelMotor.spin(fwd,0,volt);
  MoveBot(-7.6);

  RotateBot(120);
  MoveBot(-26, 60);
  IntakeDiscs();
  MoveBot(-30);
  IntakeDiscs(true);

  FlywheelMotor.spin(fwd, 11.70, volt);
  RotateBot(-87);
  ShootDiscs(3);
  FlywheelMotor.spin(fwd, 0, volt);

  RotateBot(93);
  IntakeDiscs();
  MoveBot(-52);
  IntakeDiscs(true);
  IntakeDiscs(false,true);

  FlywheelMotor.spin(fwd,12,volt);
  RotateBot(-64);
  MoveBot(3);
  ShootDiscs(3);
  FlywheelMotor.spin(fwd,0,volt);


  // RotateBot(-101);
  // wait(500,msec);
  // ShootDiscs(3);
  // FlywheelMotor.spin(fwd,0,volt);

  // RotateBot(101);
  // IntakeDiscs();
  // MoveBot(-54);
  // wait(1000,msec);
  // IntakeDiscs(true);
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
  Controller1.ButtonUp.pressed(ToggleForward);
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