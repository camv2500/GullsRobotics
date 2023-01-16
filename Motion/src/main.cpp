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

static bool pidRunning = true, isTurning = false;
static bool resetEncoders = false;
static float pidSetDegrees = 0;

double kP = 0.088, kI = 0.0, kD = 0.06;
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

    if (pidSetDegrees != 0) {
      lSensor = (lMotor11.position(degrees) + lMotor12.position(degrees) + 
        lMotor13.position(degrees) + lMotor14.position(degrees)) / 4;
      rSensor = (rMotor17.position(degrees) + rMotor18.position(degrees) + 
        rMotor19.position(degrees) + rMotor20.position(degrees)) / 4;
      if (isTurning) {sensorValue = rSensor;}
      else {sensorValue = (lSensor + rSensor) / 2;}
      error = pidSetDegrees - sensorValue;

      integral = integral + error;
      if (fabs(integral) > 5000) {integral = 500;}

      derivative = error - prevError;
      prevError = error;

      power = error * kP + integral * kI + derivative * kD;

      if (isTurning) {
        lMotor11.spin(reverse, power, pct); rMotor17.spin(forward, power, pct);
        lMotor12.spin(reverse, power, pct); rMotor18.spin(forward, power, pct);
        lMotor13.spin(reverse, power, pct); rMotor19.spin(forward, power, pct);
        lMotor14.spin(reverse, power, pct); rMotor20.spin(forward, power, pct);
      }
      else {
        lMotor11.spin(forward, power, pct); rMotor17.spin(forward, power, pct);
        lMotor12.spin(forward, power, pct); rMotor18.spin(forward, power, pct);
        lMotor13.spin(forward, power, pct); rMotor19.spin(forward, power, pct);
        lMotor14.spin(forward, power, pct); rMotor20.spin(forward, power, pct);
      }
    }
    else {
      lMotor11.spin(forward, 0, pct);
      rMotor17.spin(forward, 0, pct);
      lMotor12.spin(forward, 0, pct);
      rMotor18.spin(forward, 0, pct);
      lMotor13.spin(forward, 0, pct);
      rMotor19.spin(forward, 0, pct);
      lMotor14.spin(forward, 0, pct);
      rMotor20.spin(forward, 0, pct);
    }

    wait(20, msec);
  }

  return 1;
}

static bool resetFlywheelEncoders = false;
static float flywheelSetRPM = 0;
double fkP = 0.0018, fkI = 0, fkD = 0.00018, fkF = 0.0212;
double flyWheelError = 0, fprevError = 0, fintegral = 0, fderivative = 0, fpower = 0;
double kF, feedForward;

int flyWheelController() {
  while (1) {
    if (resetFlywheelEncoders) {
      resetFlywheelEncoders = false;
      fintegral = 0;
      fderivative = 0;
      feedForward = flywheelSetRPM; 
    }

    if (flywheelSetRPM != 0) {
      flyWheelError = flywheelSetRPM - (FlyWheel1.velocity(rpm) + FlyWheel2.velocity(rpm) / 2);

      fintegral = fintegral + flyWheelError;
      if (fabs(fintegral) > 12000) {fintegral = 12000;}

      fderivative = flyWheelError - fprevError;
      fprevError = flyWheelError;

      fpower = flyWheelError * fkP + fintegral * fkI + fderivative * fkD + feedForward * fkF;

      FlyWheel1.spin(forward, fpower, volt);
      FlyWheel2.spin(forward, fpower, volt);

      wait(20, msec);
    }
    else {
      FlyWheel1.spin(forward, 0, volt);
      FlyWheel2.spin(forward, 0, volt);
    }
  }

  return 1;
}

void turnRobot(double setDegrees) {
  double turnDiameter = 12.0;

  double requiredInches = setDegrees / 360 * M_PI * turnDiameter;

  //convert the inches to revolutions
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;

  isTurning = true;
  resetEncoders = true;
  pidSetDegrees = requiredRevolutions;
}

void autonomous(void) {
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

/*
  distance = 54;
  convDistance = (distance/circumferenceOfWheel)*outputRat*360.0;
  resetEncoders = true;
  pidSetDegrees = convDistance;
  vex::task::sleep(2500);
  pidSetDegrees = 0;

  turnRobot(-98);
  vex::task::sleep(2000);
  isTurning = false;
  pidSetDegrees = 0;

  distance = 42;
  convDistance = (distance/circumferenceOfWheel)*outputRat*360.0;
  resetEncoders = true;
  pidSetDegrees = convDistance;
  vex::task::sleep(2500);
  pidSetDegrees = 0;

  turnRobot(-50);
  vex::task::sleep(2000);
  isTurning = false;
  pidSetDegrees = 0;

  distance = 5;
  convDistance = (distance/circumferenceOfWheel)*outputRat*360.0;
  resetEncoders = true;
  pidSetDegrees = convDistance;
  resetFlywheelEncoders = true;
  flywheelSetRPM = 500;
  vex::task::sleep(2500);
  pidSetDegrees = 0;
*/
  Brain.Screen.print("isExited");
  /*
  lMotor11.spin(fwd, 0, vex::velocityUnits::pct);
  rMotor17.spin(fwd, 0, vex::velocityUnits::pct);
  lMotor12.spin(fwd, 0, vex::velocityUnits::pct);
  rMotor18.spin(fwd, 0, vex::velocityUnits::pct);
  lMotor13.spin(fwd, 0, vex::velocityUnits::pct);
  rMotor19.spin(fwd, 0, vex::velocityUnits::pct);
  lMotor14.spin(fwd, 0, vex::velocityUnits::pct);
  rMotor20.spin(fwd, 0, vex::velocityUnits::pct);
  */
  
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

void toggleFlyWheelOn() {
  resetFlywheelEncoders = true;
  flywheelSetRPM = 462;
}

void toggleFlyWheelOff() {
  flywheelSetRPM = 0;
}

void usercontrol(void) {
  task StartFlyWheel(flyWheelController);
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

    Controller1.ButtonX.pressed(toggleFlyWheelOn);
    Controller1.ButtonY.pressed(toggleFlyWheelOff);

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
