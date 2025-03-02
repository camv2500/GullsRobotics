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
    intakeAuton(true);
    clampAuton(false);
    delay(100);
    lateralPID(-46, 127);
    delay(1000);
    intakeAuton(false);
    delay(100);
    turnPID(40, 127);
    delay(100);
    lateralPID(15, 127);
    delay(100);
    clampAuton(true);
    flip(180, 127);
    delay(100);
    flip(-180, 127);
    delay(100);
    lateralPID(14, 127);
    delay(100);
    turnPID(80, 127);
    delay(100);
    intakeAuton(true);
    delay(100);
    lateralPID(-BLOCK, 127);
    delay(100);
    turnPID(40, 127);
    delay(100);
    lateralPID(-BLOCK, 127);
    delay(100);
    lateralPID(BLOCK, 127);
    delay(100);
    intakeAuton(false);
    delay(100);
    turnPID(175, 127);
    delay(100);
    lateralPID(THREE_BLOCKS, 127);
    delay(100);
    clampAuton(false);
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

}