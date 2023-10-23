#include "robot-config.h"
#include "vex.h"
#include "Conversions.h"
#include "RobotFunctions.h"
#include <math.h>

//variables for pid
double kP = 0.1775, kI = 0, kD = 0.01775;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

//variables for the auton task
static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
static bool resetPID = true, resetTurning = true, resetFlywheel = true;
static bool isReloading = false;
static double setPID = 0, setTurning = 0, setPIDLeft = 0, setPIDRight = 0, reloadTime = 0;

//moves the bot straight
void MoveBot(double d, int mTime = 1000) {
  setPID = d;
  resetPID = true;
  isPID = true;
  if (d < 0) { d*= -1; }
  wait(CalculateWaitTimeMove(d),sec);
  setPID = 0;
  wait(20,msec);
  isPID = false;
}

//rotate the bot
void RotateBot(double d, int tTime = 1000) {
  setTurning = d;
  resetTurning = true;
  isTurning = true;
  if (d < 0) { d*= -1; }
  wait(CalculateWaitTimeRotate(d), sec);
  setTurning = 0;
  isTurning = false;
  wait(20,msec);
}

//emptys the bot of all discs
void ShootDiscs() {
  SpinMotors(0);
  reloadTime = 0;
  isReloading = true;
  wait(1000,msec);
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
      lMotor3.position(degrees) + lMotor4.position(degrees)) / 4;
    rSensor = (rMotor1.position(degrees) + rMotor2.position(degrees) + 
      rMotor3.position(degrees) + rMotor4.position(degrees)) / 4;
    if (isTurning) {sensorValue = rSensor;}
    else {sensorValue = (lSensor + rSensor) / 2;}
    error = pidSetDegrees - sensorValue;

    integral = integral + error;
    if (fabs(integral) > 5000) {integral = 5000;}

    derivative = error - prevError;
    prevError = error;

    power = error * kP + integral * kI + derivative * kD;
    if (power > 33.5) {power = 33.5;}
    if (power < -33.5) {power = -33.5;}
  
    if (isTurning) {SpinMotors(power, true);}
    else {SpinMotors(power);}
  }
  else {
    SpinMotors(0);
  }
}

//auton controller
int autonController() {
  while(isAuton) {
    if (isPID) {
      if (resetPID) {
        setPID = ConvertInchesToRevolutions(setPID, 1.13);
        runPID(setPID, true);
        resetPID = false;
      }
      else {runPID(setPID);}
    }

    if (isTurning) {
      if (resetTurning) {
        setTurning = ConvertDegreesToInches(setTurning, 13);
        setTurning = ConvertInchesToRevolutions(setTurning, 1.13);
        runPID(setTurning, true, true);
        resetTurning = false;
      }
      else {runPID(setTurning, false, true);}
    }

    if (isReloading) {
      if (reloadTime > 3120) {
        cataMotor.spin(forward, 0, pct);
        isReloading = false;
      }
      else {
        reloadTime += 10;
        cataMotor.spin(forward, 100, pct);
      }
    }

    wait(10, msec);
  }
  return 1;
}

int userController() {
  while(isUser) {
    double leftDrive = (Controller1.Axis2.value() - Controller1.Axis1.value());
    double rightDrive = (Controller1.Axis2.value() + Controller1.Axis1.value());

    lMotor1.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor2.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor3.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    lMotor4.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
    rMotor1.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor2.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor3.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    rMotor4.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);

    //intake control
    if(Controller1.ButtonL1.pressing()) {
      intakeRollerMotor.spin(fwd, 100, pct);
    }
    else if (Controller1.ButtonL2.pressing()) {
      intakeRollerMotor.spin(reverse, 70, pct);
    }
    else {
      intakeRollerMotor.stop(brakeType::coast);
    }

    if (Controller1.ButtonR1.pressing() && cataLimit.pressing()) {
      cataMotor.spin(fwd,100,pct);
    }
    else if (cataLimit.pressing()) {
      cataMotor.stop(brakeType::hold);
    }
    else {
      cataMotor.spin(fwd,100,pct);
    }

    wait(10,msec);
  }

  return 1;
}