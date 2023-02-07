#include "vex.h"
#include "motion.h"
#include "math.h"

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

void autonomous(void) {
  isAuton = true; resetPID = true; resetTurning = true; resetFlywheel = true; isUser = false;
  task StartAuton(autonController);
  GoToPoint(24,15);
  //setFlywheel = 400;
  //isFlywheel = true;

  //setPID = 12;
  //isPID = true;
  //wait(1000, msec);

  Brain.Screen.print("isExited");
  SpinMotors(0); 
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

static bool isUserFlywheel = false, resetUserFlywheel = false;
static double setUserFlywheel = 0, indexerCount = 0;

void ToggleFlywheelOn() {
  resetUserFlywheel = true;
  setUserFlywheel = 450;
  isUserFlywheel = true;
}

void ToggleFlywheelOff() {
  isUserFlywheel = false;
  resetUserFlywheel = true;
  setUserFlywheel = 0;
  isUserFlywheel = true;
}

void userSpinMotors() {

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
        Brain.Screen.print(FlyWheel1.velocity(rpm));
        Brain.Screen.newLine();
      }
    }

    lMotor1.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);
    lMotor2.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);
    lMotor3.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);
    lMotor4.spin(fwd, (Controller1.Axis2.value() - Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);
    rMotor1.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);
    rMotor2.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);
    rMotor3.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);
    rMotor4.spin(fwd, (Controller1.Axis2.value() + Controller1.Axis1.value()) / 2, vex::velocityUnits::pct);

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
    else {
      rollerMotor.stop(brakeType::hold);
    }

    //flywheel controller
    if(Controller1.ButtonR1.pressing()) {
      magLifter.set(false);
      ToggleFlywheelOn();
      if (Controller1.ButtonR2.pressing()) {
        if (indexerCount < 100) {
          indexer1.set(true);
          indexerCount += 12;
        }
        else if (indexerCount < 500) {
          indexer1.set(false);
          indexerCount += 12;
        }
        else if (count >= 500) {
          indexerCount = 0;
        }
        else {
          indexerCount += 12;
        }
      }
      else {
        indexerCount = 0;
      }
    }
    else {
      ToggleFlywheelOff();
    }

    //endgame deploy
    if (Controller1.ButtonY.pressing()) {
      endGame.set(true);
    }

    wait(10,msec);
  }

  return 1;
}

void usercontrol(void) {
  isUser = true; isAuton = false;
  task StartUser(userController);
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
