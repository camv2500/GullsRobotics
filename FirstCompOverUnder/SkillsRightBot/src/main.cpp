#include "vex.h"

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lMotor1              motor         10              
// lMotor2              motor         9               
// lMotor3              motor         8               
// lMotor4              motor         7               
// rMotor1              motor         6               
// rMotor2              motor         4               
// rMotor3              motor         3               
// rMotor4              motor         2               
// cataMotor            motor         1               
// intakeRollerMotor    motor         19              
// endGame              digital_out   A               
// Controller1          controller                    
// autonPiston          digital_out   B               
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
  SpinMotors(100);
  wait(700,msec);
  MoveBot(-8);
  RotateBot(-135);
  MoveBot(18);
  RotateBot(-90);
  MoveBot(10);

  wait(1,sec);

  MoveBot(-5);
  RotateBot(90);
  MoveBot(10);
  RotateBot(45);
  MoveBot(34);
  //MoveBot(15);
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