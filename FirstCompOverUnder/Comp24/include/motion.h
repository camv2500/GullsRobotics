#include "robot-config.h"
#include "vex.h"
#include "Conversions.h"
#include "RobotFunctions.h"
#include <math.h>

//variables for pid //kI = 0.00013, kD =.0125
double kP = 0.029, kI = 0.0, kD = 0.005;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

//variables for the auton task
static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
static bool resetPID = true, resetTurning = true, resetFlywheel = true;
static bool isReloading = false;
static double setPID = 0, setTurning = 0, setPIDLeft = 0, setPIDRight = 0, reloadTime = 0;

//moves the bot straight, d is the distance in inches, this program runs on the main thread
void MoveBot(double d) {
  setPID = d; //tell the pid loop the new destination
  resetPID = true; //tell the pid to reset
  isPID = true; //tell the thread to turn on the pid
  if (d < 0) { d*= -1; } //now d is used to cacluate the wait time, so we make sure it is positive
  wait(CalculateWaitTimeMove(d),sec); //the main thread now waits while the other runs the pid until the pid should be done
  setPID = 0; //set the movement to turn off in the pid
  wait(20,msec); //wait for good measure
  isPID = false; //turn off the pid loop on the other thread
}

//rotate the bot, d is the degrees of the rotation
void RotateBot(double d) {
  setTurning = d; //tell the pid loop the new destination
  resetTurning = true; //tell the pid to reset
  isTurning = true; //tell the turning pid loop to turn on on the other thread
  if (d < 0) { d*= -1; } //calculate wait time using d
  wait(CalculateWaitTimeRotate(d), sec); //and then wait that much time
  setTurning = 0; //after waiting, turn movement off
  wait(20,msec); //wait a sec
  isTurning = false; //turn off the turning movement
}

//emptys the bot of the current ball
void ShootDiscs(double waitTime = 0) {
  SpinMotors(0);
  cataMotor.spinFor(fwd,120,deg);
  wait(waitTime, msec);
  reloadTime = 0;
  isReloading = true;
} 

//the distance is in revolutions, the encoders should only be reset on first use
void runPID(double pidSetDegrees, bool resetEncoders = false, bool isTurning = false) {
  if (resetEncoders) {
    resetEncoders = false;
    ResetEncoders();
    integral = 0;
    derivative = 0;
  }

  if (pidSetDegrees != 0) {
    lSensor = (lMotor1.position(degrees) + lMotor2.position(degrees) + 
      lMotor3.position(degrees) + lMotor4.position(degrees) / 4);
    rSensor = (rMotor1.position(degrees) + rMotor2.position(degrees) + 
      rMotor3.position(degrees) + rMotor4.position(degrees) / 4);
    if (isTurning) {sensorValue = rSensor;}
    else {sensorValue = (lSensor + rSensor) / 2;}
    error = pidSetDegrees - sensorValue;

    integral = integral + error;
    if (fabs(integral) > 5000) {integral = 5000;}

    derivative = error - prevError;
    prevError = error;

    power = (error * kP) + (integral * kI) + (derivative * kD);
    if (power > 70) {power = 70;}
    if (power < -70) {power = -70;}
  
    if (isTurning) {SpinMotors(power, true);}
    else {SpinMotors(power);}
  }
  else {
    SpinMotors(0);
  }
}

//auton controller
int autonController() {
  //this will run for the entirety of the auton, being the secondary thread that runs in parallel with the main on
  while(isAuton) {
    //checks if the PID routine should be running using variables set in the main thread
    if (isPID) {
      //if the program is just now setting PID, it will run a first time setup, otherwise just keeps looping the same thing
      if (resetPID) {
        setPID = ConvertInchesToRevolutions(setPID, 0.36);
        runPID(setPID, true);
        resetPID = false;
      }
      else {runPID(setPID);}
    }

    //checks if the PID Turning routine should be running using variables set in the main thread
    if (isTurning) {
      //if the program is just now setting PID, it will run a first time setup, otherwise just keeps looping the same thing
      if (resetTurning) {
        setTurning = ConvertDegreesToInches(setTurning, 12);
        setTurning = ConvertInchesToRevolutions(setTurning, 0.36);
        runPID(setTurning, true, true);
        resetTurning = false;
      }
      else {runPID(setTurning, false, true);}
    }

    //NEEDS WORK
    if (isReloading) {
      if (cataLimit.pressing()) {
        cataMotor.spin(forward, 0, pct);
        isReloading = false;
      }
      else {
        cataMotor.spin(forward, 75, pct);
      }
    }

   wait(5, msec);
  }
  return 1;
}

int userController() {
  while(isUser) {
    //calculate the power for the left and right side independently using two joysticks (tank control)
    double leftDrive = (Controller1.Axis3.value());
    double rightDrive = (Controller1.Axis2.value());

    //calculate the power for the left and right side independently using one joystick (arcade control)
    //double leftDrive = (Controller1.Axis2.value() - Controller1.Axis1.value());
    //double rightDrive = (Controller1.Axis2.value() + Controller1.Axis1.value());

    lMotor1.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor2.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor3.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor4.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    rMotor1.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor2.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor3.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor4.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);

    if (Controller1.ButtonX.pressing()) {
      cataMotor.spinFor(fwd,45,deg);
      setButtonXPressed();
    } 

    // ShootBallAuto();

    if (Controller1.ButtonX.pressing() && cataLimit.pressing()) {
      cataMotor.spin(fwd,40,pct);
    }
    else if (cataLimit.pressing()) {
      cataMotor.stop(brakeType::hold);
    }
    else {
      cataMotor.spin(fwd,40,pct);
    }

    if(Controller1.ButtonR1.pressing()) {
      IntakeBalls(true, 100);
    }
    else if (Controller1.ButtonR2.pressing()){
      IntakeBalls(true, -100);
    }
    else {
      IntakeBalls(false);
    }

    wait(10,msec);
  }

  return 1;
}