#include "main.h"
#include "robot-config.h"
#include "DriverControl.h"
#include "AutonFunctions.h"
#include "Autonomous.h"

using namespace pros;



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	isAuton = true; resetPID = true; resetTurning = true; isUser = false;
	Task t1 (autonController);
	Autonomous();
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// Controller master(pros::E_CONTROLLER_MASTER);
	// Motor left_mtr(1);
	// Motor right_mtr(2);

	// while (true) {
	// 	lcd::print(0, "%d %d %d", (lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	// 	                 (lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	// 	                 (lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
	// 	int left = master.get_analog(ANALOG_LEFT_Y);
	// 	int right = master.get_analog(ANALOG_RIGHT_Y);

	// 	left_mtr = left;
	// 	right_mtr = right;

	// 	delay(20);
	// }
	isAuton = false; resetPID = true; resetTurning = true; isUser = true;

	Task t1 (driverControl);
	Task t2 (intakeRings);
	
}
