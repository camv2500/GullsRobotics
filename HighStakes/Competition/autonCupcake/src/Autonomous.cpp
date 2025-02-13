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
    // Test the moveForwardPID function with a target distance of 200 units and max speed of 127
    moveForwardPID(48, 127);
    delay(1000);
    moveForwardPID(-48, 127);
    master.print(0, 0, "completed moveForwardPID");
    delay(3000);
    master.print(0, 0, "");
    // turnClockwiseTime(3000, 127);  // Turn clockwise for x milliseconds  at 100% speed
    // turnClockwiseTime(360, 127);  // Turn clockwise for x milliseconds  at 100% speed
    turnPID(180, 127);  // Turn counterclockwise for x milliseconds  at 100% speed
    delay(1000);
    turnPID(-180, 127);  // Turn clockwise for x milliseconds  at 100% speed
    master.print(0, 0, "completed Turn");

}