#include "robot-config.h"
#include "vex.h"

//spin the motors for pid
void SpinMotors(double power, bool isTurning = false) {
  if(isTurning) {
    lMotor1.spin(reverse, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(reverse, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(reverse, power, pct); rMotor3.spin(forward, power, pct);
    lMotor4.spin(reverse, power, pct); rMotor4.spin(forward, power, pct);
  }
  else {
    lMotor1.spin(forward, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(forward, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(forward, power, pct); rMotor3.spin(forward, power, pct);
    lMotor4.spin(forward, power, pct); rMotor4.spin(forward, power, pct);
  }
}

//convert degrees to inches
double ConvertDegreesToInches(double setDegrees) {
  double turnDiameter = 12.17;
  double requiredInches = setDegrees / 360 * M_PI * turnDiameter;
  return requiredInches;
}

//convert the inches to revolutions
double ConvertInchesToRevolutions(double requiredInches) {
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;
  return requiredRevolutions;
}

//variables for pid
double kP = 0.088, kI = 0, kD = 0;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

//the distance is in revolutions, the encoders should only be reset on first use
void runPID(double pidSetDegrees, bool resetEncoders = false, bool isTurning = false) {
  if (resetEncoders) {
    resetEncoders = false;
    lMotor1.setPosition(0, degrees); lMotor2.setPosition(0, degrees); lMotor3.setPosition(0, degrees); lMotor4.setPosition(0, degrees);
    rMotor1.setPosition(0, degrees); rMotor2.setPosition(0, degrees); rMotor3.setPosition(0, degrees); rMotor4.setPosition(0, degrees);
    integral = 0;
    derivative = 0;
  }

  lSensor = (lMotor1.position(degrees) + lMotor2.position(degrees) + 
    lMotor3.position(degrees) + lMotor4.position(degrees)) / 4;
  rSensor = (rMotor1.position(degrees) + rMotor2.position(degrees) + 
    rMotor3.position(degrees) + rMotor4.position(degrees)) / 4;
  if (isTurning) {sensorValue = rSensor;}
  else {sensorValue = (lSensor + rSensor) / 2;}
  error = pidSetDegrees - sensorValue;

  integral = integral + error;
  if (fabs(integral) > 5000) {integral = 500;}

  derivative = error - prevError;
  prevError = error;

  power = error * kP + integral * kI + derivative * kD;
  
  if (isTurning) {SpinMotors(power, true);}
  else {SpinMotors(power);}
}

//variables for the flywheel
double fkP = 0.000000, fkI = 0, fkD = 0.000000, fkF = 0.023;
double flyWheelError = 0, fprevError = 0, fintegral = 0, fderivative = 0, fpower = 0;
double kF, feedForward, count = 1;

//run the flywheel
void runFlywheel(double flywheelSetRPM = 0, bool resetFlywheelEncoders = false) {
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
    /*
    if (flyWheelError < 5 && count > 4) {Controller1.rumble(rumbleLong); count = 1;}
    else {
      if (count > 4) {Controller1.rumble(" ");}
      else {count++;}
    }
    */
  }
  else {
    FlyWheel1.stop(brakeType::coast);
    FlyWheel2.stop(brakeType::coast);
  }
}

//variables for the auton task
static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
static bool resetPID = true, resetTurning = true, resetFlywheel = true;
static double setPID = 0, setTurning = 0, setFlywheel = 0;

//auton controller
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
      else {
        runFlywheel(setFlywheel);
      }
    }

    wait(10, msec);
  }
  return 1;
}

//auton variables
double goalAngle, requiredAngle, currentAngle, requiredDistance, x_c, y_c, x_s = 0, y_s = 0;

//odometry function
void GoToPoint(double x_g, double y_g, bool isReversing = false) {
  //calculate distance  
  x_c = x_g - x_s;
  y_c = y_g - y_s;
  requiredDistance = sqrt((x_c * x_c) + (y_c * y_c));

  //calculate required rotation if any
  goalAngle = asin(x_c / requiredDistance) * 57.2958;
  requiredAngle = goalAngle - currentAngle;

  //if angle is more than 2 degrees, turns the robot
  if (fabs(requiredAngle) > 2 && !isReversing) {
    setTurning = requiredAngle;
    isTurning = true;
    wait(4000, msec);
    isTurning = false;
    currentAngle = requiredAngle;
  }
  if (isReversing) {
    requiredDistance *= -1;
  }

  //moves the required distance
  setPID = requiredDistance;
  isPID = true;
  wait(4000,msec);
  isPID = false;
  x_s += x_c;
  y_s += y_c;

  //show the current location and rotation based off starting rotation
  Brain.Screen.print(x_s);
  Brain.Screen.print(" , ");
  Brain.Screen.print(y_s);
  Brain.Screen.print(" , ");
  Brain.Screen.print(currentAngle);
  Brain.Screen.newLine();
}

static bool isUserFlywheel = false, resetUserFlywheel = false;
static double setUserFlywheel = 0, indexerCount = 0;

void ToggleFlywheelOn(double speed = 450) {
  resetUserFlywheel = true;
  if (speed == 450) {
    setUserFlywheel = 532;
    //fkF = 0.0253;
  }
  isUserFlywheel = true;
}

void ToggleFlywheelOff() {
  isUserFlywheel = false;
  resetUserFlywheel = true;
  setUserFlywheel = 0;
  isUserFlywheel = false;
}

int userController() {
  while(isUser) {
    if (isUserFlywheel) {
      if (resetUserFlywheel) {
        runFlywheel(setUserFlywheel, true);
        resetUserFlywheel = false;
        Brain.Screen.print(FlyWheel1.velocity(rpm));
        Brain.Screen.newLine();
      }
      else {
        runFlywheel(setUserFlywheel);
        Brain.Screen.print(FlyWheel1.velocity(rpm));
        Brain.Screen.newLine();
      }
    }
    
    if(abs(Controller1.Axis2.value()+Controller1.Axis1.value()) < 50 || abs(Controller1.Axis2.value()-Controller1.Axis1.value()) < 50) { 
      lMotor1.spin(fwd, ((Controller1.Axis2.value() - Controller1.Axis1.value())/2), vex::velocityUnits::pct);
      lMotor2.spin(fwd, ((Controller1.Axis2.value() - Controller1.Axis1.value())/2), vex::velocityUnits::pct);
      lMotor3.spin(fwd, ((Controller1.Axis2.value() - Controller1.Axis1.value())/2), vex::velocityUnits::pct);
      lMotor4.spin(fwd, ((Controller1.Axis2.value() - Controller1.Axis1.value())/2), vex::velocityUnits::pct);
      rMotor1.spin(fwd, ((Controller1.Axis2.value() + Controller1.Axis1.value())/2), vex::velocityUnits::pct);
      rMotor2.spin(fwd, ((Controller1.Axis2.value() + Controller1.Axis1.value())/2), vex::velocityUnits::pct);
      rMotor3.spin(fwd, ((Controller1.Axis2.value() + Controller1.Axis1.value())/2), vex::velocityUnits::pct);
      rMotor4.spin(fwd, ((Controller1.Axis2.value() + Controller1.Axis1.value())/2), vex::velocityUnits::pct);
    }
    else {
      lMotor1.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);
      lMotor2.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);
      lMotor3.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);
      lMotor4.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()), vex::velocityUnits::pct);
      rMotor1.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
      rMotor2.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
      rMotor3.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
      rMotor4.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()), vex::velocityUnits::pct);
    }
    //intake control
    if(Controller1.ButtonL2.pressing()) {
      magLifter.set(true);
      indexer1.set(false);
      intakeMotor.spin(fwd, 100, pct);
    }
    else if (Controller1.ButtonRight.pressing()) {
      intakeMotor.spin(reverse, 100, pct);
    }
    else {
      intakeMotor.stop(brakeType::coast);
    }

    //roller control
    if(Controller1.ButtonL1.pressing()) {
      rollerMotor.spin(reverse, 50, pct);
    }
    else if(Controller1.ButtonLeft.pressing()) {
      rollerMotor.spin(fwd, 80, pct);
    }
    else {
      rollerMotor.stop(brakeType::hold);
    }

    //flywheel controller
    if(Controller1.ButtonR1.pressing()) {
      magLifter.set(false);
      ToggleFlywheelOn();
      //FlyWheel1.spin(fwd,100,pct);
      //FlyWheel2.spin(fwd,100,pct);
      if (Controller1.ButtonR2.pressing()) {
        indexer1.set(true);
      }
      else {
        indexer1.set(false);
      }
    }
    else {
      ToggleFlywheelOff();
      //FlyWheel1.stop(brakeType::coast);
      //FlyWheel2.stop(brakeType::coast);
      indexer1.set(false);
    }

    if (Controller1.ButtonX.pressing()) {
      FlyWheel1.spin(fwd, 80, pct);
      FlyWheel2.spin(fwd,80,pct);
    }
    else if (!Controller1.ButtonX.pressing() && !Controller1.ButtonR1.pressing()) {
      FlyWheel1.stop(brakeType::coast);
      FlyWheel2.stop(brakeType::coast);
    }

    //endgame deploy
    if (Controller1.ButtonY.pressing()) {
      endGame.set(true);
    }
    else {
      endGame.set(false);
    }

    wait(10,msec);
  }

  return 1;
}
