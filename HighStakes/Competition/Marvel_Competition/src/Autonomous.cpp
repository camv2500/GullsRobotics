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

#define QUARTER_BLOCK 6
#define HALF_BLOCK 12
#define BLOCK 24
#define BLOCK_AND_HALF 36
#define TWO_BLOCKS 48
#define TWO_BLOCKS_AND_HALF 60
#define THREE_BLOCKS 72
#define THREE_BLOCKS_AND_HALF 84
#define FOUR_BLOCKS 96
#define FOUR_BLOCKS_AND_HALF 108
#define FIVE_BLOCKS 120
#define FIVE_BLOCKS_AND_HALF 132
#define SIX_BLOCKS 144
#define SIX_BLOCKS_AND_HALF 156
#define SEVEN_BLOCKS 168

void competition_initialize() {}

void Autonomous() {
    // Test the lateralPID function with a target distance of 1000 units and max speed of 100
    // intakeAuton(true);
    // delay(100);
    // lateralPID(6, 127);
    // delay(100);
    // lateralPID(-6, 127);
    // delay(100);
    // lateralPID(12, 127);
    // delay(100);
    // lateralPID(-12, 127);
    // delay(100);
    // lateralPID(24, 127);
    // delay(100);
    // lateralPID(-24, 127);
    // delay(100);
    // lateralPID(36, 127);
    // delay(100);
    // lateralPID(-36, 127);
    // delay(100);
    // lateralPID(48, 127);
    // delay(100);
    // lateralPID(-48, 127);
    // delay(100);
    // intakeAuton(false);
    // delay(100);
    // turnPID(45, 127);
    // delay(100);
    // turnPID(-45, 127);
    // delay(100);
    // turnPID(90, 127);
    // delay(100);
    // turnPID(-90, 127);
    // delay(100);
    // turnPID(135, 127);
    // delay(100);
    // turnPID(-135, 127);
    // delay(100);
    // turnPID(180, 127);
    // delay(100);
    // turnPID(-180, 127);
    // delay(100);

    // delay(3000);

    // Test the turnClockwisePID function with a target angle of 90 degrees and max speed of 100
    // turnPID(90, 127);  // Turn clockwise for x milliseconds  at 100% speed

    // intakeAuton(true);
    // delay(100);
    // lateralPID(-BLOCK, 127);
    // delay(1000);
    // intakeAuton(false);
    // delay(100);
    // lateralPID(THREE_BLOCKS, 127);
    // delay(100);
    // turnPID(-90, 127);
    // delay(100);
    // lateralPID(BLOCK_AND_HALF, 127);
    // delay(100);
    // flip(180, 127);
    // delay(100);
    // flip(-180, 127);
    // delay(100);

    lateralPID(20, 127);
    delay(100);
    turnPID(-90, 127);
    delay(100);
    lateralPID(10, 127);
    flip(180, 127);
    delay(100);
    flip(-180, 127);
    delay(100);

}