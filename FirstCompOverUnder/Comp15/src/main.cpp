#include "vex.h"
//https://docs.google.com/document/d/1A3jqPkuVcELUMtA7aDif4NWK0hWnhuneMJUJ1md91NY/edit?usp=sharing
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lMotor1              motor         11              
// lMotor2              motor         12              
// lMotor3              motor         13              
// rMotor1              motor         18              
// rMotor2              motor         19              
// rMotor3              motor         20              
// cataMotor            motor         5               
// intakeRollerMotor    motor         10              
// Controller1          controller                    
// cataLimit            limit         H               
// intakeLift           digital_out   F               
// intakeFlip           digital_out   C               
// wings                digital_out   A               
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
  intakeLift.set(false);
  intakeFlip.set(true);
  wings.set(false);
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

  /*
  //example of how to use functions

  //moves the bot the provided amount of inches (roughly)
  //i wouldnt use a tape measurer to get the distance for these but rather tune each one
  //until it moves the way you want
  MoveBot(12);

  //rotates the bot clockwise? the amout of degrees provided (even more roughly)
  //this function needs to be tuned to how you want even more than movebot
  RotateBot(90);

  //send true to turn the intake motor on, false to turn it off
  //can also use second parameter to tell a specific power, default 100
  IntakeBalls(true, 40);

  //spins the intake backwards to outake any balls
  //not sure if will be used in auton but will be used in user
  //second paramter tells power to send motor if desired, default 100
  OuttakeBalls(true, 70);

  //shoots the current ball and gets the program ready to reload the catapult
  //if given a parameter, the program will wait that long in milliseconds after shooting to continue. default 0
  ShootBall(100);
  */

  SpinMotors(-100);
  wait(200,msec);
  intakeLift.set(true);
  MoveBot(8);
  RotateBot(-45);
  MoveBot(14);
  RotateBot(90);
  intakeFlip.set(false);
  IntakeBalls(true);
  MoveBot(10);

  //shoot balls
  for (int i = 0; i < 22; i++) {
    wait(150,msec);
    MoveBot(-7);
    ShootDiscs(0);
    MoveBot(7);
  }

  //last shot
  wait(150,msec);
  MoveBot(-7);
  ShootDiscs(0);
  wait(600,msec);
  //shot balls end

  intakeLift.set(false);
  intakeFlip.set(true);
  IntakeBalls(false);

  RotateBot(90);
  MoveBot(-20);
  RotateBot(-36);
  OuttakeBalls(false);
  intakeFlip.set(true);
  intakeLift.set(false);

  //i miss u guys

  MoveBot(-86);
  RotateBot(-40);
  MoveBot(-16);
  SpinMotors(-100);
  wait(1200,msec);
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
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);

  SpinMotors(-100);
  wait(200,msec);
  intakeLift.set(true);
  MoveBot(8);
  RotateBot(-45);
  MoveBot(14);
  RotateBot(90);
  intakeFlip.set(false);
  IntakeBalls(true);
  MoveBot(10);

  //shoot balls
  for (int i = 0; i < 22; i++) {
    wait(150,msec);
    MoveBot(-7);
    ShootDiscs(0);
    MoveBot(7);
  }

  //last shot
  wait(150,msec);
  MoveBot(-7);
  ShootDiscs(0);
  wait(800,msec);
  //shot balls end

  intakeLift.set(false);
  IntakeBalls(false);

  Controller1.ButtonL1.pressed(ToggleIntakeLift);
  Controller1.ButtonL2.pressed(ToggleIntakeFlip);
  Controller1.ButtonR2.pressed(ToggleWings);
  
  isAuton = false; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = true;
  task StartUser(userController);

  Controller1.rumble("-");
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