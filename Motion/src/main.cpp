/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// lMotor1              motor         15              
// lMotor2              motor         16              
// Controller1          controller                    
// FlyWheel1            motor         9               
// FlyWheel2            motor         10              
// rMotor1              motor         11              
// rMotor2              motor         12              
// rMotor3              motor         13              
// rMotor4              motor         14              
// lMotor3              motor         17              
// lMotor4              motor         19              
// intakeMotor          motor         5               
// magLifter            digital_out   A               
// diskPusher1          digital_out   B               
// endGame              digital_out   C               
// rollerMotor          motor         21              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "motion.h"

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

static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
static bool resetPID = true, resetTurning = true, resetFlywheel = true;
static double setPID = 0, setTurning = 0, setFlywheel = 0;

int autonController() {
  while(isAuton) {
    if (isPID) {
      if (resetPID) {
        setPID = ConvertInchesToRevolutions(setPID);
        runPID(setPID, true);
        resetPID = false;
      }
      else {runPID(setPID);}
    }

    if (isTurning) {
      if (resetTurning) {
        setTurning = ConvertDegreesToInches(setTurning);
        setTurning = ConvertInchesToRevolutions(setTurning);
        runPID(setTurning, true, true);
        resetTurning = false;
      }
      else {runPID(setTurning, false, true);}
    }

    if (isFlywheel) {
      if (resetFlywheel) {
        runFlywheel(setFlywheel, true);
        resetFlywheel = false;
      }
      else {runFlywheel(setFlywheel);}
    }

    wait(10, msec);
  }
  return 1;
}

void autonomous(void) {
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);

  setFlywheel = 400;
  isFlywheel = true;

  setPID = 12;
  isPID = true;
  wait(1000, msec);
  isPID = false;
  
  /*
  task StartPID(pidController);
  task StartFlyWheel(flyWheelController);
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;

  //In inches
  double distance = -8;
  double convDistance = (distance/circumferenceOfWheel)*outputRat*360.0;
  resetEncoders = true;
  pidSetDegrees = convDistance;
  vex::task::sleep(1000);

  rollerMotor.spin(fwd, 12, volt);
  vex::task::sleep(290);
  rollerMotor.spin(fwd, 0, volt);

  Brain.Screen.print("isExited");
  SpinMotors(0); */
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

static bool isUserFlywheel = false, resetUserFlywheel = false;
static double setUserFlywheel = 0;

void ToggleFlywheelOn() {
  resetUserFlywheel = true;
  setUserFlywheel = 450;
  isUserFlywheel = true;
}

void ToggleFlywheelOff() {
  isUserFlywheel = false;
  resetUserFlywheel = true;
  setUserFlywheel = 0;
  isUserFlywheel = true;
}

void userSpinMotors() {

}

int userController() {
  while(isUser) {
    if (isUserFlywheel) {
      if (resetUserFlywheel) {
        runFlywheel(setUserFlywheel, true);
        resetUserFlywheel = false;
      }
      else {runFlywheel(setUserFlywheel);}
    }

    lMotor1.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor1.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
    lMotor2.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor2.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
    lMotor3.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor3.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
    lMotor4.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor4.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);

    Controller1.ButtonX.pressed(ToggleFlywheelOn);
    Controller1.ButtonY.pressed(ToggleFlywheelOff);

    if (Controller1.ButtonR1.pressing()) {
      magLifter.set(true);
    }
    else {
      magLifter.set(false);
    }

    if (Controller1.ButtonL1.pressing()) {
      intakeMotor.spin(fwd, 12, volt);
    }
    else {
      intakeMotor.spin(fwd, 0, volt);
    }

    if (Controller1.ButtonL2.pressing()) {
      rollerMotor.spin(fwd, 12, volt);
    }
    else {
      rollerMotor.spin(fwd, 0, volt);
    }

    if (Controller1.ButtonR2.pressing()) {
      diskPusher1.set(true);
    }
    else {
      diskPusher1.set(false);
    }

    wait(10,msec);
  }

  return 1;
}

void usercontrol(void) {
  isUser = true; isAuton = false;
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
