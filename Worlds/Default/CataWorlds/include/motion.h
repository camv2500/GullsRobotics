#include "robot-config.h"
#include "vex.h"
#include <math.h>

//variables for pid
double kP = 0.1775, kI = 0, kD = 0.01775;
double error = 0, prevError = 0, integral = 0, derivative = 0;
double power = 0, sensorValue = 0, lSensor = 0, rSensor = 0;

//variables for the odometry
double xSelf = 0, ySelf = 0, tSelf = 0, xCurrent = 0, yCurrent = 0;
double goalAngle, requiredAngle, requiredDistance;
double changeAngle, changeX, changeY;

//variables for the auton task
static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
static bool resetPID = true, resetTurning = true, resetFlywheel = true;
static bool isReloading = false;
static double setPID = 0, setTurning = 0, setPIDLeft = 0, setPIDRight = 0, reloadTime = 0;

//convert degrees to inches
double ConvertDegreesToInches(double setDegrees, double turnDiameter = 12.17) {
  double requiredInches = setDegrees / 360.0 * M_PI * turnDiameter;
  return requiredInches;
}

//convert the inches to revolutions
double ConvertInchesToRevolutions(double requiredInches, double circum = 3.86) {
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

double CalculateWaitTimeMove(double n) {
  n = 0.05 * n; n += 0.75; return n;
}

double CalculateWaitTimeRotate(double n) {
  n = 0.005 * n; n += 0.75; return n;
}

//reset all the encoders
void ResetEncoders() {
  lMotor1.setPosition(0,degrees); lMotor2.setPosition(0,degrees);
  lMotor3.setPosition(0,degrees); lMotor4.setPosition(0,degrees);
  rMotor1.setPosition(0,degrees); rMotor2.setPosition(0,degrees);
  rMotor3.setPosition(0,degrees); rMotor4.setPosition(0,degrees);
}

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

//spins the rollers
void SpinRoller(double t = 200) {
  intakeRollerMotor.spin(fwd,80,pct);
  wait(t,msec); //replace with color sensor
  intakeRollerMotor.spin(fwd,0,pct);
}

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
  isTurning = false;
  wait(20,msec);
}

//lets the bot intake discs
void IntakeDiscs(bool turnOff = false) {
  if(turnOff) {intakeRollerMotor.spin(fwd,0,pct);}
  else {intakeRollerMotor.spin(fwd,100,pct);}
}

//emptys the bot of all discs
void ShootDiscs() {
  SpinMotors(0);
  reloadTime = 0;
  isReloading = true;
  wait(1000,msec);
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

void GoToPoint2(double x, double y, double tTime = 1000, double mTime = 1000) {
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
  RotateBot(ConvertRadiansToDegrees(requiredAngle),tTime);
  MoveBot(requiredDistance,mTime);

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

double controlCurve(double controllerPos){
  //Slow curve
  return (exp(-14.6/10)+exp((fabs(controllerPos)-100)/10)*(1-exp(-14.6/10)))*controllerPos;
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
      intakeRollerMotor.spin(fwd, 70, pct);
    }
    else {
      intakeRollerMotor.stop(brakeType::coast);
    }

    // //endgame deploy
    if (Controller1.ButtonY.pressing()) {
      endGame.set(true);
    }
    else {
      endGame.set(false);
    }

    // if (Controller1.ButtonA.pressing()) {
    //   endGame.set(false);
    // }

    if (Controller1.ButtonR1.pressing()) {
      cataMotor.spin(fwd,100,pct);
    }
    else if (Controller1.ButtonR2.pressing()) {
      cataMotor.spin(fwd,40,pct);
    }
    else {
      cataMotor.spin(fwd,0,pct);
    }

    wait(10,msec);
  }

  return 1;
}