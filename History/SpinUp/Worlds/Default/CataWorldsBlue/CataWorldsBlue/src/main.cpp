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
// cataLimit            limit         C               
// OpticalRight         optical       21              
// OpticalLeft          optical       18              
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// cataLimit            limit         C               
// OpticalRight         optical       21              
// OpticalLeft          optical       18              
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// cataLimit            limit         C               
// OpticalRight         optical       21              
// ---- END VEXCODE CONFIGURED DEVICES ----
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
// cataLimit            limit         C               
// ---- END VEXCODE CONFIGURED DEVICES ----
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
  OpticalRight.setLightPower(50, percent);
  OpticalLeft.setLightPower(50, percent);
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
  double timer = 0;

  MoveBot(-21);
  RotateBot(84);
  MoveBot(-7.5);
  while(OpticalRight.hue() > 150 && OpticalRight.hue() < 250){
    if(timer >= 200) {
      SpinMotors(-15);
    }
    SpinRoller(300);
    timer+=10;
  }
  MoveBot(6);
  RotateBot(90);
  SpinMotors(0);
  MoveBot(-42);
  RotateBot(40);
  IntakeDiscs();
  MoveBot(-10);
  vex::task::sleep(2000);
  IntakeDiscs(true);


  
  // ShootDiscs();
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