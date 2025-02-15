#include "robot-config.h"
#include "DriverControl.h"
#include "AutonFunctions.h"
#include "Autonomous.h"

using namespace pros;

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

//auton controller
int autonController() {
    //this will run for the entirety of the auton, being the secondary thread that runs in parallel with the main on
    while(isAuton) {
      //checks if the PID routine should be running using variables set in the main thread
      if (isPID) {
        //if the program is just now setting PID, it will run a first time setup, otherwise just keeps looping the same thing
        if (resetPID) {
          setPID = ConvertInchesToRevolutions(setPID, 2.75);
          runPID(setPID, true);
          resetPID = false;
        }
        else {runPID(setPID);}
      }
  
      //checks if the PID Turning routine should be running using variables set in the main thread
      if (isTurning) {
        //if the program is just now setting PID, it will run a first time setup, otherwise just keeps looping the same thing
        if (resetTurning) {
          setTurning = ConvertDegreesToInches(setTurning, 9);
          setTurning = ConvertInchesToRevolutions(setTurning, 2.75);
          runPID(setTurning, true, true);
          resetTurning = false;
        }
        else {runPID(setTurning, false, true);}
      }
  
    //   if (isIntaking) {
    //       if(ballDetector.objectDistance(mm) < 100){
    //         intakeRollerMotor.spinFor( 180, degrees, false );
    //         IntakeBalls(false, 0);
    //         isIntaking = false;
    //       }
    //   }
  
     delay(5);
    }
    return 1;
  }

void Autonomous() {
    // Test the moveForwardPID function with a target distance of 200 units and max speed of 127
    MoveBot(24, 65);
    delay(1000);
    MoveBot(-24, 65);
    master.print(0, 0, "completed moveForwardPID");
    delay(3000);
    master.print(0, 0, "");

    RotateBot(180, 127);  // Turn counterclockwise for x milliseconds  at 100% speed
    delay(1000);
    RotateBot(-180, 127);  // Turn clockwise for x milliseconds  at 100% speed
    master.print(0, 0, "completed Turn");

}