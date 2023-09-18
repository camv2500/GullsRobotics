#include "main.h"
#include "robot-config.h"
#include "DriverControl.h"
#include "AutonFunctions.h"
#include "Autonomous.h"
// #include "selection.h"

using namespace pros;

// selector configuration
// TODO Implement UI and PID.
// #define HUE 360 // color of theme from 0-360
// #define AUTONS "Do Nothing", "Front", "Back" // names of the autonomous programs
// #define DEFAULT 1 // default auton

int SelectedAuton;

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	// SelectedAuton = PreAutonomous(); // RED = 1-4, BLUE = 5-8, ORANGE = 9-12, PURPLE = 13-16;
	// selector::init();
}

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
	// SelectedAuton = selector::auton;
	SelectedAuton = 1;
	Autonomous(SelectedAuton); // Runs auton based on menu
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
	lcd::print(1, "Driver");
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

	// autonomous();
	Task t1(control);
	Task t2(driver);
	Task t3(intake);
	Task t4(lift);
	
}
