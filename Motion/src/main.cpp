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
// lMotor14             motor         14              
// lMotor13             motor         13              
// Controller1          controller                    
// FlyWheel1            motor         16              
// FlyWheel2            motor         15              
// rMotor17             motor         17              
// rMotor18             motor         18              
// rMotor19             motor         19              
// rMotor20             motor         20              
// lMotor11             motor         11              
// lMotor12             motor         12              
// intakeMotor          motor         5               
// magLifter            digital_out   A               
// diskPusher1          digital_out   B               
// endGame              digital_out   C               
// rollerMotor          motor         1               
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

static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false; 
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
  isAuton = true;
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

  distance = 5;
  convDistance = (distance/circumferenceOfWheel)*outputRat*360.0;
  resetEncoders = true;
  pidSetDegrees = convDistance;
  resetFlywheelEncoders = true;
  flywheelSetRPM = 550;
  vex::task::sleep(1500);
  pidSetDegrees = 0;

  turnRobot(-7);
  vex::task::sleep(3000);
  isTurning = false;
  pidSetDegrees = 0;

  diskPusher1.set(true);
  vex::task::sleep(1000);
  diskPusher1.set(false);
  vex::task::sleep(1000);
  diskPusher1.set(true);
  */
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

/*
void toggleFlyWheelOn() {
  resetFlywheelEncoders = true;
  flywheelSetRPM = 462;
}

void toggleFlyWheelOff() {
  flywheelSetRPM = 0;
}
*/

void usercontrol(void) {
  //task StartFlyWheel(flyWheelController);
  // User control code here, inside the loop
  while (1) {
    lMotor11.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor17.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
    lMotor12.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor18.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
    lMotor13.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor19.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
    lMotor14.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
    rMotor20.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);

    //Controller1.ButtonX.pressed(toggleFlyWheelOn);
    //Controller1.ButtonY.pressed(toggleFlyWheelOff);

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
    
    //magLifter.set(false);
    //diskPusher1.set(false);
    wait(20, msec);
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
