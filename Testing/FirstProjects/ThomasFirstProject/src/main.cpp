#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

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
void autonomous() {}

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

#define FRONT_LEFT_WHEEL_PORT 1
#define FRONT_RIGHT_WHEEL_PORT 10
#define BACK_LEFT_WHEEL_PORT 11
#define BACK_RIGHT_WHEEL_PORT 20

void opcontrol() {
	// pros::Motor left_mtr(LEFT_MOTOR_PORT);
	// pros::Motor right_mtr(RIGHT_MOTOR_PORT, true);
	// pros::Controller master(CONTROLLER_MASTER);

	

	// while (true) {
	// 	// pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	// 	//                  (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	// 	//                  (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);
	// 	left_mtr.move(master.get_analog(ANALOG_LEFT_Y));
	// 	right_mtr.move(master.get_analog(ANALOG_RIGHT_Y));
		

	// 	pros::delay(2);
	// }
  pros::Motor front_left_wheel (FRONT_LEFT_WHEEL_PORT, pros::E_MOTOR_GEAR_BLUE, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor back_left_wheel (BACK_LEFT_WHEEL_PORT, pros::E_MOTOR_GEAR_BLUE, pros::E_MOTOR_ENCODER_DEGREES);
  pros::Motor front_right_wheel (FRONT_RIGHT_WHEEL_PORT, pros::E_MOTOR_GEAR_BLUE, true);
  pros::Motor back_right_wheel (BACK_RIGHT_WHEEL_PORT, pros::E_MOTOR_GEAR_BLUE, true);

  pros::Motor_Group leftMotorGroup({front_left_wheel, back_left_wheel});
  pros::Motor_Group rightMotorGroup({front_right_wheel, back_right_wheel});
  pros::Controller master (CONTROLLER_MASTER);

  while (true) {
    int power = master.get_analog(ANALOG_LEFT_Y);
    int turn = master.get_analog(ANALOG_RIGHT_X);
    int left = power + turn;
    int right = power - turn;
    front_left_wheel.move(left);
	back_left_wheel.move(left);
    front_right_wheel.move(right);
	back_right_wheel.move(right);

    pros::delay(2);
  }

}
