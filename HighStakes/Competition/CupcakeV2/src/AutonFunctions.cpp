#include "robot-config.h"
#include "AutonFunctions.h"
#include "DriverControl.h"
#include "pros/motors.hpp"
#include "pros/misc.hpp"

// NOTE: The robot now moves and stops at the correct position.
// HOWEVER: The while loop does not break and continues to move a very small distance
// THE ERROR IS PROBABLY ON LINES 88 or 112

/////////////////////////////////////////////////////////////////////////////////////
//////                              GLOBAL CONSTANTS                           //////
/////////////////////////////////////////////////////////////////////////////////////

//variables for pid
double kP = 0.029, kI = 0.0, kD = 0.009;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

/////////////////////////////////////////////////////////////////////////////////////
//////                               GLOBAL VARIABLES                          //////
/////////////////////////////////////////////////////////////////////////////////////

//variables for the auton task
bool isAuton = false, isPID = false, isTurning = false, isUser = false, isIntaking = false; 
bool resetPID = true, resetTurning = true;
double setPID = 0, setTurning = 0, setPIDLeft = 0, setPIDRight = 0;
double movePower = 127, turnPower = 127;

/////////////////////////////////////////////////////////////////////////////////////
//////                               OTHER VARIABLES                           //////
/////////////////////////////////////////////////////////////////////////////////////

// Other Variables

/////////////////////////////////////////////////////////////////////////////////////
//////                                 FUNCTIONS                               //////
/////////////////////////////////////////////////////////////////////////////////////

//reset all the encoders
void ResetEncoders() {
    front_left_wheels.tare_position();
    middle_left_wheels.tare_position();
    back_left_wheels.tare_position();
    top_front_left_wheels.tare_position();
    top_back_left_wheels.tare_position();

    front_right_wheels.tare_position();
    middle_right_wheels.tare_position();
    back_right_wheels.tare_position();
    top_front_right_wheels.tare_position();
    top_back_right_wheels.tare_position();
  }
  
  //spin the motors for pid
  void SpinMotors(double power, bool isTurning) {
    power = -power;
    if(isTurning) {
      // left side 
      front_left_wheels.move(-power);
      middle_left_wheels.move(-power);
      back_left_wheels.move(-power);
      top_front_left_wheels.move(-power);
      top_back_left_wheels.move(-power);

      // right side
      front_right_wheels.move(power);
      middle_right_wheels.move(power);
      back_right_wheels.move(power);
      top_front_right_wheels.move(power);
      top_back_right_wheels.move(power);
    }
    else {
      // left side 
      front_left_wheels.move(power);
      middle_left_wheels.move(power);
      back_left_wheels.move(power);
      top_front_left_wheels.move(power);
      top_back_left_wheels.move(power);

      // right side
      front_right_wheels.move(power);
      middle_right_wheels.move(power);
      back_right_wheels.move(power);
      top_front_right_wheels.move(power);
      top_back_right_wheels.move(power);
    }
  }

//moves the bot straight, d is the distance in inches, this program runs on the main thread
void MoveBot(double d, double p) {
    setPID = d; //tell the pid loop the new destination
    movePower = p;
    resetPID = true; //tell the pid to reset
    isPID = true; //tell the thread to turn on the pid
    if (d < 0) { d*= -1; } //now d is used to cacluate the wait time, so we make sure it is positive
    delay(CalculateWaitTimeMove(d)); //the main thread now waits while the other runs the pid until the pid should be done
    setPID = 0; //set the movement to turn off in the pid
    delay(20); //wait for good measure
    isPID = false; //turn off the pid loop on the other thread
  }
  
  //rotate the bot, d is the degrees of the rotation
  void RotateBot(double d, double p) {
    setTurning = d; //tell the pid loop the new destination
    turnPower = p;
    resetTurning = true; //tell the pid to reset
    isTurning = true; //tell the turning pid loop to turn on on the other thread
    if (d < 0) { d*= -1; } //calculate wait time using d
    delay(CalculateWaitTimeRotate(d)); //and then wait that much time
    setTurning = 0; //after waiting, turn movement off
    delay(20); //wait a sec
    isTurning = false; //turn off the turning movement
  }
  
//   void intake(double p = 100) {
//     IntakeBalls(true, p);
//     isIntaking = true;
//     }
  
  //the distance is in revolutions, the encoders should only be reset on first use
  void runPID(double pidSetDegrees, bool resetEncoders, bool isTurning) {
    if (resetEncoders) {
      resetEncoders = false;
      ResetEncoders();
      integral = 0;
      derivative = 0;
    }
  
    if (pidSetDegrees != 0) {
      lSensor = (front_left_wheels.get_position() + middle_left_wheels.get_position() + 
        back_left_wheels.get_position() / 3);
      rSensor = (front_right_wheels.get_position() + middle_right_wheels.get_position() + 
      back_right_wheels.get_position() / 3);
      if (isTurning) {sensorValue = rSensor;}
      else {sensorValue = (lSensor + rSensor) / 2;}
      error = pidSetDegrees - sensorValue;
  
      integral = integral + error;
      if (fabs(integral) > 5000) {integral = 5000;}
  
      derivative = error - prevError;
      prevError = error;
  
      power = (error * kP) + (integral * kI) + (derivative * kD);
      if (isTurning) {
        if (power > turnPower) {power = turnPower;}
        if (power < -turnPower) {power = -turnPower;}
      }
      else {
        if (power > movePower) {power = movePower;}
        if (power < -movePower) {power = -movePower;}
      }
    
      if (isTurning) {SpinMotors(power, true);}
      else {SpinMotors(power);}
    }
    else {
      SpinMotors(0);
    }
  }

/////////////////////////////////////////////////////////////////////////////////////
//////                               CONVERSIONS                               //////
/////////////////////////////////////////////////////////////////////////////////////

//convert degrees to inches
double ConvertDegreesToInches(double setDegrees, double turnDiameter) {
    double requiredInches = setDegrees / 360.0 * M_PI * turnDiameter;
    return requiredInches;
}

//convert the inches to revolutions
double ConvertInchesToRevolutions(double requiredInches, double circum) {
    double circumferenceOfWheel = circum * M_PI;
    double outputRat = 3.0/5.0;
    double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;
    return requiredRevolutions;
}

//convert radians to degrees
double ConvertRadiansToDegrees(double radian) {
    radian = radian * (180.0 / M_PI);
    return radian;
}

//formula for how long of a wait between movements
double CalculateWaitTimeMove(double n) {
    n = 0.05 * n; n += 0.25; return n*1000;
}

//formula for how long of a wait between rotations to enable quick speed but ensure completion of task
double CalculateWaitTimeRotate(double n) {
    n = 0.005 * n; n += 0.35; return n*1000;
}

double controlCurve(double controllerPos) {
    //Slow curve
    return (exp(-14.6/10)+exp((fabs(controllerPos)-100)/10)*(1-exp(-14.6/10)))*controllerPos;
}