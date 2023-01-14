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

static bool pidRunning = true;
static bool resetEncoders = false;
static float pidSetDegrees = 0;

double kP = 0.24, kI = 0.0, kD = 0;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

int pidController() {
  while (pidRunning) {
    if (resetEncoders) {
      resetEncoders = false;
      lMotor11.setPosition(0, degrees);
      lMotor12.setPosition(0, degrees);
      lMotor13.setPosition(0, degrees);
      lMotor14.setPosition(0, degrees);
      rMotor17.setPosition(0, degrees);
      rMotor18.setPosition(0, degrees);
      rMotor19.setPosition(0, degrees);
      rMotor20.setPosition(0, degrees);
      integral = 0;
      derivative = 0;
    }
    
    lSensor = (lMotor11.position(degrees) + lMotor12.position(degrees) + 
      lMotor13.position(degrees) + lMotor14.position(degrees)) / 4;
    rSensor = (rMotor17.position(degrees) + rMotor18.position(degrees) + 
      rMotor19.position(degrees) + rMotor20.position(degrees)) / 4;
    sensorValue = (lSensor + rSensor) / 2;
    error = pidSetDegrees - sensorValue;

    integral = integral + error;
    if (fabs(integral) > 5000) {integral = 500;}

    derivative = error - prevError;
    prevError = error;

    power = error * kP + integral * kI + derivative * kD;

    lMotor11.spin(forward, power, pct);
    lMotor12.spin(forward, power, pct);
    lMotor13.spin(forward, power, pct);
    lMotor14.spin(forward, power, pct);
    rMotor17.spin(forward, power, pct);
    rMotor18.spin(forward, power, pct);
    rMotor19.spin(forward, power, pct);
    rMotor20.spin(forward, power, pct);

    wait(20, msec);
  }

  return 1;
}

void autonomous(void) {
  /*
  non-task pid
  sending number of degrees to the PDLoop
  PIDLoop(convDistance);
  //turnRobot(90);
  Brain.Screen.print("isExited");
  LeftMotor1.spin(forward, 0, pct);
  RightMotor1.spin(forward, 0, pct);
  */

  
  //task based pid
  task StartTask(pidController);

  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  //In inches
  double distance = 12;
  double convDistance = (distance/circumferenceOfWheel)*outputRat*360.0;

  resetEncoders = true;
  pidSetDegrees = convDistance;

  vex::task::sleep(5000);

  resetEncoders = true;
  pidSetDegrees = 0;

  //distance = 24;
  //convDistance = (distance/circumferenceOfWheel)*outputRat*360.0;
  //resetEncoders = true;
  //pidSetDegrees = convDistance;
  

  
  //PIDLoop(400, false, true);
  Brain.Screen.print("isExited");
  lMotor11.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
  rMotor17.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
  lMotor12.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
  rMotor18.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
  lMotor13.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
  rMotor19.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
  lMotor14.spin(fwd, Controller1.Axis2.position(percent), vex::velocityUnits::pct);
  rMotor20.spin(fwd, Controller1.Axis3.position(percent), vex::velocityUnits::pct);
  
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
    if (Controller1.ButtonUp.pressing()) {
      FlyWheel1.spin(forward, 100, pct);
      FlyWheel2.spin(forward, 100, pct);
    }
    else {
      FlyWheel1.spin(forward, 0, pct);
      FlyWheel2.spin(forward, 0, pct);
    }
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
