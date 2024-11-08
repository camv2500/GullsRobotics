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

void Autonomous() {
    // Test the moveForwardPID function with a target distance of 1000 units and max speed of 100
    moveForwardPID(1000, 100, 3000);

    // Test the turnClockwisePID function with a target angle of 90 degrees and max speed of 50
    turnClockwiseTime(3000, 100);  // Turn clockwise for x milliseconds  at 100% speed

}