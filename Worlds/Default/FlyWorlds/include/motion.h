#include "robot-config.h"
#include "vex.h"
#include <math.h>

//variables for pid
double kP = 0.468, kI = 0.0000468, kD = 0.048;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

//variables for the flywheel
double fkP = 0.008, fkI = 0, fkD = 0.008, fkF = 0.02;
double flyWheelError = 0, fprevError = 0, fintegral = 0, fderivative = 0, fpower = 0;
double kF, feedForward, count = 1;

//variables for the odometry
double xSelf = 0, ySelf = 0, tSelf = 0, xCurrent = 0, yCurrent = 0;
double goalAngle, requiredAngle, requiredDistance;
double changeAngle, changeX, changeY;

//variables for the auton task
static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
static bool resetPID = true, resetTurning = true, resetFlywheel = true, isAutonFlywheel = false;
static double setPID = 0, setTurning = 0, setFlywheel = 0;

//user variables
static bool isUserFlywheel = false, resetUserFlywheel = false, isForwardForward = true;
static double setUserFlywheel = 0, indexerCount = 0;

//convert degrees to inches
double ConvertDegreesToInches(double setDegrees, double turnDiameter = 12.17) {
  double requiredInches = setDegrees / 360.0 * M_PI * turnDiameter;
  return requiredInches;
}

//convert the inches to revolutions
double ConvertInchesToRevolutions(double requiredInches) {
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;
  return requiredRevolutions;
}

//convert radians to degrees
double ConvertRadiansToDegrees(double radian) {
  radian = radian * (180.0 / M_PI);
  return radian;
}

double CalculateWaitTimeMove(double n) {
  n = 0.05 * n; n += 1.25; return n;
}

double CalculateWaitTimeRotate(double n) {
  n = 0.005 * n; n += 1.25; return n;
}

//reset all the encoders
void ResetEncoders() {
  lMotor1.setPosition(0,degrees); lMotor2.setPosition(0,degrees);
  lMotor3.setPosition(0,degrees);
  rMotor1.setPosition(0,degrees); rMotor2.setPosition(0,degrees);
  rMotor3.setPosition(0,degrees);
}

//spin the motors for pid
void SpinMotors(double power, bool isTurning = false) {
  if(isTurning) {
    lMotor1.spin(reverse, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(reverse, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(reverse, power, pct); rMotor3.spin(forward, power, pct);
  }
  else {
    lMotor1.spin(forward, power, pct); rMotor1.spin(forward, power, pct);
    lMotor2.spin(forward, power, pct); rMotor2.spin(forward, power, pct);
    lMotor3.spin(forward, power, pct); rMotor3.spin(forward, power, pct);
  }
}

//spins the rollers
void SpinRoller(double t = 200) {
  rollerMotor.spin(reverse,80,pct);
  wait(t,msec); //replace with color sensor
  rollerMotor.spin(fwd,0,pct);
}

//moves the bot straight
void MoveBot(double d) {
  setPID = d;
  if (d < 0) { d = d * -1;}
  resetPID = true;
  isPID = true;
  wait(CalculateWaitTimeMove(d),sec);
  setPID = 0;
  wait(20,msec);
  isPID = false;
}

//rotate the bot
void RotateBot(double d) {
  setTurning = d;
  resetTurning = true;
  isTurning = true;
  wait(CalculateWaitTimeRotate(d),sec);
  isTurning = false;
  wait(20,msec);
}

//lets the bot intake discs
void IntakeDiscs(bool turnOff = false) {
  if(isAutonFlywheel) {
    isAutonFlywheel = false;
  }
  if(turnOff) {
    intakeMotor.spin(fwd,0,pct);
    intakeMotor2.spin(fwd,0,pct);
  }
  else {
    intakeMotor.spin(fwd,100,pct);
    intakeMotor2.spin(fwd,100,pct);
  }
}

//emptys the bot of all discs
void ShootDiscs(double a = 1, double s = 600) {
  SpinMotors(0);
  if (!isAutonFlywheel) {
    isAutonFlywheel = true;
  }
  setFlywheel = s;
  resetFlywheel = true;
  isFlywheel = true;
  wait(2000,msec);
  indexer1.set(true);
  wait(600,msec);
  indexer1.set(false);
  if (a > 1) {
    wait(2000,msec);
    indexer1.set(true);
    wait(600,msec);
    indexer1.set(false);
  }
  if (a > 2) {
    wait(2000,msec);
    indexer1.set(true);
    wait(600,msec);
    indexer1.set(false);
  }
  setFlywheel = 0;
  wait(20,msec);
  isFlywheel = false;
}

//auton endgame deployment
void EndgameDeploy() {
  endGame.set(true); wait(500,msec);
  endGame.set(false); wait(500,msec);
  endGame.set(true); wait(500,msec);
  endGame.set(false); wait(500,msec);
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
      lMotor3.position(degrees)) / 3;
    rSensor = (rMotor1.position(degrees) + rMotor2.position(degrees) + 
      rMotor3.position(degrees)) / 3;
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

//run the flywheel
void runFlywheel(double flywheelSetRPM = 0, bool resetFlywheelEncoders = false) {
  if (resetFlywheelEncoders) {
    resetFlywheelEncoders = false;
    fintegral = 0;
    fderivative = 0;
    feedForward = flywheelSetRPM; 
  }

  if (flywheelSetRPM != 0) {
    flyWheelError = flywheelSetRPM - FlywheelMotor.velocity(rpm);

    fintegral = fintegral + flyWheelError;
    //if (fabs(fintegral) > 12000) {fintegral = 12000;}

    fderivative = flyWheelError - fprevError;
    fprevError = flyWheelError;

    fpower = flyWheelError * fkP + fintegral * fkI + fderivative * fkD + feedForward * fkF;
    if (fpower > (flywheelSetRPM / 600 * 12)) {
      fpower = flywheelSetRPM / 600 * 12;
    }

    FlywheelMotor.spin(forward, fpower, volt);
    /*
    if (flyWheelError < 5 && count > 4) {Controller1.rumble(rumbleLong); count = 1;}
    else {
      if (count > 4) {Controller1.rumble(" ");}
      else {count++;}
    }
    */
  }
  else {
    FlywheelMotor.stop(brakeType::coast);
  }
}

void GoToPoint2(double x, double y) {
  //calculate the distance the bot will have to travel
  changeX = x - xSelf;
  changeY = y - ySelf;
  requiredDistance = sqrt((changeX * changeX) + (changeY * changeY));

  //calculate the goal angle
  goalAngle = asin(changeX / requiredDistance);
  if (goalAngle < 0) { goalAngle *= -1; }

  //change the quadrant to which one is needed based on the change of x and the change of y
  //if it lands on an axis it just changes the goal angle to that axis degree (in radians) 
  if (changeX == 0 && changeY > 0) {goalAngle = 0;}
  else if (changeX > 0 && changeY == 0) { goalAngle = 1.5708; }
  else if (changeX == 0 && changeY < 0) { goalAngle = 3.14159; }
  else if (changeX < 0 && changeY == 0) { goalAngle = 4.71239; }
  else if (changeX > 0 && changeY < 0) { goalAngle += 1.5708; }
  else if (changeX < 0 && changeY < 0) { goalAngle += 3.14159; }
  else if (changeX < 0 && changeY > 0) { goalAngle += 4.71239; }

  //calculates how far the bot actually needs to spin, if it is more than 180 it moves the opposite way
  requiredAngle = goalAngle - tSelf;
  if (requiredAngle > 180) { requiredAngle = (360 - requiredAngle) * -1; }

  //rotate the bot then move the bot
  RotateBot(ConvertRadiansToDegrees(requiredAngle));
  MoveBot(requiredDistance);

  //update where the bot is
  xSelf = x;
  ySelf = y;
  tSelf = goalAngle;

  //print out where the robot should be on the screen
  Brain.Screen.print(xSelf);
  Brain.Screen.print(" , ");
  Brain.Screen.print(ySelf);
  Brain.Screen.print(" , ");
  Brain.Screen.print(ConvertRadiansToDegrees(tSelf));
  Brain.Screen.newLine();
}

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
        setTurning = ConvertDegreesToInches(setTurning, 13.65);
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

void ToggleFlywheelOn(double speed = 450) {
  resetUserFlywheel = true;
  setUserFlywheel = speed;
  isUserFlywheel = true;
}

void ToggleFlywheelOff() {
  isUserFlywheel = false;
  resetUserFlywheel = true;
  setUserFlywheel = 0;
  isUserFlywheel = false;
}

void ToggleForward() {
  if (isForwardForward) { isForwardForward = false; }
  else { isForwardForward = true; }
}

double controlCurve(double controllerPos){
  //Slow curve
  return (exp(-14.6/10)+exp((fabs(controllerPos)-100)/10)*(1-exp(-14.6/10)))*controllerPos;
}

int userController() {
  while(isUser) {
    if (isUserFlywheel) {
      if (resetUserFlywheel) {
        runFlywheel(setUserFlywheel, true);
        resetUserFlywheel = false;
      }
      else {
        runFlywheel(setUserFlywheel);
      }
    }
    
    if (isForwardForward) {
      double leftDrive = (Controller1.Axis2.value() + Controller1.Axis1.value());
      double rightDrive = (Controller1.Axis2.value() - Controller1.Axis1.value());

      lMotor1.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
      lMotor2.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
      lMotor3.spin(fwd, controlCurve(leftDrive), vex::velocityUnits::pct);
      rMotor1.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
      rMotor2.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
      rMotor3.spin(fwd, controlCurve(rightDrive), vex::velocityUnits::pct);
    }
    else {
      double leftDrive = (Controller1.Axis2.value() - Controller1.Axis1.value());
      double rightDrive = (Controller1.Axis2.value() + Controller1.Axis1.value());

      lMotor1.spin(reverse, controlCurve(leftDrive), vex::velocityUnits::pct);
      lMotor2.spin(reverse, controlCurve(leftDrive), vex::velocityUnits::pct);
      lMotor3.spin(reverse, controlCurve(leftDrive), vex::velocityUnits::pct);
      rMotor1.spin(reverse, controlCurve(rightDrive), vex::velocityUnits::pct);
      rMotor2.spin(reverse, controlCurve(rightDrive), vex::velocityUnits::pct);
      rMotor3.spin(reverse, controlCurve(rightDrive), vex::velocityUnits::pct);
    }

    //intake control
    if(Controller1.ButtonL2.pressing()) {
      indexer1.set(false);
      intakeMotor.spin(fwd, 100, pct);
      intakeMotor2.spin(fwd,100,pct);
    }
    else if (Controller1.ButtonRight.pressing()) {
      intakeMotor.spin(reverse, 100, pct);
      intakeMotor2.spin(reverse,100,pct);
    }
    else {
      intakeMotor.stop(brakeType::coast);
      intakeMotor2.stop(brakeType::coast);
    }

    //roller control
    if(Controller1.ButtonL1.pressing()) {
      rollerMotor.spin(reverse, 100, pct);
    }
    else if(Controller1.ButtonLeft.pressing()) {
      rollerMotor.spin(fwd, 100, pct);
    }
    else {
      rollerMotor.stop(brakeType::hold);
    }

    //flywheel controller
    if(Controller1.ButtonR1.pressing()) {
      ToggleFlywheelOn(540);
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
      FlywheelMotor.spin(fwd, 80, pct);
    }
    else if (!Controller1.ButtonX.pressing() && !Controller1.ButtonR1.pressing()) {
      FlywheelMotor.stop(brakeType::coast);
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