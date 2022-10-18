/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
//my comment
// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// leftMotor1           motor         1               
// rightMotor1          motor         10              
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "function.h"

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

void pre_auton(void) 
{
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

void autonomous(void) 
{
  //sensorValueTotal : average of left and right motor encoders
  //sensorValueLeft : value of left drive train motor encoders
  //sensorValueRight : value of right drive train motor encoders
  //setpoint : the amount of rotations that we aim to move
  //derivative : holds the current amount of the derivative
  //prevError : holds the pervious error for calculation in the next cycle
  //power : holds the amount of power to give to the motor
  //error : hold the amount of distance left to go
  //kp : The kP value is used to tune our Porportional part of the PD controller
  //kD : the kD value is used to tune our Derivative part of the PD controller
  double sensorValueTotal, sensorValueLeft, sensorValueRight, setpoint = 1410.38;
  double derivative, prevError = 0;
  double power = 0, error = setpoint;
  double kP = 0.255, kD = 0.2;

  leftMotor1.setPosition(0,degrees);
  rightMotor1.setPosition(0,degrees);

  while (fabs(error) >= 1)
  {
    //wheel diamtere 3.25
    //wheel circumference 10.21
    //per full rotation travels 6.126 inches

    sensorValueLeft = leftMotor1.position(degrees);
    sensorValueRight = rightMotor1.position(degrees);
    sensorValueTotal = sensorValueLeft + sensorValueRight / 2;
    error = setpoint - sensorValueTotal;

    derivative = error - prevError;
    prevError = error;

    power = error * kP + derivative * kD;
    leftMotor1.spin(forward,power,pct);
    rightMotor1.spin(forward,power,pct);
    wait(20,msec);
  }

  Brain.Screen.print(error);
  Brain.Screen.print(" ");
  Brain.Screen.print(derivative);
  Brain.Screen.newLine();
  Brain.Screen.print("Leaving Auton");
  leftMotor1.spin(forward,0,pct);
  rightMotor1.spin(forward,0,pct);
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

void usercontrol(void) 
{
  while (1) 
  {
    leftMotor1.spin(fwd, Controller1.Axis3.value(), pct);
    rightMotor1.spin(fwd, Controller1.Axis2.value(), pct);
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
