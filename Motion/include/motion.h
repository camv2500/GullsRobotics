#include "robot-config.h"
#include "vex.h"



//current function for turning the robot, converts the degrees given to revolutions required and sends it to the PIDLoop
/*void turnRobot(double setDegrees) {
  //need to convert to using radians to decrease the amount of math

  //setDegrees is the amount of degrees we want to turn
  //turnDiameter is the diameter of the circle of roation that the robot establishes while spinning
  double turnDiameter = 12.0;

  //convert the setDegrees given into the amount of inches required
  double requiredInches = setDegrees / 360 * M_PI * turnDiameter;

  //convert the inches to revolutions
  double circumferenceOfWheel = 3.5 * M_PI;
  double outputRat = 3.0/5.0;
  double requiredRevolutions = (requiredInches / circumferenceOfWheel) * outputRat * 360.0;

  PIDLoop(requiredRevolutions, true);
}*/

/*
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
*/

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

double fkP = 0.000000, fkI = 0, fkD = 0.000000, fkF = 0.024;
double flyWheelError = 0, fprevError = 0, fintegral = 0, fderivative = 0, fpower = 0;
double kF, feedForward, count = 1;

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

//testing stuff, current, self, goal
double goalAngle, requiredAngle, currentAngle, requiredDistance, x_c, y_c, x_s = 24, y_s = 0;

static bool isAuton = false, isPID = false, isTurning = false, isFlywheel = false, isUser = false; 
static bool resetPID = true, resetTurning = true, resetFlywheel = true;
static double setPID = 0, setTurning = 0, setFlywheel = 0;

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

void GoToPoint(double x_g, double y_g) {
  //turn the robot
  
  x_c = x_g - x_s;
  y_c = y_g - y_s;
  requiredDistance = sqrt((x_c * x_c) + (y_c * y_c));

  goalAngle = asin(x_c / requiredDistance) * 57.2958;
  requiredAngle = goalAngle - currentAngle;
  if (fabs(requiredAngle) > 3) {
    setTurning = requiredAngle;
    isTurning = true;
    wait(6000, msec);
    isTurning = false;
    currentAngle = requiredAngle;
  }

  setPID = requiredDistance;
  isPID = true;
  wait(8000,msec);
  isPID = false;
  x_s += x_c;
  y_s += y_c;

  Brain.Screen.print(x_s);
  Brain.Screen.print(" , ");
  Brain.Screen.print(y_s);
  Brain.Screen.print(" , ");
  Brain.Screen.print(currentAngle);
  Brain.Screen.newLine();
}
