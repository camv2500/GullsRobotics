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

void Autonomous() {
    //convert the inches to revolutions
	double revs = ConvertInchesToRevolutions(180);
	//print out the revolutions that it will be using on the robot
	lcd::print(1, "%f", revs);
	while(true) {
		//continuously run the pid function, but each time it runs it will use the updated motor encoders to
		//reflect how far the robot has actually moved
		runPID(revs);
	}
}