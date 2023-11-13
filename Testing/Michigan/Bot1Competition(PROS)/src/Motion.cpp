#include "Motion.h"

//variables for pid
// double kP = 0.1775, kI = 0, kD = 0.01775;
double kP = 0.07, kI = 0.00013, kD = 0.0125;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

//variables for the auton task
/*static*/ bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
/*static*/ bool resetPID = true, resetTurning = true, resetFlywheel = true;
/*static*/ bool isReloading = false;
/*static*/ double setPID = 0, setTurning = 0, setPIDLeft = 0, setPIDRight = 0, reloadTime = 0;

//moves the bot straight, d is the distance in inches, this program runs on the main thread
void MoveBot(double d) {
  setPID = d; //tell the pid loop the new destination
  resetPID = true; //tell the pid to reset
  isPID = true; //tell the thread to turn on the pid
  if (d < 0) { d*= -1; } //now d is used to cacluate the wait time, so we make sure it is positive
  // wait(CalculateWaitTimeMove(d),sec); //the main thread now waits while the other runs the pid until the pid should be done
  delay(CalculateWaitTimeMove(d)*1000); //the main thread now waits while the other runs the pid until the pid should be done
  setPID = 0; //set the movement to turn off in the pid
  delay(20); //wait for good measure
  isPID = false; //turn off the pid loop on the other thread
}

//rotate the bot, d is the degrees of the rotation
void RotateBot(double d) {
  setTurning = d; //tell the pid loop the new destination
  resetTurning = true; //tell the pid to reset
  isTurning = true; //tell the turning pid loop to turn on on the other thread
  if (d < 0) { d*= -1; } //calculate wait time using d
  // wait(CalculateWaitTimeRotate(d), sec); //and then wait that much time
  delay(CalculateWaitTimeRotate(d)*1000); //and then wait that much time
  setTurning = 0; //after waiting, turn movement off
  delay(20); //wait a sec
  isTurning = false; //turn off the turning movement
}

//emptys the bot of the current ball
void ShootDiscs(double waitTime) {
  SpinMotors(0);
  reloadTime = 0;
  isReloading = true;
  delay(waitTime);
} 

//the distance is in revolutions, the encoders should only be reset on first use
void runPID(double pidSetDegrees, bool resetEncoders, bool isTurning) {
  if (resetEncoders) {
    resetEncoders = false;
    ResetEncoders();
    integral = 0;
    derivative = 0;
  }

  if (pidSetDegrees != 0) {
    lSensor = (lMotor1.get_position() + lMotor2.get_position() + 
      lMotor3.get_position()) / 3; // + lMotor4.get_position()) / 4;
    rSensor = (rMotor1.get_position() + rMotor2.get_position() + 
      rMotor3.get_position()) / 3; // + rMotor4.get_position()) / 4;
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
  //this will run for the entirety of the auton, being the secondary thread that runs in parallel with the main on
  while(isAuton) {
    //checks if the PID routine should be running using variables set in the main thread
    if (isPID) {
      //if the program is just now setting PID, it will run a first time setup, otherwise just keeps looping the same thing
      if (resetPID) {
        // setPID = ConvertInchesToRevolutions(setPID, 1.13);
        setPID = ConvertInchesToRevolutions(setPID, 0.5);
        runPID(setPID, true);
        resetPID = false;
      }
      else {runPID(setPID);}
    }

    //checks if the PID Turning routine should be running using variables set in the main thread
    if (isTurning) {
      //if the program is just now setting PID, it will run a first time setup, otherwise just keeps looping the same thing
      if (resetTurning) {
        // setTurning = ConvertDegreesToInches(setTurning, 13);
        // setTurning = ConvertInchesToRevolutions(setTurning, 1.13);
        setTurning = ConvertDegreesToInches(setTurning, 10.4);
        setTurning = ConvertInchesToRevolutions(setTurning, 0.5);
        runPID(setTurning, true, true);
        resetTurning = false;
      }
      else {runPID(setTurning, false, true);}
    }

    /* commented out until catapult is confirmed to be working
    // without the use of a limit switch. a little bit buggy without it, hoping we get a working limit switch and can use that
    if (isReloading) {
      if (reloadTime > 3120) {
        cataMotor.spin(forward, 0, pct);
        isReloading = false;
      }
      else {
        reloadTime += 10;
        cataMotor.spin(forward, 100, pct);
      }
    } */

    delay(10);
  }
  return 1;
}